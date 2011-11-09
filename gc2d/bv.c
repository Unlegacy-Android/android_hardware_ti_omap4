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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h> /* open() */
#include <sys/ioctl.h>
#include <unistd.h> /* close() */
#include <sys/signal.h>
#include "bv.h"
#include "bltsville.h"
#include "ocd.h"
#include "gcreg.h"

#if !defined(COUNTOF)
#	define COUNTOF(a) (sizeof(a) / sizeof(a[0]))
#endif

#define GET_2D_RESRC_USAGE(fg_rop, bg_rop, use_src, use_dest) \
{ \
	uint8_t target_only = \
	((fg_rop == 0x00) && (bg_rop == 0x00)) ||  /* Blackness.    */ \
	((fg_rop == 0x55) && (bg_rop == 0x55)) ||  /* Invert.       */ \
	((fg_rop == 0xAA) && (bg_rop == 0xAA)) ||  /* No operation. */ \
	((fg_rop == 0xFF) && (bg_rop == 0xFF));    /* Whiteness.    */ \
	\
	use_src = !target_only && \
			((((fg_rop >> 2) & 0x33) != (fg_rop & 0x33)) || \
				(((bg_rop >> 2) & 0x33) != (bg_rop & 0x33))); \
	\
	use_dest = (((fg_rop >> 1) & 0x55) != (fg_rop & 0x55)) || \
			(((bg_rop >> 1) & 0x55) != (bg_rop & 0x55)); \
}

#define CONVERT_DEST_FMT(ocdfmt) \
	(ocdfmt == OCDFMT_ARGB12 ? AQDE_DEST_CONFIG_FORMAT_A4R4G4B4 : \
	(ocdfmt == OCDFMT_1RGB15 ? AQDE_DEST_CONFIG_FORMAT_A1R5G5B5 : \
	(ocdfmt == OCDFMT_xRGB16 ? AQDE_DEST_CONFIG_FORMAT_R5G6B5 : \
	(ocdfmt == OCDFMT_ARGB24 ? AQDE_DEST_CONFIG_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_BGRA24 ? AQDE_DEST_CONFIG_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_RGBA24 ? AQDE_DEST_CONFIG_FORMAT_A8R8G8B8 : 0xFFFFFFFF))))))

#define CONVERT_DEST_SWZZL(ocdfmt) \
	(ocdfmt == OCDFMT_ARGB12 ? AQDE_DEST_CONFIG_SWIZZLE_RGBA : \
	(ocdfmt == OCDFMT_1RGB15 ? AQDE_DEST_CONFIG_SWIZZLE_RGBA : \
	(ocdfmt == OCDFMT_xRGB16 ? AQDE_DEST_CONFIG_SWIZZLE_RGBA : \
	(ocdfmt == OCDFMT_ARGB24 ? AQDE_DEST_CONFIG_SWIZZLE_RGBA : \
	(ocdfmt == OCDFMT_BGRA24 ? AQDE_DEST_CONFIG_SWIZZLE_ABGR : \
	(ocdfmt == OCDFMT_RGBA24 ? AQDE_DEST_CONFIG_SWIZZLE_ARGB : 0xFFFFFFFF))))))

#define CONVERT_SRC_FMT(ocdfmt) \
	(ocdfmt == OCDFMT_ARGB12 ? AQDE_SRC_CONFIG_FORMAT_A4R4G4B4 : \
	(ocdfmt == OCDFMT_1RGB15 ? AQDE_SRC_CONFIG_FORMAT_A1R5G5B5 : \
	(ocdfmt == OCDFMT_xRGB16 ? AQDE_SRC_CONFIG_FORMAT_R5G6B5 : \
	(ocdfmt == OCDFMT_ARGB24 ? AQDE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_BGRA24 ? AQDE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_RGBA24 ? AQDE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : 0xFFFFFFFF))))))

#define CONVERT_SRC_SWZZL(ocdfmt) \
	(ocdfmt == OCDFMT_ARGB16 ? AQDE_SRC_CONFIG_SWIZZLE_RGBA : \
	(ocdfmt == OCDFMT_ARGB24 ? AQDE_SRC_CONFIG_SWIZZLE_RGBA : \
	(ocdfmt == OCDFMT_BGRA24 ? AQDE_SRC_CONFIG_SWIZZLE_ABGR : \
	(ocdfmt == OCDFMT_RGBA24 ? AQDE_SRC_CONFIG_SWIZZLE_ARGB : 0xFFFFFFFF))))

#define CONVERT_SRC1_FMT(ocdfmt) \
	CONVERT_SRC_FMT(ocdfmt)

#define CONVERT_SRC2_FMT(ocdfmt) \
	CONVERT_SRC_FMT(ocdfmt)

#define CONVERT_SRC_GCFMT(ocdfmt) \
	(ocdfmt == OCDFMT_ARGB16 ? GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_R5G6B5 : \
	(ocdfmt == OCDFMT_ARGB24 ? GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_BGRA24 ? GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_RGBA24 ? GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : 0xFFFFFFFF))))

#define CONVERT_SRC1_GCFMT(ocdfmt) \
	CONVERT_SRC_GCFMT(ocdfmt)

#define CONVERT_SRC2_GCFMT(ocdfmt) \
	CONVERT_SRC_GCFMT(ocdfmt)

#define db(x) \
	fprintf(stdout, "%s(%d): %s=(%08ld)\n", __FUNCTION__, __LINE__, #x, (unsigned long)x); \
	fflush(stdout)

#define dbx(x) \
	fprintf(stdout, "%s(%d): %s=(0x%08lx)\n", __FUNCTION__, __LINE__, #x, (unsigned long)x); \
	fflush(stdout)

#define dbs(x) \
	fprintf(stdout, "%s(%d): %s=(%s)\n", __FUNCTION__, __LINE__, #x, x); \
	fflush(stdout)

#define BLT _IOW('x', 100, uint32_t)
#define MAP _IOWR('x', 101, uint32_t)
#define UMAP _IOW('x', 102, uint32_t)

#define MAX_THRD 1

struct blt {
	uint32_t *cmdbuf;
	uint32_t cmdlen;
	uint32_t offset[128];
	uint32_t linkindex[128];
	uint32_t linkvalue[128];
};

struct bv_alpha {
       /*
              The blending formulas used are as follows:
                     outR = srcR * srcRFactor + dstR * dstRFactor
                     outG = srcG * srcGFactor + dstG * dstGFactor
                     outB = srcB * srcBFactor + dstB * dstBFactor
                     outA = srcA * srcAFactor + dstA * dstAFactor
       */

       /*
              Global color values.
       */
       uint32_t src_global_color;
       uint32_t dst_global_color;

       /*
              NORMAL:
                     pick straight alpha value;
              INVERSED:
                     get the inverse of alpha value.
       */
       uint8_t src_inverse_alpha;
       uint8_t dst_inverse_alpha;

       /*
              NORMAL:
                     pick the pixel (local) alpha value;
              GLOBAL:
                     pick the global alpha value;
              SCALED:
                     use the multiplication product of local and global alphas.
       */
       uint8_t src_global_alpha_mode;
       uint8_t dst_global_alpha_mode;

       /*
              ZERO:
                     R/G/B/A blending factors = 0;
              ONE:
                     R/G/B/A blending factors = 1;
              NORMAL:
                     R/G/B/A blending factors are the alpha value determined
                     above;
              INVERSED:
                     R/G/B/A blending factors are the inversed alpha value
                     determined above;
              COLOR:
                     R/G/B blending factors is the color of the pixel;
                     A blending factor is the alpha value determined above;
              COLOR_INVERSED:
                     R/G/B blending factors is the inversed color
                           of the pixel;
                     A blending factor is the inversed alpha value
                           determined above;
              SATURATED_ALPHA:
                     Factors are set as follows (source mode pseudo code):
                            srcFactorA = 1.0
                           srcFactorR = srcFactorG = srcFactorB =
                                  (srcAlpha < (1.0 - dstAlpha))
                                         ? srcAlpha
                                         : (1.0 - dstAlpha)
                     Note:
                           1. srcAlpha and dstAlpha are the determined
                                  alpha values of source and destination
                                  pixels.
                           2. Similar formula is used for the destination
                                  factos.
              SATURATED_DEST_ALPHA:
                     Same as above with the exception of alpha values
                     reversed (source vs. destination).
       */
       uint8_t src_factor_mode;
       uint8_t dst_factor_mode;

       /*
              DISABLED:
                     Source factors are based off of the destination pixel;
                     Destination factors are based off of the source pixel;
              ENABLED:
                     Source factors are based off of the source pixel;
                     Destination factors are based off of the destination pixel;
       */
       uint8_t src_alpha_factor;
       uint8_t dst_alpha_factor;

       /*
              DISABLED:
                     Premultiplication is disabled.
              ENABLED:
                     Premultipy the color by its own alpha value
                     (alpha value stays the same).
       */
       uint8_t src_premul_src_alpha;
       uint8_t dst_premul_dst_alpha;

       /*
              DISABLE:
                     Premultiplication is disabled.
              ALPHA:
                     Premultipy the color by the global source alpha value
                     (alpha value stays the same).
              COLOR:
                     Premultipy the color by the global source color values
                     (alpha value stays the same).
       */
       uint8_t src_premul_global_mode;

       /*
              DISABLED:
                     Division is disabled.
              ENABLED:
                     Divide blended color by its own alpha value
                     (alpha value stays the same).
       */
       uint8_t dst_demul_dst_alpha;
};

static const char *file = "/dev/gc-core";
static int fd;
static pthread_t id[MAX_THRD];

extern void bv_init(void) __attribute__((constructor));
extern void bv_exit(void) __attribute__((destructor));

/* TODO: check that we aren't using more logic than we need */
static void sig_handler(int sig)
{
	fprintf(stdout, "%s::%d:%lx:%d\n", __FUNCTION__, __LINE__,
		(unsigned long)pthread_self(), sig);
	fflush(stdout);
	sleep(2); sched_yield();
}

/* TODO: check that we aren't using more logic than we need */
static void * thread(void *p)
{
	int r = 0;
	sigset_t set;
	struct sigaction sa;

	sigemptyset(&set);
	sa.sa_handler = sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);

	while (1) {
		fprintf(stdout, "%s::%d\n", __FUNCTION__, __LINE__); fflush(stdout);
		sigwait(&set, &r);
		fprintf(stdout, "%s::%d\n", __FUNCTION__, __LINE__); fflush(stdout);
	}
	return NULL;
}

extern void bv_init(void)
{
	int32_t res, i;

	fd = open(file, O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "%s(%d): failed to open device (%d)\n",
			__FUNCTION__, __LINE__, errno);
		fflush(stderr);
		goto exit;
	}

	for (i = 0; i < MAX_THRD; i++) {
		res = pthread_create(&id[i], NULL, thread, NULL);
		if(res != 0) {
			fprintf(stderr, "%s(%d): failed to start a thread (%d)\n",
				__FUNCTION__, __LINE__, res);
			fflush(stderr);
			goto exit;
		}
	}

exit:;
}

extern void bv_exit(void)
{
	int32_t res, i;

	for (i = 0; i < MAX_THRD; i++) {
		if (id[i] != 0) {
			res = pthread_cancel(id[i]);
			if (res == 0) {
				id[i] = 0;
			} else {
				fprintf(stderr, "%s(%d): failed to cancel a thread (%d)\n",
					__FUNCTION__, __LINE__, res);
				fflush(stderr);
			}
		}
	}

	if (fd != 0) {
		close(fd);
		fd = 0;
	}
}

enum bverror bv_map(struct bvbuffdesc *buffdesc)
{
	int32_t res;

	if (!buffdesc) {
		fprintf(stderr, "%s(%d): invalid argument\n", __FUNCTION__, __LINE__);
		fflush(stderr);
		res = BVERR_UNK;
		goto exit;
	}

	if (sizeof(*buffdesc) != sizeof(struct bvbuffdesc)) {
		fprintf(stderr, "%s(%d): invalid argument\n", __FUNCTION__, __LINE__);
		fflush(stderr);
		res = BVERR_BUFFERDESC_VERS;
		goto exit;
	}

	res = ioctl(fd, MAP, buffdesc);
	if ((res == -1) || (buffdesc->map == NULL)) {
		fprintf(stderr, "%s(%d): mapping failed\n", __FUNCTION__, __LINE__);
		fflush(stderr);
		res = BVERR_UNK;
		goto exit;
	}

	res = BVERR_NONE;

exit:
	return res;
}

struct bvblendxlate {
	uint8_t match1;
	uint8_t match2;

	uint8_t dst_factor_mode;
	uint8_t dst_alpha_factor;

	uint8_t src_factor_mode;
	uint8_t src_alpha_factor;
};


/***********************************************
** Color factor is an alpha variant.
*/

#define BVBLENDMATCH(Mode, Inverse, Normal) \
	BVBLENDDEF_ ## Mode | \
	BVBLENDDEF_ ## Inverse | \
	BVBLENDDEF_ ## Normal

#define BVBLENDMODE(Mode, Inverse) \
	AQ_DRAWING_ENGINE_ALPHA_BLENDING_BLENDING_MODE_ ## Mode, \
	AQ_DRAWING_ENGINE_FACTOR_INVERSE_ ## Inverse

#define BVBLENDUNDEFINED() \
	~0, ~0

static struct bvblendxlate blendxlate[64] = {
	/**********************************************************************/
	/* color factor: 00 00 00 A:(1-Cd,Cd)=zero
	   alpha factor: zero ==> 00 00 00 */
	{
		0x00,
		0x00,

		BVBLENDMODE(ZERO, DISABLE),	/* K0/K3 */
		BVBLENDMODE(ZERO, DISABLE)	/* K1/K2 */
	},

	/* color factor: 00 00 01 A:(1-Cd,Ad)=Ad
	   alpha factor: Ad ==> 00 00 01 or 00 10 01 */
	{
		BVBLENDMATCH(ONLY_A, INV_C1, NORM_A1),
		BVBLENDMATCH(ONLY_A, INV_C2, NORM_A1),

		BVBLENDMODE(NORMAL, ENABLE),	/* K0/K3 */
		BVBLENDMODE(NORMAL, DISABLE)	/* K1/K2 */
	},

	/* color factor: 00 00 10 A:(1-Cd,Cs)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 00 00 11 A:(1-Cd,As)=As
	   alpha factor: As ==> 00 00 11 or 00 10 11 */
	{
		BVBLENDMATCH(ONLY_A, INV_C1, NORM_A2),
		BVBLENDMATCH(ONLY_A, INV_C2, NORM_A2),

		BVBLENDMODE(NORMAL, DISABLE),	/* K0/K3 */
		BVBLENDMODE(NORMAL, ENABLE)	/* K1/K2 */
	},

	/* color factor: 00 01 00 A:(1-Ad,Cd)=1-Ad
	   alpha factor: 1-Ad ==> 00 01 00 or 00 01 10 */
	{
		BVBLENDMATCH(ONLY_A, INV_A1, NORM_C1),
		BVBLENDMATCH(ONLY_A, INV_A1, NORM_C2),

		BVBLENDMODE(INVERSED, ENABLE),	/* K0/K3 */
		BVBLENDMODE(INVERSED, DISABLE)	/* K1/K2 */
	},

	/* color factor: 00 01 01 A:(1-Ad,Ad)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 00 01 10 A:(1-Ad,Cs)=1-Ad
	   alpha factor: 1-Ad ==> 00 01 00 or 00 01 10 */
	{
		BVBLENDMATCH(ONLY_A, INV_A1, NORM_C1),
		BVBLENDMATCH(ONLY_A, INV_A1, NORM_C2),

		BVBLENDMODE(INVERSED, ENABLE),	/* K0/K3 */
		BVBLENDMODE(INVERSED, DISABLE)	/* K1/K2 */
	},

	/* color factor: 00 01 11 A:(1-Ad,As)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 00 10 00 A:(1-Cs,Cd)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 00 10 01 A:(1-Cs,Ad)=Ad
	   alpha factor: Ad ==> 00 00 01 or 00 10 01 */
	{
		BVBLENDMATCH(ONLY_A, INV_C1, NORM_A1),
		BVBLENDMATCH(ONLY_A, INV_C2, NORM_A1),

		BVBLENDMODE(NORMAL, ENABLE),	/* K0/K3 */
		BVBLENDMODE(NORMAL, DISABLE)	/* K1/K2 */
	},

	/* color factor: 00 10 10 A:(1-Cs,Cs)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 00 10 11 A:(1-Cs,As)=As
	   alpha factor: As ==> 00 00 11 or 00 10 11 */
	{
		BVBLENDMATCH(ONLY_A, INV_C1, NORM_A2),
		BVBLENDMATCH(ONLY_A, INV_C2, NORM_A2),

		BVBLENDMODE(NORMAL, DISABLE),	/* K0/K3 */
		BVBLENDMODE(NORMAL, ENABLE)	/* K1/K2 */
	},

	/* color factor: 00 11 00 A:(1-As,Cd)=1-As
	   alpha factor: 1-As ==> 00 11 00 or 00 11 10 */
	{
		BVBLENDMATCH(ONLY_A, INV_A2, NORM_C1),
		BVBLENDMATCH(ONLY_A, INV_A2, NORM_C2),

		BVBLENDMODE(INVERSED, DISABLE),	/* K0/K3 */
		BVBLENDMODE(INVERSED, ENABLE)	/* K1/K2 */
	},

	/* color factor: 00 11 01 A:(1-As,Ad)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 00 11 10 A:(1-As,Cs)=1-As
	   alpha factor: 1-As ==> 00 11 00 or 00 11 10 */
	{
		BVBLENDMATCH(ONLY_A, INV_A2, NORM_C1),
		BVBLENDMATCH(ONLY_A, INV_A2, NORM_C2),

		BVBLENDMODE(INVERSED, DISABLE),	/* K0/K3 */
		BVBLENDMODE(INVERSED, ENABLE)	/* K1/K2 */
	},

	/* color factor: 00 11 11 A:(1-As,As)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/**********************************************************************/
	/* color factor: 01 00 00 MIN:(1-Cd,Cd) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 00 01 MIN:(1-Cd,Ad) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 00 10 MIN:(1-Cd,Cs) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 00 11 MIN:(1-Cd,As) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 01 00 MIN:(1-Ad,Cd) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 01 01 MIN:(1-Ad,Ad) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 01 10 MIN:(1-Ad,Cs) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 01 11 MIN:(1-Ad,As)
	   alpha factor: one ==> 11 11 11 */
	{
		0x3F,
		0x3F,

		BVBLENDMODE(SATURATED_DEST_ALPHA, DISABLE),	/* K0/K3 */
		BVBLENDMODE(SATURATED_ALPHA, DISABLE)		/* K1/K2 */
	},

	/* color factor: 01 10 00 MIN:(1-Cs,Cd) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 10 01 MIN:(1-Cs,Ad) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 10 10 MIN:(1-Cs,Cs) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 10 11 MIN:(1-Cs,As) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 11 00 MIN:(1-As,Cd) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 11 01 MIN:(1-As,Ad)
	   alpha factor: one ==> 11 11 11 */
	{
		0x3F,
		0x3F,

		BVBLENDMODE(SATURATED_ALPHA, DISABLE),		/* K0/K3 */
		BVBLENDMODE(SATURATED_DEST_ALPHA, DISABLE)	/* K1/K2 */
	},

	/* color factor: 01 11 10 MIN:(1-As,Cs) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 01 11 11 MIN:(1-As,As) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/**********************************************************************/
	/* color factor: 10 00 00 MAX:(1-Cd,Cd) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 00 01 MAX:(1-Cd,Ad) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 00 10 MAX:(1-Cd,Cs) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 00 11 MAX:(1-Cd,As) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 01 00 MAX:(1-Ad,Cd) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 01 01 MAX:(1-Ad,Ad) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 01 10 MAX:(1-Ad,Cs) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 01 11 MAX:(1-Ad,As) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 10 00 MAX:(1-Cs,Cd) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 10 01 MAX:(1-Cs,Ad) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 10 10 MAX:(1-Cs,Cs) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 10 11 MAX:(1-Cs,As) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 11 00 MAX:(1-As,Cd) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 11 01 MAX:(1-As,Ad) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 11 10 MAX:(1-As,Cs) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 10 11 11 MAX:(1-As,As) ==> not supported
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/**********************************************************************/
	/* color factor: 11 00 00 C:(1-Cd,Cd)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 11 00 01 C:(1-Cd,Ad)=1-Cd
	   alpha factor: 1-Ad ==> 00 01 00 or 00 01 10 */
	{
		BVBLENDMATCH(ONLY_A, INV_A1, NORM_C1),
		BVBLENDMATCH(ONLY_A, INV_A1, NORM_C2),

		BVBLENDMODE(COLOR_INVERSED, ENABLE),	/* K0/K3 */
		BVBLENDMODE(COLOR_INVERSED, DISABLE)	/* K1/K2 */
	},

	/* color factor: 11 00 10 C:(1-Cd,Cs)=undefined
	   alpha factor: N/A */
	{
		BVBLENDUNDEFINED()
	},

	/* color factor: 11 00 11 C:(1-Cd,As)=1-Cd
	   alpha factor: 1-Ad ==> 00 01 00 or 00 01 10 */
	{
		BVBLENDMATCH(ONLY_A, INV_A1, NORM_C1),
		BVBLENDMATCH(ONLY_A, INV_A1, NORM_C2),

		BVBLENDMODE(COLOR_INVERSED, ENABLE),	/* K0/K3 */
		BVBLENDMODE(COLOR_INVERSED, DISABLE)	/* K1/K2 */
	},

	/* color factor: 11 01 00 C:(1-Ad,Cd)=Cd
	   alpha factor: Ad ==> 00 00 01 or 00 10 01 */
	{
		BVBLENDMATCH(ONLY_A, INV_C1, NORM_A1),
		BVBLENDMATCH(ONLY_A, INV_C2, NORM_A1),

		BVBLENDMODE(COLOR, ENABLE),		/* K0/K3 */
		BVBLENDMODE(COLOR, DISABLE)		/* K1/K2 */
	},

	/* color factor: 11 01 01 C:(1-Ad,Ad)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 11 01 10 C:(1-Ad,Cs)=Cs
	   alpha factor: As ==> 00 00 11 or 00 10 11 */
	{
		BVBLENDMATCH(ONLY_A, INV_C1, NORM_A2),
		BVBLENDMATCH(ONLY_A, INV_C2, NORM_A2),

		BVBLENDMODE(COLOR, DISABLE),		/* K0/K3 */
		BVBLENDMODE(COLOR, ENABLE)		/* K1/K2 */
	},

	/* color factor: 11 01 11 C:(1-Ad,As)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 11 10 00 C:(1-Cs,Cd)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 11 10 01 C:(1-Cs,Ad)=1-Cs
	   alpha factor: 1-As ==> 00 11 00 or 00 11 10 */
	{
		BVBLENDMATCH(ONLY_A, INV_A2, NORM_C1),
		BVBLENDMATCH(ONLY_A, INV_A2, NORM_C2),

		BVBLENDMODE(COLOR_INVERSED, DISABLE),	/* K0/K3 */
		BVBLENDMODE(COLOR_INVERSED, ENABLE)	/* K1/K2 */
	},

	/* color factor: 11 10 10 C:(1-Cs,Cs)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 11 10 11 C:(1-Cs,As)=1-Cs
	   alpha factor: 1-As ==> 00 11 00 or 00 11 10 */
	{
		BVBLENDMATCH(ONLY_A, INV_A2, NORM_C1),
		BVBLENDMATCH(ONLY_A, INV_A2, NORM_C2),

		BVBLENDMODE(COLOR_INVERSED, DISABLE),	/* K0/K3 */
		BVBLENDMODE(COLOR_INVERSED, ENABLE)	/* K1/K2 */
	},

	/* color factor: 11 11 00 C:(1-As,Cd)=Cd
	   alpha factor: Ad ==> 00 00 01 or 00 10 01 */
	{
		BVBLENDMATCH(ONLY_A, INV_C1, NORM_A1),
		BVBLENDMATCH(ONLY_A, INV_C2, NORM_A1),

		BVBLENDMODE(COLOR, ENABLE),		/* K0/K3 */
		BVBLENDMODE(COLOR, DISABLE)		/* K1/K2 */
	},

	/* color factor: 11 11 01 C:(1-As,Ad)=undefined
	   alpha factor: N/A */
	{ BVBLENDUNDEFINED() },

	/* color factor: 11 11 10 C:(1-As,Cs)=Cs
	   alpha factor: As ==> 00 00 11 or 00 10 11 */
	{
		BVBLENDMATCH(ONLY_A, INV_C1, NORM_A2),
		BVBLENDMATCH(ONLY_A, INV_C2, NORM_A2),

		BVBLENDMODE(COLOR, DISABLE),		/* K0/K3 */
		BVBLENDMODE(COLOR, ENABLE)		/* K1/K2 */
	},

	/* color factor: 11 11 11 C:(1-As,As)=one
	   alpha factor: one ==> 11 11 11 */
	{
		0x3F,
		0x3F,

		BVBLENDMODE(ONE, DISABLE),	/* K0/K3 */
		BVBLENDMODE(ONE, DISABLE)	/* K1/K2 */
	}
};

static enum bverror parse_blend(struct bvbltparams *bltparams,
	enum bvblend blend, struct bv_alpha *bva)
{
	enum bverror res;
	uint32_t global;
	uint32_t k1, k2, k3, k4;
	struct bvblendxlate *dstxlate;
	struct bvblendxlate *srcxlate;

	if ((blend & BVBLENDDEF_REMOTE) != 0) {
		fprintf(stderr, "%s(%d): remote alpha not supported\n",
			__FUNCTION__, __LINE__);
		fflush(stderr);
		res = BVERR_BLEND;
		goto exit;
	}

	global = (blend & BVBLENDDEF_GLOBAL_MASK) >> BVBLENDDEF_GLOBAL_SHIFT;

	switch (global) {
	case (BVBLENDDEF_GLOBAL_NONE >> BVBLENDDEF_GLOBAL_SHIFT):
		bva->src_global_alpha_mode = AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_NORMAL;
		bva->dst_global_alpha_mode = AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_NORMAL;
		break;

	case (BVBLENDDEF_GLOBAL_UCHAR >> BVBLENDDEF_GLOBAL_SHIFT):
		bva->src_global_color =
		bva->dst_global_color =
			((uint32_t) bltparams->globalalpha.size8) << 24;

		bva->src_global_alpha_mode = AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_GLOBAL;
		bva->dst_global_alpha_mode = AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_GLOBAL;
		break;

	case (BVBLENDDEF_GLOBAL_FLOAT >> BVBLENDDEF_GLOBAL_SHIFT):
		bva->src_global_color =
		bva->dst_global_color =
			((uint32_t) ((uint8_t) (255.0f * bltparams->globalalpha.fp))) << 24;

		bva->src_global_alpha_mode = AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_GLOBAL;
		bva->dst_global_alpha_mode = AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_GLOBAL;
		break;

	default:
		fprintf(stderr, "%s(%d): invalid global alpha mode.\n",
			__FUNCTION__, __LINE__);
		fflush(stderr);
		res = BVERR_BLEND;
		goto exit;
	}

	/*
		Co = K1 x Cd + K2 x Cs
		Ao = K3 x Ad + K4 x As
	*/

	k1 = (blend >> 18) & 0x3F;
	k2 = (blend >> 12) & 0x3F;
	k3 = (blend >>  6) & 0x3F;
	k4 =  blend        & 0x3F;

	dstxlate = &blendxlate[k1];
	srcxlate = &blendxlate[k2];

	if (((k3 != dstxlate->match1) && (k3 != dstxlate->match2)) ||
		((k4 != srcxlate->match1) && (k4 != srcxlate->match2))) {
		fprintf(stderr, "%s(%d): not supported coefficient combination.\n",
			__FUNCTION__, __LINE__);
		fflush(stderr);
		res = BVERR_BLEND;
		goto exit;
	}

	bva->dst_factor_mode = dstxlate->dst_factor_mode;
	bva->dst_alpha_factor = dstxlate->dst_alpha_factor;

	bva->src_factor_mode = srcxlate->src_factor_mode;
	bva->src_alpha_factor = srcxlate->src_alpha_factor;

	bva->src_inverse_alpha = AQDE_ALPHA_MODES_SRC_ALPHA_MODE_NORMAL;
	bva->dst_inverse_alpha = AQDE_ALPHA_MODES_DST_ALPHA_MODE_NORMAL;

	res = BVERR_NONE;

exit:
	return res;
}

static enum bverror fill(struct bvbltparams *bltparams)
{
	int32_t res;

	uint32_t buffer[32 * 2];
	uint32_t *head, *tail;
	int count;

	uint32_t swizzle, format;
	uint32_t fillcolor;
	uint8_t use_src = 0, use_dest = 0;
	int unmap_dest = 0;
	int k = 0;

	int l, t, r, b;

	struct blt blt = {0};
	struct bvsurfgeom *destgeom = bltparams->dstgeom;
	struct bvrect *destrect = &bltparams->dstrect;

	swizzle = CONVERT_DEST_SWZZL(destgeom->format);
	if (swizzle == 0xFFFFFFFF) {
		fprintf(stderr, "%s(%d): invalid format (%d)\n", __FUNCTION__, __LINE__, destgeom->format);
		fflush(stderr);
		res = BVERR_DSTGEOM_FORMAT;
		goto exit;
	}

	format = CONVERT_DEST_FMT(destgeom->format);
	if (format == 0xFFFFFFFF) {
		fprintf(stderr, "%s(%d): invalid format (%d)\n", __FUNCTION__, __LINE__, destgeom->format);
		fflush(stderr);
		res = BVERR_DSTGEOM_FORMAT;
		goto exit;
	}

	if (bltparams->dstdesc->map == NULL) {
		res = bv_map(bltparams->dstdesc);
		if (res != 0) {
			goto exit;
		}
		unmap_dest = 1;
	}

	fillcolor = * (uint32_t *) bltparams->src1.desc->virtaddr;

	GET_2D_RESRC_USAGE(bltparams->op.rop, bltparams->op.rop, use_src, use_dest);

	l = destrect->left;
	t = destrect->top;
	r = destrect->left + destrect->width;
	b = destrect->top + destrect->height;

	head = tail = buffer;

	*tail++ = LS(AQPipeSelectRegAddrs, 1);
	*tail++ = CONFIG_GPU_PIPE(PIPE2D);

	*tail++ = LS(AQDESrcRotationConfigRegAddrs, 1);
	*tail++ =
		CONFIG_SRC_ROT_MODE(NORMAL) |
		CONFIG_SRC_ROT_WIDTH(destgeom->width);

	*tail++ = LS(AQDESrcRotationHeightRegAddrs, 1);
	*tail++ = CONFIG_SRC_ROT_HEIGHT(destgeom->height);

	*tail++ = LS(AQDEDestAddressRegAddrs, 1);
	*tail++ = (uint32_t) bltparams->dstdesc->map;
	blt.offset[k++] = tail - head;

	*tail++ = LS(AQDEDestStrideRegAddrs, 1);
	*tail++ = destgeom->virtstride;

	*tail++ = LS(AQDEDestRotationConfigRegAddrs, 1);
	*tail++ =
		CONFIG_DEST_ROT_MODE(NORMAL) |
		CONFIG_DEST_ROT_WIDTH(destgeom->width);

	*tail++ = LS(AQDEDestConfigRegAddrs, 1);
	*tail++ =
		CONFIG_DEST_CMD(CLEAR) |
		CONFIG_DEST_SWIZZLE(swizzle) |
		CONFIG_DEST_FMT(format);

	*tail++ = LS((AQDEDstRotationHeightRegAddrs), 1);
	*tail++ = destgeom->height;

	*tail++ = LS(AQDEClipTopLeftRegAddrs, 1);
	*tail++ = CONFIG_CLIP_LFTTOP(l, t);
	*tail++ = LS(AQDEClipBottomRightRegAddrs, 1);
	*tail++ = CONFIG_CLIP_RHTBTM(r, b);

	*tail++ = LS(AQDEClearPixelValue32RegAddrs, 1);
	*tail++ = fillcolor;

	if (use_src || use_dest) {
		*tail++ = LS(AQFlushRegAddrs, 1);
		*tail++ = CONFIG_PE2DCACHE_FLUSH();
	}

	*tail++ = LS(AQDERopRegAddrs, 1);
	*tail++ =
		CONFIG_ROP_TYPE(AQDE_ROP_TYPE_ROP3) |
		CONFIG_ROP_FORGND(bltparams->op.rop);

	*tail++ = CONFIG_START_DE(1);
	*tail++ = 0xC0FFEE;
	*tail++ = CONFIG_START_DE_LFTTOP(l, t);
	*tail++ = CONFIG_START_DE_RGHBTM(r, b);

	*tail++ = LS(AQFlushRegAddrs, 1);
	*tail++ = CONFIG_PE2DCACHE_FLUSH();

	count = tail - head;
	if (count > COUNTOF(buffer)) {
		fprintf(stderr, "%s(%d): !!! buffer overrun (%d) !!!\n",
			__FUNCTION__, __LINE__, count);
		fflush(stderr);
		res = BVERR_OOM;
		goto exit;
	}

	blt.cmdbuf = head;
	blt.cmdlen = count * sizeof(uint32_t);

	res = ioctl(fd, BLT, (uint32_t) &blt);
	if (res != 0) {
		fprintf(stderr, "%s(%d): ioctl failed\n", __FUNCTION__, __LINE__);
		fflush(stderr);
		res = BVERR_UNK;
		goto exit;
	}

	/* no errors, so exit */
	res = BVERR_NONE;

exit:
	if (unmap_dest) bv_unmap(bltparams->dstdesc);
	return res;
}

static enum bverror blit(struct bvbltparams *bltparams)
{
	int32_t res;

	uint32_t buffer[128 * 2];
	uint32_t *head, *tail;
	int count;

	int i, k = 0;
	uint32_t index;
	uint32_t src_swizzle, src_format;
	uint32_t dst_swizzle, dst_format;
	uint8_t use_src = 0, use_dest = 0;
	uint8_t rop_fg, rop_bg;
	int l, t, r, b;
	int unmap_dest = 0, unmap_src[2] = {0};

	int enable_blend;
	struct bv_alpha bva = {0};

	struct blt blt = {0};
	struct bvsurfgeom *destgeom = bltparams->dstgeom;
	struct bvrect *destrect = &bltparams->dstrect;

	struct bvbuffdesc *srcdesc[2];
	struct bvsurfgeom *srcgeom[2];
	struct bvrect *srcrect[2];

	dst_swizzle = CONVERT_DEST_SWZZL(destgeom->format);
	if (dst_swizzle == 0xFFFFFFFF) {
		fprintf(stderr, "%s(%d): invalid format (%d)\n", __FUNCTION__, __LINE__, destgeom->format);
		fflush(stderr);
		res = BVERR_DSTGEOM_FORMAT;
		goto exit;
	}

	dst_format = CONVERT_DEST_FMT(destgeom->format);
	if (dst_format == 0xFFFFFFFF) {
		fprintf(stderr, "%s(%d): invalid format (%d)\n", __FUNCTION__, __LINE__, destgeom->format);
		fflush(stderr);
		res = BVERR_DSTGEOM_FORMAT;
		goto exit;
	}

	enable_blend = (bltparams->flags == BVFLAG_BLEND);
	if (enable_blend) {
		res = parse_blend(bltparams, bltparams->op.blend, &bva);
		if (res != BVERR_NONE) {
			goto exit;
		}
	}

	if ((destgeom->format & OCDFMTDEF_NON_PREMULT) != 0) {
		bva.dst_premul_dst_alpha = AQDE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_ENABLE;
		bva.dst_demul_dst_alpha = AQDE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_ENABLE;
	} else {
		bva.dst_premul_dst_alpha = AQDE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_DISABLE;
		bva.dst_demul_dst_alpha = AQDE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_DISABLE;
	}

	bva.src_premul_global_mode = AQDE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_DISABLE;

	l = destrect->left;
	t = destrect->top;
	r = destrect->left + destrect->width;
	b = destrect->top + destrect->height;

	srcdesc[0] = bltparams->src1.desc;
	srcdesc[1] = bltparams->src2.desc;

	srcgeom[0] = bltparams->src1geom;
	srcgeom[1] = bltparams->src2geom;

	srcrect[0] = &bltparams->src1rect;
	srcrect[1] = &bltparams->src2rect;

	head = tail = buffer;

	*tail++ = LS(AQPipeSelectRegAddrs, 1);
	*tail++ = CONFIG_GPU_PIPE(PIPE2D);

	for (i = 0, index = 0; i < 2; i += 1) {
		if (srcdesc[i] == NULL) {
			continue;
		}

		src_swizzle = CONVERT_SRC_SWZZL(srcgeom[i]->format);
		if (src_swizzle == 0xFFFFFFFF) {
			fprintf(stderr, "%s(%d): invalid format (%d)\n",
				__FUNCTION__, __LINE__, srcgeom[i]->format);
			fflush(stderr);
			i == 0 ? (res = BVERR_SRC1GEOM_FORMAT) : (res = BVERR_SRC2GEOM_FORMAT);
			goto exit;
		}

		src_format = CONVERT_SRC_GCFMT(srcgeom[i]->format);
		if (src_format == 0xFFFFFFFF) {
			fprintf(stderr, "%s(%d): invalid format (%d)\n",
				__FUNCTION__, __LINE__, srcgeom[i]->format);
			fflush(stderr);
			i == 0 ? (res = BVERR_SRC1GEOM_FORMAT) : (res = BVERR_SRC2GEOM_FORMAT);
			goto exit;
		}

		if (srcdesc[i]->map == NULL) {
			res = bv_map(srcdesc[i]);
			if (res != 0)
				goto exit;
			unmap_src[i] = 1;
		}

		if (enable_blend) {
			rop_fg = 0xCC;
			rop_bg = 0xCC;
		} else {
			rop_fg = bltparams->op.rop;
			rop_bg = bltparams->op.rop;
		}

		GET_2D_RESRC_USAGE(rop_fg, rop_bg, use_src, use_dest);

		bva.src_premul_src_alpha
			= ((srcgeom[i]->format & OCDFMTDEF_NON_PREMULT) != 0)
				? AQDE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_ENABLE
				: AQDE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_DISABLE;

		*tail++ = LS((gcregDESrcAddressRegAddrs + index), 1);
		*tail++ = (uint32_t) srcdesc[i]->map;
		blt.offset[k++] = tail - head;

		*tail++ = LS((gcregDESrcStrideRegAddrs + index), 1);
		*tail++ = srcgeom[i]->virtstride;

		*tail++ = LS((gcregDESrcRotationConfigRegAddrs + index), 1);
		*tail++ =
			CONFIG_MLTSRC_ROT_MODE(NORMAL) |
			CONFIG_MLTSRC_ROT_WIDTH(srcrect[i]->width);

		*tail++ = LS((gcregDESrcConfigRegAddrs + index), 1);
		*tail++ =
			CONFIG_MLTSRC_LOC(MEMORY) |
			CONFIG_MLTSRC_FMT(src_format) |
			CONFIG_MLTSRC_SWIZZLE(src_swizzle);

		*tail++ = LS((gcregDESrcOriginRegAddrs + index), 1);
		*tail++ =
			CONFIG_MLTSRC_ORIGIN(srcrect[i]->top, srcrect[i]->left);

		*tail++ = LS((gcregDESrcSizeRegAddrs + index), 1);
		*tail++ =
			CONFIG_MLTSRC_SIZE(srcrect[i]->left + srcrect[i]->width,
					srcrect[i]->top + srcrect[i]->height);

		*tail++ = LS((gcregDERopRegAddrs + index), 1);
		*tail++ =
			CONFIG_MLTSRC_ROP_TYPE(GCREG_DE_ROP_TYPE_ROP4) |
			CONFIG_MLTSRC_ROP_BCKGND(rop_bg) |
			CONFIG_MLTSRC_ROP_FORGND(rop_fg);

		*tail++ = LS((gcregDESrcRotationHeightRegAddrs + index), 1);
		*tail++ = srcrect[i]->height;

		/* blend */
		if (enable_blend && (i > 0)) {
			*tail++ = LS(gcregDEAlphaControlRegAddrs + index, 1);
			*tail++ = CONFIG_ALPHA_CTRL(ON);

			*tail++ = LS(gcregDEAlphaModesRegAddrs + index, 1);
			*tail++ =
				SETFIELD(0, AQDE_ALPHA_MODES, SRC_ALPHA_MODE, bva.src_inverse_alpha) |
				SETFIELD(0, AQDE_ALPHA_MODES, DST_ALPHA_MODE, bva.dst_inverse_alpha) |
				SETFIELD(0, AQDE_ALPHA_MODES, GLOBAL_SRC_ALPHA_MODE, bva.src_global_alpha_mode) |
				SETFIELD(0, AQDE_ALPHA_MODES, GLOBAL_DST_ALPHA_MODE, bva.dst_global_alpha_mode) |
				SETFIELD(0, AQDE_ALPHA_MODES, SRC_BLENDING_MODE, bva.src_factor_mode) |
				SETFIELD(0, AQDE_ALPHA_MODES, DST_BLENDING_MODE, bva.dst_factor_mode) |
				SETFIELD(0, AQDE_ALPHA_MODES, SRC_ALPHA_FACTOR, bva.src_alpha_factor) |
				SETFIELD(0, AQDE_ALPHA_MODES, DST_ALPHA_FACTOR, bva.dst_alpha_factor);

			if (bva.src_global_alpha_mode != AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_NORMAL) {
				*tail++ = LS(gcregDEGlobalSrcColorRegAddrs + index, 1);
				*tail++ = bva.src_global_color;
			}

			if (bva.dst_global_alpha_mode != AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_NORMAL) {
				*tail++ = LS(gcregDEGlobalDestColorRegAddrs + index, 1);
				*tail++ = bva.dst_global_color;
			}
		} else {
			*tail++ = LS(gcregDEAlphaControlRegAddrs + index, 1);
			*tail++ = CONFIG_ALPHA_CTRL(OFF);
		}

		*tail++ = LS(gcregDEColorMultiplyModesRegAddrs + index, 1);
		*tail++ =
			SETFIELD(0, AQDE_COLOR_MULTIPLY_MODES, SRC_PREMULTIPLY, bva.src_premul_src_alpha) |
			SETFIELD(0, AQDE_COLOR_MULTIPLY_MODES, DST_PREMULTIPLY, bva.dst_premul_dst_alpha) |
			SETFIELD(0, AQDE_COLOR_MULTIPLY_MODES, SRC_GLOBAL_PREMULTIPLY, bva.src_premul_global_mode) |
			SETFIELD(0, AQDE_COLOR_MULTIPLY_MODES, DST_DEMULTIPLY, bva.dst_demul_dst_alpha);

		index += 1;
	}

	if (index == 0) {
		fprintf(stderr, "%s(%d): no source specified\n",
			__FUNCTION__, __LINE__);
		fflush(stderr);
		res = BVERR_UNK;
		goto exit;
	}

	if (bltparams->dstdesc->map == NULL) {
		res = bv_map(bltparams->dstdesc);
		if (res != 0)
			goto exit;
		unmap_dest = 1;
	}

	*tail++ = LS(AQDEDestAddressRegAddrs, 1);
	*tail++ = (uint32_t) bltparams->dstdesc->map;
	blt.offset[k++] = tail - head;

	*tail++ = LS(AQDEDestStrideRegAddrs, 1);
	*tail++ = destgeom->virtstride;

	*tail++ = LS(AQDEDestRotationConfigRegAddrs, 1);
	*tail++ =
		CONFIG_DEST_ROT_MODE(NORMAL) |
		CONFIG_DEST_ROT_WIDTH(destgeom->width);

	*tail++ = LS(AQDEDestConfigRegAddrs, 1);
	*tail++ =
		((index == 1)
			? CONFIG_DEST_CMD(BIT_BLT)
			: CONFIG_DEST_CMD(MULTI_SOURCE_BLT)) |
		CONFIG_DEST_SWIZZLE(dst_swizzle) |
		CONFIG_DEST_FMT(dst_format);

	*tail++ = LS((AQDEDstRotationHeightRegAddrs), 1);
	*tail++ = destgeom->height;

	*tail++ = LS(AQDEClipTopLeftRegAddrs, 1);
	*tail++ = CONFIG_CLIP_LFTTOP(l, t);
	*tail++ = LS(AQDEClipBottomRightRegAddrs, 1);
	*tail++ = CONFIG_CLIP_RHTBTM(r, b);

	if (index > 1 ) {
		*tail++ = LS(gcregDEMultiSourceRegAddrs, 1);
		*tail++ = CONFIG_MLTSRC_CTRL(index - 1);
	}

	*tail++ = CONFIG_START_DE(1);
	*tail++ = 0xC0FFEE;
	*tail++ = CONFIG_START_DE_LFTTOP(l, t);
	*tail++ = CONFIG_START_DE_RGHBTM(r, b);

	*tail++ = LS(AQFlushRegAddrs, 1);
	*tail++ = CONFIG_PE2DCACHE_FLUSH();

	count = tail - head;
	if (count > COUNTOF(buffer)) {
		fprintf(stderr, "%s(%d): !!! buffer overrun (%d) !!!\n",
			__FUNCTION__, __LINE__, count);
		fflush(stderr);
		res = BVERR_OOM;
		goto exit;
	}

	blt.cmdbuf = head;
	blt.cmdlen = count * sizeof(uint32_t);

	res = ioctl(fd, BLT, (uint32_t) &blt);
	if (res != 0) {
		fprintf(stderr, "%s(%d): ioctl failed\n", __FUNCTION__, __LINE__);
		fflush(stderr);
		res = BVERR_UNK;
		goto exit;
	}

	/* no errors, so exit */
	res = BVERR_NONE;

exit:
	for (i = 0; i < 2; i++)
		if (unmap_src[i]) bv_unmap(srcdesc[i]);
	if (unmap_dest) bv_unmap(bltparams->dstdesc);

	return res;
}

enum bverror bv_blt(struct bvbltparams *bltparams)
{
	int32_t res;

	if (bltparams == NULL) {
		res = BVERR_UNK;
		goto exit;
	}

	if (bltparams->structsize != sizeof(struct bvbltparams)) {
		res = BVERR_BUFFERDESC_VERS;
		goto exit;
	}

	if (bltparams->flags == BVFLAG_TILE_SRC1 ||
			bltparams->flags == BVFLAG_TILE_SRC2 ||
			bltparams->flags == BVFLAG_TILE_MASK) {
		/* tiling */
		res = BVERR_FLAGS;
	} else if ((bltparams->flags == BVFLAG_ROP) ||
		(bltparams->flags == BVFLAG_BLEND)) {
		if ((bltparams->src1rect.width == bltparams->dstrect.width) &&
				(bltparams->src1rect.height == bltparams->dstrect.height)) {
			res = blit(bltparams);
		} else if ((bltparams->src1rect.width == 1) &&
				(bltparams->src1rect.height == 1)) {
			res = fill(bltparams);
		} else {
			res = BVERR_FLAGS;
		}
	} else if (bltparams->flags == BVFLAG_FILTER) {
		res = BVERR_FLAGS;
	} else {
		/* error */
		res = BVERR_FLAGS;
	}

exit:
	return res;
}

enum bverror bv_unmap(struct bvbuffdesc *buffdesc)
{
	int32_t res;

	if (buffdesc == NULL) {
		res = BVERR_UNK;
		goto exit;
	}

	if (buffdesc->structsize != sizeof(struct bvbuffdesc)) {
		res = BVERR_BUFFERDESC_VERS;
		goto exit;
	}

	res = ioctl(fd, UMAP, buffdesc);
	if ((res == -1) || (buffdesc->map == NULL)) {
		res = BVERR_UNK;
		goto exit;
	}

	res = BVERR_NONE;

exit:
	return res;
}
