# only include if running TI 3.0 kernel
ifeq ($(BOARD_USE_TI_LIBION),true)

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := ion.c
LOCAL_CFLAGS := -Wall -Werror -DUSE_TI_LIBION
LOCAL_MODULE := libion_ti
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := liblog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := ion.c ion_test.c
LOCAL_CFLAGS := -DUSE_TI_LIBION
LOCAL_MODULE := ion_ti_test
LOCAL_MODULE_TAGS := optional tests
LOCAL_SHARED_LIBRARIES := liblog
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := ion.c ion_test_2.c
LOCAL_CFLAGS := -DUSE_TI_LIBION
LOCAL_MODULE := ion_ti_test2
LOCAL_MODULE_TAGS := optional tests
LOCAL_SHARED_LIBRARIES := liblog
include $(BUILD_EXECUTABLE)

endif
