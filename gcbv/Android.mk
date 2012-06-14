#
# Copyright (c) 2012, 
# Texas Instruments, Inc. and Vivante Corporation. 
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of Texas Instruments, Inc. nor the names of its
#       contributors may be used to endorse or promote products derived from
#       this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL TEXAS INSTRUMENTS, INC. BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
	gcmain.c \
	mirror/gcbv.c \
	mirror/gcdbglog.c

LOCAL_CFLAGS :=

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/mirror/include \
	external/bltsville/bltsville/include \
	external/bltsville/ocd/include

VERSION_H := external/bltsville/gcbv/version.h
BV_VERSION := $(shell grep "VER_FILEVERSION_STR" $(VERSION_H) | sed "s,.*\"\([0-9.]*\)\\\0.*,\1,")

LOCAL_MODULE_TAGS    := optional
LOCAL_MODULE         := libbltsville_gc2d
LOCAL_MODULE_SUFFIX  := .$(BV_VERSION).so
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/../vendor/lib

$(shell ln -fs ./libbltsville_gc2d.$(BV_VERSION).so $(LOCAL_MODULE_PATH)/libbltsville_gc2d.so)
$(shell ln -fs ./libbltsville_gc2d.so $(LOCAL_MODULE_PATH)/libbltsville_hw2d.so)

include $(BUILD_SHARED_LIBRARY)
