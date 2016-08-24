LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    src/OMX_Core.c \
    src/OMX_Core_Wrapper.c

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/inc \
    $(LOCAL_PATH)/../mm_osal/inc \
    frameworks/native/include/media/openmax

LOCAL_SHARED_LIBRARIES := \
    libdl \
    liblog \
    libmm_osal

ifdef USE_ITTIAM_AAC
LOCAL_CFLAGS += -DUSE_ITTIAM_AAC
endif

LOCAL_CFLAGS += -DSTATIC_TABLE -D_Android -DCHECK_SECURE_STATE
LOCAL_MODULE:= libOMX_Core
LOCAL_MODULE_TAGS:= optional
include $(BUILD_HEAPTRACKED_SHARED_LIBRARY)
