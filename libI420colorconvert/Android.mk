LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    ColorConvert.cpp

LOCAL_C_INCLUDES:= \
        $(TOP)/frameworks/native/include/media/openmax \
        $(TOP)/frameworks/native/include/media/editor

LOCAL_CFLAGS := -Wall -Werror

LOCAL_MODULE_TAGS := optional

ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 26 || echo 1),)
LOCAL_SHARED_LIBRARIES := libarect
endif

LOCAL_MODULE := libI420colorconvert

include $(BUILD_HEAPTRACKED_SHARED_LIBRARY)
