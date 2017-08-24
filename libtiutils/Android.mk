################################################

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)


LOCAL_SRC_FILES:= \
    DebugUtils.cpp \
    MessageQueue.cpp \
    Semaphore.cpp \
    ErrorUtils.cpp

LOCAL_SHARED_LIBRARIES:= \
    libdl \
    libui \
    libbinder \
    libutils \
    libcutils \
    liblog

ifdef ANDROID_API_JB_OR_LATER
LOCAL_C_INCLUDES += \
    frameworks/native/include/media/openmax \
    frameworks/native/include
else
LOCAL_C_INCLUDES += \
    frameworks/native/include/media/openmax \
    frameworks/base/include
endif

LOCAL_C_INCLUDES += \
    bionic/libc/include 

ifdef ENHANCED_DOMX
LOCAL_C_INCLUDES += \
    $(DOMX_PATH)/omx_core/inc \
    $(DOMX_PATH)/mm_osal/inc
else
LOCAL_C_INCLUDES += \
    $(HARDWARE_TI_OMAP4_BASE)/domx/omx_core/inc \
    $(HARDWARE_TI_OMAP4_BASE)/domx/mm_osal/inc
endif

LOCAL_CFLAGS += -fno-short-enums $(ANDROID_API_CFLAGS)

ifdef TI_UTILS_MESSAGE_QUEUE_DEBUG_ENABLED
    # Enable debug logs
    LOCAL_CFLAGS += -DMSGQ_DEBUG
endif

ifdef TI_UTILS_MESSAGE_QUEUE_DEBUG_FUNCTION_NAMES
    # Enable function enter/exit logging
    LOCAL_CFLAGS += -DTI_UTILS_FUNCTION_LOGGER_ENABLE
endif

LOCAL_CFLAGS += $(ANDROID_API_CFLAGS)

LOCAL_MODULE:= libtiutils
LOCAL_MODULE_TAGS:= optional

include $(BUILD_HEAPTRACKED_SHARED_LIBRARY)
