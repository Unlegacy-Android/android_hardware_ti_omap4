LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    ColorConvert.cpp

LOCAL_C_INCLUDES:= \
        $(TOP)/frameworks/native/include/media/openmax \
        $(TOP)/frameworks/native/include/media/editor

LOCAL_CFLAGS := -Wall -Werror

LOCAL_MODULE_TAGS := optional

ifdef ANDROID_API_O_OR_LATER
LOCAL_SHARED_LIBRARIES := libarect
endif

LOCAL_MODULE := libI420colorconvert

include $(BUILD_HEAPTRACKED_SHARED_LIBRARY)
