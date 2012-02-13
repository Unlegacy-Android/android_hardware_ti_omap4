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

#ifndef GCIOCTL_H
#define GCIOCTL_H

#include "gcerror.h"
#include <bverror.h>

/* IOCTL parameters. */
#define GCIOCTL_TYPE 0x5D
#define GCIOCTL_BASE 0x5D

/*******************************************************************************
 * Commit API entry.
 */

struct gccommit;
struct gcbuffer;
struct gcfixup;

#define GCIOCTL_COMMIT _IOWR(GCIOCTL_TYPE, GCIOCTL_BASE + 0x10, struct gccommit)

/* Commit header; contains pointers to the head and the tail of a linked list
   of command buffers to execute. */
struct gccommit {
	enum gcerror gcerror;		/* Return status code. */
	struct gcbuffer *buffer;	/* Command buffer list. */
};

/* Command buffer header. */
#define GC_BUFFER_SIZE 81920
struct gcbuffer {
	struct gcfixup *fixuphead;	/* Address fixup list. */
	struct gcfixup *fixuptail;

	unsigned int pixelcount;	/* Number of pixels to be rendered. */

	unsigned int *head;		/* Pointers to the head and tail */
	unsigned int *tail;		/* of the command buffer. */

	unsigned int available;		/* Number of bytes available in the
					   buffer. */
	struct gcbuffer *next;		/* Pointer to the next commmand
					   buffer. */
};

/* Fixup entry. */
struct gcfixupentry {
	unsigned int dataoffset;	/* Offset into the commmand buffer
					   where fixup is to be performed. */
	unsigned int surfoffset;	/* Offset to be added to the base
					   address of the surface. */
};

/* Address fixup array. */
#define GC_FIXUP_MAX 1024
struct gcfixup {
	struct gcfixup *next;
	unsigned int count;
	struct gcfixupentry fixup[GC_FIXUP_MAX];
};

/*******************************************************************************
 * Map/unmap API entries.
 */

struct gcmap;

#define GCIOCTL_MAP   _IOWR(GCIOCTL_TYPE, GCIOCTL_BASE + 0x20, struct gcmap)
#define GCIOCTL_UNMAP _IOWR(GCIOCTL_TYPE, GCIOCTL_BASE + 0x21, struct gcmap)

struct gcmap {
	enum gcerror gcerror;		/* Return status code. */
	unsigned int handle;		/* Mapped handle of the buffer. */

	void *logical;			/* Pointer to the buffer. */
	unsigned int size;		/* Size of the buffer. */
	unsigned long pagecount;	/* Number of physical pages */
	unsigned long *pagearray;	/* List of physical pages */
};

/*******************************************************************************
 * BLTsville: blit API entry.
 */

struct gcbvblt;

#define GCIOCTL_BVBLT _IOWR(GCIOCTL_TYPE, GCIOCTL_BASE + 0x30, struct gcbvblt)

struct gcbvblt {
	enum bverror bverror;		/* Return status code. */
	struct bvbltparams *bltparams;	/* Blit parameters. */
	char *errdesc;			/* Blit error message. */
	int errdesclen;			/* Maximum length of the error
					   message. */
};

/*******************************************************************************
 * BLTsville: map/unmap API entries.
 */

struct gcbvmap;

#define GCIOCTL_BVMAP   _IOWR(GCIOCTL_TYPE, GCIOCTL_BASE + 0x40, struct gcbvmap)
#define GCIOCTL_BVUNMAP _IOWR(GCIOCTL_TYPE, GCIOCTL_BASE + 0x41, struct gcbvmap)

struct gcbvmap {
	enum bverror bverror;		/* Return status code. */
	struct bvbuffdesc *buffdesc;	/* Surface descriptor. */
};

#endif
