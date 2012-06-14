/*
 * Copyright (c) 2012,
 * Texas Instruments, Inc. and Vivante Corporation
 * 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Texas Instruments, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL TEXAS INSTRUMENTS, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "gcmain.h"
#include <semaphore.h>

#define GCZONE_NONE		0
#define GCZONE_ALL		(~0U)
#define GCZONE_INIT		(1 << 0)
#define GCZONE_CALLBACK		(1 << 1)

GCDBG_FILTERDEF(gcmain, GCZONE_NONE,
		"init",
		"callback")


static int g_handle;


/*******************************************************************************
 * Callback manager.
 */

struct gccallbackinfo {
	/* Callback handle. */
	unsigned long handle;

	/* Termination semaphore. */
	sem_t stop;

	/* Callback thread handle. */
	pthread_t thread;
};

struct gccallbackinfo g_callbackinfo;

static void *callbackthread(void *_gccallbackinfo)
{
	struct gccallbackinfo *gccallbackinfo;
	struct gccmdcallbackwait gccmdcallbackwait;
	int result;

	/* Get callback info. */
	gccallbackinfo = (struct gccallbackinfo *) _gccallbackinfo;

	/* Initialize the command. */
	gccmdcallbackwait.handle = gccallbackinfo->handle;
	gccmdcallbackwait.timeoutms = 2000;

	/* Enter wait loop. */
	while (1) {
		/* Call the kernel to wait for callback event. */
		result = ioctl(g_handle, GCIOCTL_CALLBACK_WAIT,
			       &gccmdcallbackwait);
		if (result == 0) {
			if (gccmdcallbackwait.gcerror == GCERR_NONE) {
				/* Work completed. */
				GCDBG(GCZONE_CALLBACK, "callback 0x%08X(0x%08X).\n",
				      (unsigned int) gccmdcallbackwait.callback,
				      (unsigned int) gccmdcallbackwait.callbackparam);

				/* Invoke the callback. */
				gccmdcallbackwait.callback(
					gccmdcallbackwait.callbackparam);
			} else if (gccmdcallbackwait.gcerror == GCERR_TIMEOUT) {
				/* Timeout. */
				GCDBG(GCZONE_CALLBACK, "callback wait timeout.\n");
			} else {
				/* Error occurred. */
				GCERR("callback wait failed (0x%08X).\n",
				      gccmdcallbackwait.gcerror);
				break;
			}
		}
		else if (result != -EINTR) {
			GCERR("callback wait ioctl failed (%d).\n", result);
			break;
		}

		/* Stop requested? */
		if (sem_trywait(&gccallbackinfo->stop) == 0) {
			GCDBG(GCZONE_CALLBACK, "terminating.\n");
			break;
		}
	}

	return NULL;
}

static int callback_start(struct gccallbackinfo *gccallbackinfo)
{
	int result;
	struct gccmdcallback gccmdcallback;

	/* Initialize callback. */
	gccmdcallback.handle = 0;
	result = ioctl(g_handle, GCIOCTL_CALLBACK_ALLOC, &gccmdcallback);
	if (result != 0) {
		GCERR("callback ioctl failed (%d).\n", result);
		goto fail;
	}

	if (gccmdcallback.gcerror != GCERR_NONE) {
		GCERR("failed to initialize callback mechanism (0x%08X).\n",
		      gccmdcallback.gcerror);
		goto fail;
	}

	gccallbackinfo->handle = gccmdcallback.handle;

	/* Initialize the termiantion semaphore. */
	result = sem_init(&gccallbackinfo->stop, 0, 0);
	if (result != 0) {
		GCERR("callback semaphore init failed (%d).\n", result);
		goto fail;
	}

	/* Start the thread. */
	result = pthread_create(&gccallbackinfo->thread, NULL,
				callbackthread, gccallbackinfo);
	if (result != 0) {
		GCERR("failed to start callback thread.\n");
		goto fail;
	}

	/* Success. */
	return 0;

fail:
	if (gccmdcallback.handle != 0)
		ioctl(g_handle, GCIOCTL_CALLBACK_FREE, &gccmdcallback);

	return result;
}

static void callback_stop(struct gccallbackinfo *gccallbackinfo)
{
	struct gccmdcallback gccmdcallback;

	/* Stop the thread. */
	GCDBG(GCZONE_CALLBACK, "stopping active client.");

	sem_post(&gccallbackinfo->stop);
	pthread_kill(gccallbackinfo->thread, SIGINT);

	GCDBG(GCZONE_CALLBACK, "waiting to join callback thread...\n");

	pthread_join(gccallbackinfo->thread, NULL);

	gccallbackinfo->thread = 0;

	/* Free kernel resources. */
	if (gccmdcallback.handle != 0) {
		gccmdcallback.handle = gccallbackinfo->handle;
		ioctl(g_handle, GCIOCTL_CALLBACK_FREE, &gccmdcallback);
		gccallbackinfo->handle = 0;
	}
}


/*******************************************************************************
 * IOCTL wrappers.
 */

#if GCDEBUG_ENABLE && 0
#define GCPRINTDELAY() sleep(1)
#else
#define GCPRINTDELAY()
#endif

void gc_map_wrapper(struct gcmap *gcmap)
{
	int result;

	GCPRINTDELAY();
	result = ioctl(g_handle, GCIOCTL_MAP, gcmap);

	if (result != 0) {
		GCERR("ioctl failed (%d).\n", result);
		gcmap->gcerror = GCERR_IOCTL;
	}
}

void gc_unmap_wrapper(struct gcmap *gcmap)
{
	int result;

	GCPRINTDELAY();
	result = ioctl(g_handle, GCIOCTL_UNMAP, gcmap);

	if (result != 0) {
		GCERR("ioctl failed (%d).\n", result);
		gcmap->gcerror = GCERR_IOCTL;
	}
}

void gc_commit_wrapper(struct gccommit *gccommit)
{
	int result;

	GCPRINTDELAY();
	gccommit->handle = g_callbackinfo.handle;
	result = ioctl(g_handle, GCIOCTL_COMMIT, gccommit);

	if (result != 0) {
		GCERR("ioctl failed (%d).\n", result);
		gccommit->gcerror = GCERR_IOCTL;
	}
}


/*******************************************************************************
 * Convert floating point in 0..1 range to an 8-bit value in range 0..255.
 */

union gcfp {
	struct {
		unsigned int mantissa:23;
		unsigned int exponent:8;
		unsigned int sign:1;
	} comp;

	float value;
};

unsigned char gcfp2norm8(float value)
{
	union gcfp gcfp;
	int exponent;
	unsigned int mantissa;
	int shift;

	/* Get access to components. */
	gcfp.value = value;

	/* Clamp negatives. */
	if (gcfp.comp.sign)
		return 0;

	/* Get unbiased exponent. */
	exponent = (int) gcfp.comp.exponent - 127;

	/* Clamp if too large. */
	if (exponent >= 0)
		return 255;

	/* Clamp if too small. */
	if (exponent < -8)
		return 0;

	/* Determine the shift value. */
	shift = (23 - 8) - exponent;

	/* Compute the mantissa. */
	mantissa = (gcfp.comp.mantissa | 0x00800000) >> shift;

	/* Normalize. */
	mantissa = (mantissa * 255) >> 8;

	return (unsigned char) mantissa;
}


/*******************************************************************************
 * Cache operation wrapper.
 */

enum bverror gcbvcacheop(int count, struct c2dmrgn rgn[],
			 enum bvcacheop cacheop)
{
	int result;
	struct gccachexfer xfer;

	if ((count < 0) || (count > 3))
		return BVERR_CACHEOP;

	xfer.count = count;
	xfer.dir = cacheop;
	memcpy(xfer.rgn, rgn, count * sizeof(struct c2dmrgn));

	GCPRINTDELAY();
	result = ioctl(g_handle, GCIOCTL_CACHE, &xfer);

	if (result != 0)
		GCERR("ioctl failed (%d).\n", result);

	return BVERR_NONE;
}


/*******************************************************************************
 * Device init/cleanup.
 */

void  __attribute__((constructor)) dev_init(void)
{
	char* env;

	env = getenv("GCBV_DEBUG");
	if (env && (atol(env) != 0))
		GCDBG_ENABLEDUMP();

	GCDBG_INIT();
	GCDBG_REGISTER(gcmain);

	GCENTER(GCZONE_INIT);

	g_handle = open("/dev/gcioctl", O_RDWR);
	if (g_handle == -1) {
		GCERR("failed to open device (%d).\n", errno);
		goto fail;
	}

	if (callback_start(&g_callbackinfo) != 0)
		goto fail;

	bv_init();

	GCEXIT(GCZONE_INIT);
	return;

fail:
	if (g_handle > 0) {
		close(g_handle);
		g_handle = 0;
	}

	GCEXIT(GCZONE_INIT);
}

void __attribute__((destructor)) dev_exit(void)
{
	GCENTER(GCZONE_INIT);

	bv_exit();
	callback_stop(&g_callbackinfo);

	if (g_handle != 0) {
		close(g_handle);
		g_handle = 0;
	}

	GCEXIT(GCZONE_INIT);
	GCDBG_EXIT();
}

