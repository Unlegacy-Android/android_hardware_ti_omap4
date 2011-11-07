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

#ifndef BV_H
#define BV_H
#include "bltsville.h"

#define EVENT(buf, n) \
        *buf++ = SETFIELDVAL(0, AQ_COMMAND_LOAD_STATE_COMMAND, OPCODE, LOAD_STATE) \
                | SETFIELD(0, AQ_COMMAND_LOAD_STATE_COMMAND, ADDRESS, AQEventRegAddrs) \
                | SETFIELD(0, AQ_COMMAND_LOAD_STATE_COMMAND, COUNT, 1); \
        *buf++ = SETFIELDVAL(0, AQ_EVENT, PE_SRC, ENABLE) \
                | SETFIELD(0, AQ_EVENT, EVENT_ID, n);

/* Stop FE. */
#define END(buf) \
        *buf++ = SETFIELDVAL(0, AQ_COMMAND_END_COMMAND, OPCODE, END);\
	*buf++ = 0xC0FFEE;

#define EVENT_END(buf, n) \
	EVENT(buf, n); \
	END(buf);

enum bverror bv_map(struct bvbuffdesc *buffdesc);
enum bverror bv_blt(struct bvbltparams *bltparams);
enum bverror bv_unmap(struct bvbuffdesc *buffdesc);
enum bverror bv_test(void);
#endif
