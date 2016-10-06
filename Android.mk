ifeq ($(TARGET_BOARD_PLATFORM),omap4)
ifeq ($(TARGET_BOARD_PLATFORM_VARIANT),omap4-next)

LOCAL_PATH:= $(call my-dir)

include $(LOCAL_PATH)/android-api.mk

ifeq ($(ANDROID_API_LP_OR_LATER),true)
libEGL_shim_name := libEGL_POWERVR_SGX54X
else
libEGL_shim_name := libEGL_POWERVR
endif

HARDWARE_TI_OMAP4_BASE:= $(LOCAL_PATH)
OMAP4_DEBUG_MEMLEAK:= false

ifeq ($(OMAP4_DEBUG_MEMLEAK),true)

OMAP4_DEBUG_CFLAGS:= -DHEAPTRACKER
OMAP4_DEBUG_LDFLAGS:= $(foreach f, $(strip malloc realloc calloc free), -Wl,--wrap=$(f))
OMAP4_DEBUG_SHARED_LIBRARIES:= liblog
BUILD_HEAPTRACKED_SHARED_LIBRARY:= $(HARDWARE_TI_OMAP4_BASE)/heaptracked-shared-library.mk
BUILD_HEAPTRACKED_EXECUTABLE:= $(HARDWARE_TI_OMAP4_BASE)/heaptracked-executable.mk

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= heaptracker.c stacktrace.c mapinfo.c
LOCAL_MODULE:= libheaptracker
LOCAL_MODULE_TAGS:= optional
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= tm.c
LOCAL_MODULE:= tm
LOCAL_MODULE_TAGS:= test
include $(BUILD_HEAPTRACKED_EXECUTABLE)

else
BUILD_HEAPTRACKED_SHARED_LIBRARY:=$(BUILD_SHARED_LIBRARY)
BUILD_HEAPTRACKED_EXECUTABLE:= $(BUILD_EXECUTABLE)
endif

include $(call first-makefiles-under,$(LOCAL_PATH))
else
LOCAL_PATH:= $(call my-dir)

$(clear-android-api-vars)

endif
endif
