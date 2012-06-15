/*
 * Copyright(c) 2012,
 * Texas Instruments, Inc. and Vivante Corporation.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Vivante Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GCIOCTL_H
#define GCIOCTL_H

#include "gclist.h"
#include "gcerror.h"
#include "cache-2dmanager.h"
#include <bverror.h>

/* IOCTL parameters. */
#define GCIOCTL_TYPE 0x5D
#define GCIOCTL_BASE 0x5D


/*******************************************************************************
 * Commit API entry.
 */

#define GCIOCTL_COMMIT _IOWR(GCIOCTL_TYPE, GCIOCTL_BASE + 0x10, struct gccommit)

/* GPU graphics pipe definition. */
enum gcpipe {
	GCPIPE_UNKNOWN,
	GCPIPE_2D,
	GCPIPE_3D
};

/* Commit header; contains pointers to the head and the tail of a linked list
   of command buffers to execute. */
struct gccommit {
	/* Return status code. */
	enum gcerror gcerror;

	/* Entry graphics pipe specifies the pipe the GPU is expected to be in
	 * for successfull execution of the specified command buffers in this
	 * call. Exit graphics pipe specifies the state of the GPU after the
	 * buffers are executed. */
	enum gcpipe entrypipe;
	enum gcpipe exitpipe;

	/* Pointer to the list of command buffers to be executed. */
	struct gcbuffer *buffer;

	/* Pointer to the callback function to be called when the GPU completes
	 * execution of all buffers specified in this call. This member can be
	 * NULL if no callback is desired. callbackparam specifies data to be
	 * passed to the callback. */
	void (*callback) (void *callbackparam);
	void *callbackparam;
	unsigned long handle;

	/* If asynchronous is set to true, the call returns immediately without
	 * waiting until all specified buffers have been executed. If set to
	 * false, the call does not return until execution is finished. */
	bool asynchronous;

	/* Scheduled unmappings (gcschedunmap). */
	struct list_head unmap;
};

/* Command buffer header. */
#define GC_BUFFER_SIZE (32 * 1024)
struct gcbuffer {
	/* Pointers to the head and tail of the command buffer fixup list. */
	struct gcfixup *fixuphead;
	struct gcfixup *fixuptail;

	/* Number of pixels to be rendered. */
	unsigned int pixelcount;

	/* Pointers to the head and tail of the command buffer list. */
	unsigned int *head;
	unsigned int *tail;

	/* Number of bytes available in the buffer for allocation. */
	unsigned int available;

	/* Pointer to the next commmand buffer.
	 * TODO: change to kernel style linked list. */
	struct gcbuffer *next;
};

/* Fixup entry. */
struct gcfixupentry {
	/* Offset into the commmand buffer where fixup is to be performed. */
	unsigned int dataoffset;

	/* Offset to be added to the translated address. */
	unsigned int surfoffset;
};

/* Address fixup array. */
#define GC_FIXUP_MAX 1024
struct gcfixup {
	/* Pointer to the next fixup array.
	 * TODO: change to kernel style linked list. */
	struct gcfixup *next;

	/* Fixup array. */
	unsigned int count;
	struct gcfixupentry fixup[GC_FIXUP_MAX];
};

/* Defines a link list of scheduled unmappings. */
struct gcschedunmap {
	/* Map handle. */
	unsigned long handle;

	/* Previous/next unmapping info. */
	struct list_head link;
};


/*******************************************************************************
 * Map/unmap API entries.
 */

#define GCIOCTL_MAP   _IOWR(GCIOCTL_TYPE, GCIOCTL_BASE + 0x20, struct gcmap)
#define GCIOCTL_UNMAP _IOWR(GCIOCTL_TYPE, GCIOCTL_BASE + 0x21, struct gcmap)

struct gcmap {
	/* Return status code. */
	enum gcerror gcerror;

	/* Mapped handle of the buffer. */
	unsigned long handle;

	union {
		/* Pointer to the buffer to be mapped;
		 * used when pagearray is not provided (set to NULL). */
		void *logical;

		/* Page offset of the buffer to be mapped;
		 * used when pagearray is provided. */
		unsigned int offset;
	} buf;

	/* Size of a physical page, 0 for  default. */
	unsigned int pagesize;

	/* Pointer to array of physical pages. */
	unsigned long *pagearray;

	/* Size of the buffer to be mappped. */
	unsigned int size;
};


/*****************************************************************************
 * Cache manipulation API entries.
 */

#define GCIOCTL_CACHE _IOW(GCIOCTL_TYPE, GCIOCTL_BASE + 0x30, \
			   struct gccachexfer)

struct gccachexfer {
	/* Number of regions. */
	int count;

	/* The most regions that we deal with is 3. */
	struct c2dmrgn rgn[3];

	/* Direction of data. */
	int dir;
};


/*******************************************************************************
 * Callback API entry.
 */

#define GCIOCTL_CALLBACK_ALLOC _IOW(GCIOCTL_TYPE, GCIOCTL_BASE + 0x40, \
				    struct gccmdcallback)
#define GCIOCTL_CALLBACK_FREE _IOW(GCIOCTL_TYPE, GCIOCTL_BASE + 0x41, \
				   struct gccmdcallback)
#define GCIOCTL_CALLBACK_WAIT _IOW(GCIOCTL_TYPE, GCIOCTL_BASE + 0x42, \
				   struct gccmdcallbackwait)

struct gccmdcallback {
	/* Error code. */
	enum gcerror gcerror;

	/* Callback handle. */
	unsigned long handle;
};

struct gccmdcallbackwait {
	/* Error code. */
	enum gcerror gcerror;

	/* Callback handle. */
	unsigned long handle;

	/* Timeout in milliseconds. */
	unsigned long timeoutms;

	/* OUT: if the call succeeds, callback and callbackparam are
	 *      initialized with the callback to call. */
	void (*callback) (void *callbackparam);
	void *callbackparam;
};


#endif
