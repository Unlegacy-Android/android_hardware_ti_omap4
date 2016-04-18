LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := pvrsrvinit.c
LOCAL_CFLAGS := -Wall -Werror
LOCAL_LDFLAGS := -L $(TARGET_OUT_VENDOR)/lib
LOCAL_LDFLAGS += -lsrv_init -lsrv_um
pvrsrvinit: $(TARGET_OUT_VENDOR)/lib/libsrv_init.so
pvrsrvinit: $(TARGET_OUT_VENDOR)/lib/libsrv_um.so
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
LOCAL_MODULE := pvrsrvinit
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

