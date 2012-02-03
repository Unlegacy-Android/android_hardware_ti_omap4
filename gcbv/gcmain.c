/*
 * Copyright (c) 2011, Texas Instruments, Inc.
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

#include <gcx.h>
#include <gc2d.h>
#include "gcmain.h"

#ifndef GC_DUMP
#	define GC_DUMP 0
#endif

#if GC_DUMP
#	define GC_PRINT gcdump
#else
#	define GC_PRINT(...)
#endif

static int g_fd;	/* Open device file descriptor. */

/*******************************************************************************
 * IOCTL wrappers.
 */

#if GC_DUMP
#	define GC_IOCTL(result, id, data) \
	{ \
		sleep(1); \
		result = ioctl(g_fd, id, data); \
	}
#else
#	define GC_IOCTL(result, id, data) \
	{ \
		result = ioctl(g_fd, id, data); \
	}
#endif

void gc_map_wrapper(struct gcmap *gcmap)
{
	int result;
	GC_IOCTL(result, GCIOCTL_MAP, gcmap);
	if (result != 0) {
		GC_PRINT(GC_ERR_MSG "ioctl failed (%d)\n",
			__func__, __LINE__, result);
		gcmap->gcerror = GCERR_IOCTL;
	}
}

void gc_unmap_wrapper(struct gcmap *gcmap)
{
	int result;
	GC_IOCTL(result, GCIOCTL_UNMAP, gcmap);
	if (result != 0) {
		GC_PRINT(GC_ERR_MSG "ioctl failed (%d)\n",
			__func__, __LINE__, result);
		gcmap->gcerror = GCERR_IOCTL;
	}
}

void gc_commit_wrapper(struct gccommit *gccommit)
{
	int result;
	GC_IOCTL(result, GCIOCTL_COMMIT, gccommit);
	if (result != 0) {
		GC_PRINT(GC_ERR_MSG "ioctl failed (%d)\n",
			__func__, __LINE__, result);
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
 * Device init/cleanup.
 */

extern void dev_init(void) __attribute__((constructor));
extern void dev_init(void)
{
	GC_PRINT(GC_INFO_MSG "\n", __func__, __LINE__);

	g_fd = open("/dev/gcioctl", O_RDWR);
	if (g_fd == -1) {
		GC_PRINT(GC_ERR_MSG " failed to open device (%d)\n",
			__func__, __LINE__, errno);
		goto exit;
	}

	bv_init();

exit:;
}

extern void dev_exit(void) __attribute__((destructor));
extern void dev_exit(void)
{
	GC_PRINT(GC_INFO_MSG "\n", __func__, __LINE__);

	bv_exit();

	if (g_fd != 0) {
		close(g_fd);
		g_fd = 0;
	}
}
