#
# Copyright (C) 2012 Texas Instruments Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := $(if $(ANDROID_API_P_OR_LATER),libhwui,libskia)

LOCAL_WHOLE_STATIC_LIBRARIES := libc_common

LOCAL_SRC_FILES := SkLibTiJpeg_Test.cpp

LOCAL_MODULE := SkLibTiJpeg_Test
LOCAL_MODULE_TAGS:= optional

LOCAL_C_INCLUDES += \
    bionic/libc/bionic \
    external/skia/include/core \
    external/skia/include/images


ifeq ($(TARGET_BOARD_PLATFORM),omap4)
    LOCAL_CFLAGS += -DTARGET_OMAP4
endif


include $(BUILD_EXECUTABLE)
