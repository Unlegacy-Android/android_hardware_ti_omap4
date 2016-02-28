LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := corkscrew.c
LOCAL_CFLAGS := -Wall -Werror
LOCAL_MODULE := libcorkscrew
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
