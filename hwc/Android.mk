LOCAL_PATH := $(call my-dir)

# HAL module implementation, not prelinked and stored in
# hw/<HWCOMPOSE_HARDWARE_MODULE_ID>.<ro.product.board>.so
include $(CLEAR_VARS)
LOCAL_ARM_MODE := arm
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/../vendor/lib/hw
LOCAL_SHARED_LIBRARIES := liblog libEGL libcutils libutils libhardware libhardware_legacy libz

LOCAL_SRC_FILES := hwc.c rgz_2d.c dock_image.c sw_vsync.c display.c
LOCAL_CFLAGS := -DLOG_TAG=\"ti_hwc\" -Wall -Werror

ifeq ($(BOARD_USE_TI_LIBION),true)
LOCAL_SHARED_LIBRARIES += libion_ti
LOCAL_CFLAGS += -DUSE_TI_LIBION
else
LOCAL_SHARED_LIBRARIES += libion
LOCAL_SRC_FILES += ../libion/ion_ti_custom.c
LOCAL_CFLAGS += -DSUPPORT_ANDROID_FRAMEBUFFER_HAL
LOCAL_C_INCLUDES += $(HARDWARE_TI_OMAP4_BASE)/libion
endif

ifdef OMAP_ENHANCEMENT_S3D
LOCAL_CFLAGS += -DOMAP_ENHANCEMENT_S3D
endif

ifdef OMAP_ENHANCEMENT_HWC_EXTENDED_API
LOCAL_CFLAGS += -DOMAP_ENHANCEMENT_HWC_EXTENDED_API
endif

LOCAL_STATIC_LIBRARIES := libpng

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := hwcomposer.omap4
LOCAL_C_INCLUDES += external/libpng external/zlib

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../edid/inc \
    $(LOCAL_PATH)/../include
LOCAL_SHARED_LIBRARIES += libedid

# LOG_NDEBUG=0 means verbose logging enabled
# LOCAL_CFLAGS += -DLOG_NDEBUG=0
include $(BUILD_SHARED_LIBRARY)
