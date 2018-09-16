LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := pvrsrvinit.c
LOCAL_CFLAGS := -Wall -Werror
LOCAL_SHARED_LIBRARIES := libsrv_init libsrv_um
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
LOCAL_MODULE := pvrsrvinit
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

