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
 *     * Neither the name of Texas Instruments, Inc. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Texas Instruments, Inc. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#include "bvinternal.h"
#include "ocd.h"
#include "aqcmd.h"
#include "aqcommon.h"
#include "aqhostiface.h"
#include "aqdma.h"
#include "aqde.h"
#include "_bv.h"

#define __GCSTART(reg_field) (0 ? reg_field)
#define __GCEND(reg_field) (1 ? reg_field)
#define __GCGETSIZE(reg_field) \
		(__GCEND(reg_field) - __GCSTART(reg_field) + 1)
#define __GCALIGN(data, reg_field) \
			(((uint32_t) (data)) << __GCSTART(reg_field))
#define __GCMASK(reg_field) ((uint32_t) ((__GCGETSIZE(reg_field) == 32) ?  ~0 \
	: (~(~0 << __GCGETSIZE(reg_field)))))
#define SETFIELDVAL(data, reg, field, value) \
( \
    (((uint32_t) (data)) \
	& ~__GCALIGN(__GCMASK(reg##_##field), reg##_##field)) \
	|  __GCALIGN(reg##_##field##_##value \
	& __GCMASK(reg##_##field), reg##_##field) \
)
#define SETFIELD(data, reg, field, value) \
( \
    (((uint32_t) (data)) \
	& ~__GCALIGN(__GCMASK(reg##_##field), reg##_##field)) \
	|  __GCALIGN((uint32_t) (value) \
	& __GCMASK(reg##_##field), reg##_##field) \
)

#define GET_2D_RESRC_USAGE(fg_rop, bg_rop, src_trans, use_src, use_pattern, use_dest) \
	if (use_src != NULL) { \
		uint8_t target_only = \
		((fg_rop == 0x00) && (bg_rop == 0x00)) ||  /* Blackness.    */ \
		((fg_rop == 0x55) && (bg_rop == 0x55)) ||  /* Invert.       */ \
		((fg_rop == 0xAA) && (bg_rop == 0xAA)) ||  /* No operation. */ \
		((fg_rop == 0xFF) && (bg_rop == 0xFF));    /* Whiteness.    */ \
 \
		*use_src = !target_only && \
				((((fg_rop >> 2) & 0x33) != (fg_rop & 0x33)) || \
				(((bg_rop >> 2) & 0x33) != (bg_rop & 0x33))); \
	} \
\
	if (use_pattern != NULL) { \
		*use_pattern = (((fg_rop >> 4) & 0x0F) != (fg_rop & 0x0F)) || \
				(((bg_rop >> 4) & 0x0F) != (bg_rop & 0x0F)); \
	} \
\
	if (use_dest != NULL) { \
		*use_dest = (((fg_rop >> 1) & 0x55) != (fg_rop & 0x55)) || \
				(((bg_rop >> 1) & 0x55) != (bg_rop & 0x55)); \
	}

#define CONVERT_DEST_FMT(ocdfmt) \
	ocdfmt == OCDFMT_ARGB16 ? AQDE_DEST_CONFIG_FORMAT_R5G6B5 : \
	(ocdfmt == OCDFMT_ARGB24 ? AQDE_DEST_CONFIG_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_BGRA24 ? AQDE_DEST_CONFIG_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_RGBA24 ? AQDE_DEST_CONFIG_FORMAT_A8R8G8B8 : 0xFFFFFFFF)));

#define CONVERT_DEST_SWZZL(ocdfmt) \
	ocdfmt == OCDFMT_ARGB16 ? AQDE_DEST_CONFIG_SWIZZLE_ARGB : \
	(ocdfmt == OCDFMT_ARGB24 ? AQDE_DEST_CONFIG_SWIZZLE_ARGB : \
	(ocdfmt == OCDFMT_BGRA24 ? AQDE_DEST_CONFIG_SWIZZLE_BGRA : \
	(ocdfmt == OCDFMT_RGBA24 ? AQDE_DEST_CONFIG_SWIZZLE_RGBA : 0xFFFFFFFF)));

#define CONVERT_SRC_FMT(ocdfmt) \
	ocdfmt == OCDFMT_ARGB16 ? AQDE_SRC_CONFIG_SOURCE_FORMAT_R5G6B5 : \
	(ocdfmt == OCDFMT_ARGB24 ? AQDE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_BGRA24 ? AQDE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_RGBA24 ? AQDE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : 0xFFFFFFFF)));

#define CONVERT_SRC_SWZZL(ocdfmt) \
	ocdfmt == OCDFMT_ARGB16 ? AQDE_SRC_CONFIG_SWIZZLE_ARGB : \
	(ocdfmt == OCDFMT_ARGB24 ? AQDE_SRC_CONFIG_SWIZZLE_ARGB : \
	(ocdfmt == OCDFMT_BGRA24 ? AQDE_SRC_CONFIG_SWIZZLE_BGRA : \
	(ocdfmt == OCDFMT_RGBA24 ? AQDE_SRC_CONFIG_SWIZZLE_RGBA : 0xFFFFFFFF)));

#define CONVERT_SRC1_FMT(ocdfmt) \
	CONVERT_SRC_FMT(ocdfmt);

#define CONVERT_SRC2_FMT(ocdfmt) \
	CONVERT_SRC_FMT(ocdfmt);

#define CONVERT_SRC_GCFMT(ocdfmt) \
	ocdfmt == OCDFMT_ARGB16 ? GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_R5G6B5 : \
	(ocdfmt == OCDFMT_ARGB24 ? GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_BGRA24 ? GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : \
	(ocdfmt == OCDFMT_RGBA24 ? GCREG_DE_SRC_CONFIG_SOURCE_FORMAT_A8R8G8B8 : 0xFFFFFFFF)));

#define CONVERT_SRC1_GCFMT(ocdfmt) \
	CONVERT_SRC_GCFMT(ocdfmt);

#define CONVERT_SRC2_GCFMT(ocdfmt) \
	CONVERT_SRC_GCFMT(ocdfmt);

#define db(x) \
	fprintf(stdout, "%s(%d): %s=(%08ld)\n", __FUNCTION__, __LINE__, #x, (unsigned long)x); \
	fflush(stdout);

#define dbx(x) \
	fprintf(stdout, "%s(%d): %s=(0x%08lx)\n", __FUNCTION__, __LINE__, #x, (unsigned long)x); \
	fflush(stdout);

#define dbs(x) \
	fprintf(stdout, "%s(%d): %s=(%s)\n", __FUNCTION__, __LINE__, #x, x); \
	fflush(stdout);

#define BLT _IOW('x', 100, uint32_t)
#define MAP _IOWR('x', 101, uint32_t)
#define UMAP _IOW('x', 102, uint32_t)
#define TEST _IOW('x', 104, uint32_t)
#define MAX_THRD 1
#define MAX_SRC 2
#define MAX_SRC_1PASS 4

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
extern int errno;

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
	int32_t r = -1, i = 0;
	int error;

	fprintf(stdout, "%s()::%d\n", __FUNCTION__, __LINE__); fflush(stdout);

	fd = open(file, O_RDWR);
	if (fd == -1)
		goto exit;

	for (i = 0; i < MAX_THRD; i++) {
		r = pthread_create(&id[i], NULL, thread, NULL);
		if (r != 0)
			goto e1;
	}

	/* no errors, so exit */
	goto exit;
e1:
	fprintf(stderr, "%s()::%d:error\n", __FUNCTION__, __LINE__); fflush(stderr);

	for (; i > 0; i--) {
		pthread_cancel(id[i - 1]);
	}

	close(fd);
	fd = 0;
exit:
	error = errno;
	if (error != 0)
		fprintf(stderr, "%s\n", (char *)strerror(error)); fflush(stderr);
	return;
}

extern void bv_exit(void)
{
	int32_t i = 0, r = 0;

	fprintf(stdout, "%s()::%d\n", __FUNCTION__, __LINE__); fflush(stdout);
	for (i = 0; i < MAX_THRD; i++) {
		if (id[i] != 0) {
			r = pthread_cancel(id[i]);
			if (r != 0) {
				fprintf(stderr, "%s\n", (char *)strerror(errno)); fflush(stderr);
			}
		}
	}

	if (fd != 0)
		close(fd);
}

enum bverror bv_map(struct bvbuffdesc *buffdesc)
{
	int32_t e = BVERR_UNK;
	int32_t r = -1;

	fprintf(stdout, "%s()::%d\n", __FUNCTION__, __LINE__); fflush(stdout);
	if (!buffdesc)
		goto e1;
	if (sizeof(*buffdesc) != sizeof(struct bvbuffdesc)) {
		e = BVERR_BUFFERDESC_VERS;
		goto e1;
	}

	r = ioctl(fd, MAP, buffdesc);
	if (r == -1 || buffdesc->map == NULL)
		goto e1;

	/* no errors, so exit */
	e = BVERR_NONE;
	goto exit;
e1:
	fprintf(stderr, "%s()::%d:error\n", __FUNCTION__, __LINE__); fflush(stderr);
exit:
	return e;
}

static enum bverror fill(struct bvbltparams *bltparams)
{
	int32_t e = BVERR_UNK, r = 0;
	uint32_t *cmdbuf = NULL, *tmp = NULL, *start = NULL, command = 0, swizzle = 0, format = 0, color;
	uint8_t use_src = 0, use_dest = 0, use_pattern = 0, rop_fg = 0, rop_bg = 0;
	int j = 0, k = 0;
	struct blt blt = {0};
	struct bvbltparams bltparam = {0};
	struct bvsurfgeom destgeom = {0};
	struct bvsurfgeom src1geom = {0};
	struct bvrect destrect = {0};
	struct bvrect src1rect = {0};
	struct bvbuffdesc destdesc = {0};
	struct bvbuffdesc src1desc = {0};

	bltparam = *bltparams;
	destdesc = *bltparam.dstdesc;
	destgeom = *bltparam.dstgeom;
	destrect = bltparam.dstrect;
	src1desc = *bltparam.src1.desc;
	src1geom = *bltparam.src1geom;
	src1rect = bltparam.src1rect;

	tmp = (uint32_t *)src1desc.virtaddr;
	color = (uint32_t)tmp[src1rect.left];

	rop_fg = rop_bg = 0xCC;
	command = AQDE_DEST_CONFIG_COMMAND_CLEAR;

	swizzle = CONVERT_DEST_SWZZL(destgeom.format);
	if (swizzle == 0xFFFFFFFF) {
		e = BVERR_DSTGEOM_FORMAT;
		goto exit;
	}

	format = CONVERT_DEST_FMT(destgeom.format);
	if (format == 0xFFFFFFFF) {
		e = BVERR_DSTGEOM_FORMAT;
		goto exit;
	}

	/* TODO: find a way to get the exact cmd size */
	r = posix_memalign((void **)&cmdbuf, getpagesize(), getpagesize());
	if (r != 0)
		goto exit;
	memset(cmdbuf, 0x0, getpagesize());

	start = cmdbuf;

	*cmdbuf++ = LS(AQ_PIPE_SELECT_Address, 1);
	*cmdbuf++ = CONFIG_GPU_PIPE(AQ_PIPE_SELECT_PIPE_PIPE2D);
	*cmdbuf++ = LS(AQDE_DEST_CONFIG_Address, 1);
	*cmdbuf++ =
		CONFIG_DEST_CMD(command) |
		CONFIG_DEST_SWIZZLE(swizzle) |
		CONFIG_DEST_FMT(format);

	*cmdbuf++ = LS(AQDE_DEST_ADDRESS_Address, 1);
	*cmdbuf++ = (uint32_t)destdesc.map; blt.offset[k] = cmdbuf - start; k++;

	*cmdbuf++ = LS(AQDE_DEST_STRIDE_Address, 1);
	*cmdbuf++ = destgeom.virtstride;

	*cmdbuf++ = LS(AQDE_CLIP_TOP_LEFT_Address, 1);
	*cmdbuf++ = CONFIG_CLIP_LFTTOP(destrect.left, destrect.top);
	*cmdbuf++ = LS(AQDE_CLIP_BOTTOM_RIGHT_Address, 1);
	*cmdbuf++ = CONFIG_CLIP_RHTBTM(destrect.left + destrect.width,
				       destrect.top + destrect.height);

	*cmdbuf++ = LS(AQDE_CLEAR_PIXEL_VALUE32_Address, 1);
	*cmdbuf++ = color;

	GET_2D_RESRC_USAGE(rop_fg, rop_bg, 0, &use_src, &use_pattern, &use_dest);

	if (use_src || use_dest) {
		*cmdbuf++ = LS(AQ_FLUSH_Address, 1);
		*cmdbuf++ = CONFIG_PE2DCACHE_FLUSH();
	}

	*cmdbuf++ = LS(AQDE_ROP_Address, 1);
	*cmdbuf++ =
		CONFIG_ROP_TYPE(AQDE_ROP_TYPE_ROP4) |
		CONFIG_ROP_BCKGND(rop_bg) |
		CONFIG_ROP_FORGND(rop_fg);

	*cmdbuf++ = LS(AQDE_SRC_ROTATION_CONFIG_Address, 1);
	*cmdbuf++ =
		CONFIG_SRC_ROT_MODE(AQDE_SRC_ROTATION_CONFIG_ROTATION_NORMAL) |
		CONFIG_SRC_ROT_WIDTH(src1geom.width);

	*cmdbuf++ = LS(AQDE_SRC_ROTATION_HEIGHT_Address, 1);
	*cmdbuf++ = CONFIG_SRC_ROT_HEIGHT(src1geom.height);

	*cmdbuf++ = LS(AQDE_SRC_CONFIG_Address, 1);
	*cmdbuf++ = CONFIG_SRC_LOCATION(AQDE_SRC_CONFIG_LOCATION_MEMORY);

	*cmdbuf++ = CONFIG_START_DE(AQ_COMMAND_START_DE_COMMAND_OPCODE_START_DE);
	*cmdbuf++ = 0xC0FFEE;
	*cmdbuf++ = CONFIG_CLIP_LFTTOP(destrect.left, destrect.top);
	*cmdbuf++ = CONFIG_CLIP_RHTBTM(destrect.left + destrect.width,
				       destrect.top + destrect.height);

	*cmdbuf++ = LS(AQ_EVENT_Address, 1);
	*cmdbuf++ =
		CONFIG_PE_EVENT(AQ_EVENT_PE_SRC_ENABLE) |
		CONFIG_PE_EVENT_ID(29);
	*cmdbuf++ = CONFIG_STOP_FE();
	*cmdbuf++ = 0xC0FFEE;

	blt.cmdbuf = start;
	blt.cmdlen = (uint32_t)(cmdbuf - start) * sizeof(uint32_t);

	r = ioctl(fd, BLT, (uint32_t)&blt);
	if (r != 0)
		goto exit;

	/* print out the command buffer */
	tmp = start;
	for (j = 0; j < (cmdbuf - start); j++) {
		fprintf(stdout, "%s()::%d:cmd=(0x%08lX) %d uva=(1x%08lX)\n",
			__func__, __LINE__, (unsigned long)*tmp, j+1, (unsigned long)tmp);
		tmp++;
	}
	fflush(stdout);

	/* no errors, so exit */
	e = BVERR_NONE;
	goto exit;
exit:
	free(start);
	return e;
}

static enum bverror blend(struct bvbltparams *bltparams)
{
	int32_t e = BVERR_UNK;
	uint32_t *cmdbuf = NULL, *start = NULL, *tmp;
	uint32_t command = 0, swizzle = 0, swzzl[MAX_SRC];
	uint32_t fmt = 0, format[MAX_SRC], srcmask = 0, src_current = 0;
	uint8_t use_src = 0, use_dest = 0, use_pattern = 0;
	uint8_t rop_fg[MAX_SRC] = {0}, rop_bg[MAX_SRC] = {0}, unmap_src[MAX_SRC] = {0}, unmap_dest = 0;
	int r = 0, i = 0, j = 0, k = 0;
	struct blt blt = {0};
	struct bvbltparams bltparam = {0};
	struct bvsurfgeom destgeom = {0};
	struct bvsurfgeom srcgeom[MAX_SRC];
	struct bvrect destrect = {0};
	struct bvrect srcrect[MAX_SRC];
	struct bvbuffdesc destdesc = {0};
	struct bvbuffdesc srcdesc[MAX_SRC];
	struct bv_alpha bva = {0};

	fprintf(stderr, "%s()::%d\n", __FUNCTION__, __LINE__); fflush(stderr);
	bltparam = *bltparams;
	destdesc = *bltparam.dstdesc;
	destgeom = *bltparam.dstgeom;
	destrect = bltparam.dstrect;

	srcdesc[0] = *bltparam.src1.desc;
	srcgeom[0] = *bltparam.src1geom;
	srcrect[0] = bltparam.src1rect;
	srcdesc[1] = *bltparam.src2.desc;
	srcgeom[1] = *bltparam.src2geom;
	srcrect[1] = bltparam.src2rect;

	if (destdesc.map == NULL) {
		e = bv_map(&destdesc);
		if (e != 0)
			goto exit;
		unmap_dest = 1;
	} /* need to unmap this later */

	/* TODO: need to roll back out on failure */
	/* TODO: need to unmap this before exit */
	/* TODO: create a bitfield for unmapping */
	for (i = 0; i < MAX_SRC; i++) {
		if (srcdesc[i].map == NULL) {
			e = bv_map(&srcdesc[i]);
			if (e != 0)
				goto exit;
			unmap_src[i] = 1;
		}
	}

	rop_fg[0] = rop_bg[0] = 0xCC;
	rop_fg[1] = rop_bg[1] = 0xCC;

	/* Not using colors here, just reset them. */
	bva.src_global_color = 0;
	bva.dst_global_color = 0;

	/* Source factor for SOURCE_OVER is 1. */
	bva.src_inverse_alpha = AQDE_ALPHA_MODES_SRC_ALPHA_MODE_NORMAL;
	bva.src_global_alpha_mode = AQDE_ALPHA_MODES_GLOBAL_SRC_ALPHA_MODE_NORMAL;
	bva.src_factor_mode = AQDE_ALPHA_MODES_SRC_BLENDING_MODE_ONE;
	bva.src_alpha_factor = AQDE_ALPHA_MODES_SRC_ALPHA_FACTOR_DISABLED;

	/* Destination factor for SOURCE_OVER is (1 - SrcAlpha). */
	bva.dst_inverse_alpha = AQDE_ALPHA_MODES_DST_ALPHA_MODE_INVERSED;
	bva.dst_global_alpha_mode = AQDE_ALPHA_MODES_GLOBAL_DST_ALPHA_MODE_NORMAL;
	bva.dst_factor_mode = AQDE_ALPHA_MODES_DST_BLENDING_MODE_NORMAL;
	bva.dst_alpha_factor = AQDE_ALPHA_MODES_DST_ALPHA_FACTOR_DISABLED;

	/* No premultiplication. */
	bva.src_premul_src_alpha = AQDE_COLOR_MULTIPLY_MODES_SRC_PREMULTIPLY_DISABLE;
	bva.dst_premul_dst_alpha = AQDE_COLOR_MULTIPLY_MODES_DST_PREMULTIPLY_DISABLE;
	bva.src_premul_global_mode = AQDE_COLOR_MULTIPLY_MODES_SRC_GLOBAL_PREMULTIPLY_DISABLE;
	bva.dst_demul_dst_alpha = AQDE_COLOR_MULTIPLY_MODES_DST_DEMULTIPLY_DISABLE;

	command = AQDE_DEST_CONFIG_COMMAND_BIT_BLT;

	swizzle = CONVERT_DEST_SWZZL(destgeom.format);
	if (swizzle == 0xFFFFFFFF) {
		e = BVERR_DSTGEOM_FORMAT;
		goto exit;
	}

	fmt = CONVERT_DEST_FMT(destgeom.format);
	if (fmt == 0xFFFFFFFF) {
		e = BVERR_DSTGEOM_FORMAT;
		goto exit;
	}

	/* TODO: find a way to get the exact cmd size */
	r = posix_memalign((void **)&cmdbuf, getpagesize(), getpagesize());
	if (r != 0)
		goto exit;
	memset(cmdbuf, 0x0, getpagesize());

	start = cmdbuf;

	*cmdbuf++ = LS(AQ_PIPE_SELECT_Address, 1);
	*cmdbuf++ = CONFIG_GPU_PIPE(AQ_PIPE_SELECT_PIPE_PIPE2D);
	*cmdbuf++ = LS(AQDE_DEST_CONFIG_Address, 1);
	*cmdbuf++ =
		CONFIG_DEST_CMD(command) |
		CONFIG_DEST_SWIZZLE(swizzle) |
		CONFIG_DEST_FMT(fmt);

	*cmdbuf++ = LS(AQDE_DEST_ADDRESS_Address, 1);
	*cmdbuf++ = (uint32_t)destdesc.map; blt.offset[k] = cmdbuf - start; k++;

	*cmdbuf++ = LS(AQDE_DEST_STRIDE_Address, 1);
	*cmdbuf++ = destgeom.virtstride;

	*cmdbuf++ = LS(AQDE_DEST_ROTATION_CONFIG_Address, 1);
	*cmdbuf++ =
		CONFIG_DEST_ROT_MODE(AQDE_DEST_ROTATION_CONFIG_ROTATION_NORMAL) |
		CONFIG_DEST_ROT_WIDTH(destgeom.width);

	*cmdbuf++ = LS(AQDE_CLIP_TOP_LEFT_Address, 1);
	*cmdbuf++ = CONFIG_CLIP_LFTTOP(destrect.left, destrect.top);
	*cmdbuf++ = LS(AQDE_CLIP_BOTTOM_RIGHT_Address, 1);
	*cmdbuf++ = CONFIG_CLIP_RHTBTM(destrect.left + destrect.width,
				       destrect.top + destrect.height);

	*cmdbuf++ = LS(AQ_FLUSH_Address, 1);
	*cmdbuf++ = CONFIG_PE2DCACHE_FLUSH();

	srcmask = 0x3;
	use_src = use_pattern = use_dest = src_current = 0;
	for (i = 0; i < MAX_SRC_1PASS; i++) {
		if (!(srcmask & (1 << i)))
			continue;

		GET_2D_RESRC_USAGE(rop_fg[i], rop_bg[i], 0, &use_src, &use_pattern, &use_dest);

		*cmdbuf++ = LS((GCREG_DE_SRC_ADDRESS_Address + i), 1);
		*cmdbuf++ = (uint32_t)srcdesc[i].map; blt.offset[k] = cmdbuf - start; k++;

		*cmdbuf++ = LS((GCREG_DE_SRC_STRIDE_Address + i), 1);
		*cmdbuf++ = srcgeom[i].virtstride;

		*cmdbuf++ = LS((GCREG_DE_SRC_ROTATION_CONFIG_Address + i), 1);
		*cmdbuf++ = CONFIG_MLTSRC_ROT_MODE(GCREG_DE_SRC_ROTATION_CONFIG_ROTATION_NORMAL);

		swzzl[i] = CONVERT_SRC_SWZZL(srcgeom[i].format);
		if (swzzl[i] == 0xFFFFFFFF) {
			i == 0 ? (e = BVERR_SRC1GEOM_FORMAT) : (e = BVERR_SRC2GEOM_FORMAT);
			goto exit;
		}

		format[i] = CONVERT_SRC_GCFMT(srcgeom[i].format);
		if (format[i] == 0xFFFFFFFF) {
			i == 0 ? (e = BVERR_SRC1GEOM_FORMAT) : (e = BVERR_SRC2GEOM_FORMAT);
			goto exit;
		}

		*cmdbuf++ = LS((GCREG_DE_SRC_CONFIG_Address + i), 1);
		*cmdbuf++ =
			CONFIG_MLTSRC_LOC(GCREG_DE_SRC_CONFIG_LOCATION_MEMORY) |
			CONFIG_MLTSRC_FMT(format[i]) |
			CONFIG_MLTSRC_SWIZZLE(swzzl[i]);

		*cmdbuf++ = LS((GCREG_DE_SRC_ORIGIN_Address + i), 1);
		*cmdbuf++ =
			CONFIG_MLTSRC_ORIGIN(srcrect[i].top, srcrect[i].left);

		*cmdbuf++ = LS((GCREG_DE_SRC_SIZE_Address + i), 1);
		*cmdbuf++ =
			CONFIG_MLTSRC_SIZE(srcrect[i].left + srcrect[i].width,
					   srcrect[i].top + srcrect[i].height);

		*cmdbuf++ = LS((GCREG_DE_ROP_Address + i), 1);
		*cmdbuf++ =
			CONFIG_MLTSRC_ROP_TYPE(GCREG_DE_ROP_TYPE_ROP4) |
			CONFIG_MLTSRC_ROP_BCKGND(rop_bg[i]) |
			CONFIG_MLTSRC_ROP_FORGND(rop_fg[i]);

		/* blend */
		*cmdbuf++ = LS(AQDE_ALPHA_CONTROL_Address, 1);
		*cmdbuf++ = CONFIG_ALPHA_CTRL(AQDE_ALPHA_CONTROL_ENABLE_ON);

		*cmdbuf++ = LS(AQDE_ALPHA_MODES_Address, 1);
		*cmdbuf++ =
			SETFIELD(0, AQDE_ALPHA_MODES, SRC_ALPHA_MODE, bva.src_inverse_alpha) |
			SETFIELD(0, AQDE_ALPHA_MODES, DST_ALPHA_MODE, bva.dst_inverse_alpha) |
			SETFIELD(0, AQDE_ALPHA_MODES, GLOBAL_SRC_ALPHA_MODE, bva.src_global_alpha_mode) |
			SETFIELD(0, AQDE_ALPHA_MODES, GLOBAL_DST_ALPHA_MODE, bva.dst_global_alpha_mode) |
			SETFIELD(0, AQDE_ALPHA_MODES, SRC_BLENDING_MODE, bva.src_factor_mode) |
			SETFIELD(0, AQDE_ALPHA_MODES, DST_BLENDING_MODE, bva.dst_factor_mode) |
			SETFIELD(0, AQDE_ALPHA_MODES, SRC_ALPHA_FACTOR, bva.src_alpha_factor) |
			SETFIELD(0, AQDE_ALPHA_MODES, DST_ALPHA_FACTOR, bva.dst_alpha_factor);

		*cmdbuf++ = LS(AQDE_GLOBAL_SRC_COLOR_Address, 1);
		*cmdbuf++ = bva.src_global_color;

		*cmdbuf++ = LS(AQDE_GLOBAL_DEST_COLOR_Address, 1);
		*cmdbuf++ = bva.dst_global_color;

		*cmdbuf++ = LS(AQDE_COLOR_MULTIPLY_MODES_Address, 1);
		*cmdbuf++ =
			SETFIELD(0, AQDE_COLOR_MULTIPLY_MODES, SRC_PREMULTIPLY, bva.src_premul_src_alpha) |
			SETFIELD(0, AQDE_COLOR_MULTIPLY_MODES, DST_PREMULTIPLY, bva.dst_premul_dst_alpha) |
			SETFIELD(0, AQDE_COLOR_MULTIPLY_MODES, SRC_GLOBAL_PREMULTIPLY, bva.src_premul_global_mode) |
			SETFIELD(0, AQDE_COLOR_MULTIPLY_MODES, DST_DEMULTIPLY, bva.dst_demul_dst_alpha);
		src_current++;
	}

	*cmdbuf++ = LS(GCREG_DE_MULTI_SOURCE_Address, 1);
	*cmdbuf++ = CONFIG_MLTSRC_CTRL(src_current - 1);

	*cmdbuf++ = CONFIG_START_DE(AQ_COMMAND_START_DE_COMMAND_OPCODE_START_DE);
	*cmdbuf++ = 0xC0FFEE;
	*cmdbuf++ = CONFIG_CLIP_LFTTOP(destrect.left, destrect.top);
	*cmdbuf++ = CONFIG_CLIP_RHTBTM(destrect.left + destrect.width,
				       destrect.top + destrect.height);

	*cmdbuf++ = LS(AQ_FLUSH_Address, 1);
	*cmdbuf++ = CONFIG_PE2DCACHE_FLUSH();

	*cmdbuf++ = LS(AQ_EVENT_Address, 1);
	*cmdbuf++ =
		CONFIG_PE_EVENT(AQ_EVENT_PE_SRC_ENABLE) |
		CONFIG_PE_EVENT_ID(29);
	*cmdbuf++ = CONFIG_STOP_FE();
	*cmdbuf++ = 0xC0FFEE;

	blt.cmdbuf = start;
	blt.cmdlen = (uint32_t)(cmdbuf - start) * sizeof(uint32_t);

	r = ioctl(fd, BLT, (uint32_t)&blt);
	if (r != 0)
		goto exit;

	/* print out the command buffer */
	tmp = start;
	for (j = 0; j < (cmdbuf - start); j++) {
		fprintf(stdout, "%s()::%d:cmd=(0x%08lX) %d uva=(1x%08lX)\n",
			__func__, __LINE__, (unsigned long)*tmp, j+1, (unsigned long)tmp);
		tmp++;
	}
	fflush(stdout);

	/* no errors, so exit */
	e = BVERR_NONE;
	goto exit;
exit:
	free(start);
	return e;
}

static enum bverror copy(struct bvbltparams *bltparams)
{
	int32_t e = BVERR_UNK, r = 0;
	uint32_t *cmdbuf = NULL, *tmp = NULL, *start = NULL, command = 0, swizzle = 0, format = 0;
	uint8_t use_src = 0, use_dest = 0, use_pattern = 0, rop_fg = 0, rop_bg = 0, unmap_src1 = 0, unmap_dest = 0;
	int j = 0, k = 0;
	struct blt blt = {0};
	struct bvbltparams bltparam = {0};
	struct bvsurfgeom destgeom = {0};
	struct bvsurfgeom src1geom = {0};
	struct bvrect destrect = {0};
	struct bvrect src1rect = {0};
	struct bvbuffdesc destdesc = {0};
	struct bvbuffdesc src1desc = {0};

	fprintf(stderr, "%s()::%d\n", __FUNCTION__, __LINE__); fflush(stderr);
	bltparam = *bltparams;
	destdesc = *bltparam.dstdesc;
	destgeom = *bltparam.dstgeom;
	destrect = bltparam.dstrect;
	src1desc = *bltparam.src1.desc;
	src1geom = *bltparam.src1geom;
	src1rect = bltparam.src1rect;

	if (destdesc.map == NULL) {
		e = bv_map(&destdesc);
		if (e != 0)
			goto exit;
		unmap_dest = 1;
	} /* need to unmap this later */

	if (src1desc.map == NULL) {
		e = bv_map(&src1desc);
		if (e != 0)
			goto exit;
		unmap_src1 = 1;
	} /* need to unmap this later */

	rop_fg = rop_bg = 0xCC;
	command = AQDE_DEST_CONFIG_COMMAND_BIT_BLT;

	swizzle = CONVERT_DEST_SWZZL(destgeom.format);
	if (swizzle == 0xFFFFFFFF) {
		e = BVERR_DSTGEOM_FORMAT;
		goto exit;
	}

	format = CONVERT_DEST_FMT(destgeom.format);
	if (format == 0xFFFFFFFF) {
		e = BVERR_DSTGEOM_FORMAT;
		goto exit;
	}

	/* TODO: find a way to get the exact cmd size */
	r = posix_memalign((void **)&cmdbuf, getpagesize(), getpagesize());
	if (r != 0)
		goto exit;
	memset(cmdbuf, 0x0, getpagesize());

	start = cmdbuf;

	*cmdbuf++ = LS(AQ_PIPE_SELECT_Address, 1);
	*cmdbuf++ = CONFIG_GPU_PIPE(AQ_PIPE_SELECT_PIPE_PIPE2D);
	*cmdbuf++ = LS(AQDE_DEST_CONFIG_Address, 1);
	*cmdbuf++ =
		CONFIG_DEST_CMD(command) |
		CONFIG_DEST_SWIZZLE(swizzle) |
		CONFIG_DEST_FMT(format);

	*cmdbuf++ = LS(AQDE_DEST_ADDRESS_Address, 1);
	*cmdbuf++ = (uint32_t)destdesc.map; blt.offset[k] = cmdbuf - start; k++;

	*cmdbuf++ = LS(AQDE_DEST_STRIDE_Address, 1);
	*cmdbuf++ = destgeom.virtstride;

	*cmdbuf++ = LS(AQDE_CLIP_TOP_LEFT_Address, 1);
	*cmdbuf++ = CONFIG_CLIP_LFTTOP(destrect.left, destrect.top);
	*cmdbuf++ = LS(AQDE_CLIP_BOTTOM_RIGHT_Address, 1);
	*cmdbuf++ = CONFIG_CLIP_RHTBTM(destrect.left + destrect.width,
				       destrect.top +  destrect.height);

	use_src = use_pattern = use_dest;

	GET_2D_RESRC_USAGE(rop_fg, rop_bg, 0, &use_src, &use_pattern, &use_dest);

	if (use_src || use_dest) {
		*cmdbuf++ = LS(AQ_FLUSH_Address, 1);
		*cmdbuf++ = CONFIG_PE2DCACHE_FLUSH();
	}

	*cmdbuf++ = LS(AQDE_ROP_Address, 1);
	*cmdbuf++ =
		CONFIG_ROP_TYPE(AQDE_ROP_TYPE_ROP4) |
		CONFIG_ROP_BCKGND(rop_bg) |
		CONFIG_ROP_FORGND(rop_fg);

	*cmdbuf++ = LS(AQDE_SRC_ORIGIN_Address, 1);
	*cmdbuf++ =
		CONFIG_SRC_ORIGIN(src1rect.left, src1rect.top);

	*cmdbuf++ = LS(AQDE_SRC_SIZE_Address, 1);
	*cmdbuf++ =
		CONFIG_SRC_SIZE(src1rect.left + src1rect.width,
				src1rect.top + src1rect.height);

	*cmdbuf++ = LS(AQDE_SRC_ADDRESS_Address, 1);
	*cmdbuf++ = (uint32_t)src1desc.map; blt.offset[k] = cmdbuf - start; k++;

	*cmdbuf++ = LS(AQDE_SRC_STRIDE_Address, 1);
	*cmdbuf++ = src1geom.virtstride;

	*cmdbuf++ = LS(AQDE_SRC_ROTATION_CONFIG_Address, 1);
	*cmdbuf++ =
		CONFIG_SRC_ROT_MODE(AQDE_SRC_ROTATION_CONFIG_ROTATION_NORMAL) |
		CONFIG_SRC_ROT_WIDTH(src1geom.width);

	*cmdbuf++ = LS(AQDE_SRC_ROTATION_HEIGHT_Address, 1);
	*cmdbuf++ = CONFIG_SRC_ROT_HEIGHT(src1geom.height);

	swizzle = CONVERT_SRC_SWZZL(src1geom.format);
	if (swizzle == 0xFFFFFFFF) {
		e = BVERR_SRC1GEOM_FORMAT;
		goto exit;
	}

	format = CONVERT_SRC1_FMT(src1geom.format);
	if (format == 0xFFFFFFFF) {
		e = BVERR_SRC1GEOM_FORMAT;
		goto exit;
	}

	*cmdbuf++ = LS(AQDE_SRC_CONFIG_Address, 1);
	*cmdbuf++ =
		CONFIG_SRC_LOCATION(AQDE_SRC_CONFIG_LOCATION_MEMORY) |
		CONFIG_SRC_TRANSPARENCY(AQDE_SRC_CONFIG_TRANSPARENCY_OPAQUE) |
		CONFIG_SRC_FMT(format) |
		CONFIG_SRC_SWIZZLE(swizzle) |
		CONFIG_SRC_PIX_CALC(AQDE_SRC_CONFIG_SRC_RELATIVE_ABSOLUTE);

	*cmdbuf++ = CONFIG_START_DE(AQ_COMMAND_START_DE_COMMAND_OPCODE_START_DE);
	*cmdbuf++ = 0xC0FFEE;
	*cmdbuf++ = CONFIG_CLIP_LFTTOP(destrect.left, destrect.top);
	*cmdbuf++ = CONFIG_CLIP_RHTBTM(destrect.left + destrect.width,
				       destrect.top +  destrect.height);

	*cmdbuf++ = LS(AQ_FLUSH_Address, 1);
	*cmdbuf++ = CONFIG_PE2DCACHE_FLUSH();

	*cmdbuf++ = LS(AQ_EVENT_Address, 1);
	*cmdbuf++ =
		CONFIG_PE_EVENT(AQ_EVENT_PE_SRC_ENABLE) |
		CONFIG_PE_EVENT_ID(29);
	*cmdbuf++ = CONFIG_STOP_FE();
	*cmdbuf++ = 0xC0FFEE;

	blt.cmdbuf = start;
	blt.cmdlen = (uint32_t)(cmdbuf - start) * sizeof(uint32_t);

	r = ioctl(fd, BLT, (uint32_t)&blt);
	if (r != 0)
		goto exit;

	/* print out the command buffer */
	tmp = start;
	for (j = 0; j < (cmdbuf - start); j++) {
		fprintf(stdout, "%s()::%d:cmd=(0x%08lX) %d uva=(1x%08lX)\n",
			__func__, __LINE__, (unsigned long)*tmp, j+1, (unsigned long)tmp);
		tmp++;
	}
	fflush(stdout);

	/* no errors, so exit */
	e = BVERR_NONE;
	goto exit;
exit:
	free(start);
	return e;
}

enum bverror bv_blt(struct bvbltparams *bltparams)
{
	int32_t e = BVERR_UNK;
	struct bvbltparams bltparam = {0};
	struct bvrect destrect = {0};

	e = bv_test();
	if (e != 0)
		goto exit;
	sleep(2); sched_yield();

	if (!bltparams)
		goto exit;

	if (sizeof(*bltparams) != sizeof(struct bvbltparams)) {
		e = BVERR_BUFFERDESC_VERS;
		goto exit;
	}

	bltparam = *bltparams;
	destrect = bltparam.dstrect;

	if (bltparam.flags == BVFLAG_TILE_SRC1 ||
			bltparam.flags == BVFLAG_TILE_SRC2 ||
			bltparam.flags == BVFLAG_TILE_MASK) {
		/* tiling */
	} else {
	}

	if (bltparam.flags == BVFLAG_ROP) {
		if (bltparam.src1rect.width - bltparam.src1rect.left == 1 &&
				bltparam.src1rect.height - bltparam.src1rect.top == 1)
			e = fill(bltparams);
		else if (bltparam.src1rect.width == bltparam.dstrect.width &&
				bltparam.src1rect.height == bltparam.dstrect.height)
			e = copy(bltparams);
		else
			goto exit; /* scaling not supported */
	} else if (bltparam.flags == BVFLAG_BLEND) {
		e = blend(bltparams);
	} else if (bltparam.flags == BVFLAG_FILTER) {
	} else {
		/* error */
	}

	/* no errors, so exit */
	e = BVERR_NONE;
	goto exit;
exit:
	return e;
}

enum bverror bv_unmap(struct bvbuffdesc *buffdesc)
{
	int32_t e = BVERR_UNK;
	int32_t r = -1;

	fprintf(stdout, "%s()::%d\n", __FUNCTION__, __LINE__); fflush(stdout);
	if (!buffdesc)
		goto exit;
	if (sizeof(*buffdesc) != sizeof(struct bvbuffdesc)) {
		e = BVERR_BUFFERDESC_VERS;
		goto exit;
	}

	r = ioctl(fd, UMAP, buffdesc);
	if (r == -1 || buffdesc->map == NULL)
		goto e1;

	/* no errors, so exit */
	e = BVERR_NONE;
	goto exit;
e1:
	fprintf(stderr, "%s()::%d:error\n", __FUNCTION__, __LINE__); fflush(stderr);
exit:
	return e;
}

enum bverror bv_test(void)
{
	int32_t e = BVERR_UNK;
	int r = 0;
	uint32_t i = 0;

	r = ioctl(fd, TEST, &i);
	if (r != 0)
		goto exit;
	fprintf(stdout, "%s()::%d:errno=(%d)\n", __FUNCTION__, __LINE__, errno); fflush(stdout);

	e = BVERR_NONE;
	goto exit;
exit:
	return e;
}
