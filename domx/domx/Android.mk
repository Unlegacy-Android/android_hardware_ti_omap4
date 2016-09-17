LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    omx_rpc/src/omx_rpc.c \
    omx_rpc/src/omx_rpc_skel.c \
    omx_rpc/src/omx_rpc_stub.c \
    omx_rpc/src/omx_rpc_config.c \
    omx_rpc/src/omx_rpc_platform.c \
    omx_proxy_common/src/omx_proxy_common.c \
    profiling/src/profile.c \
    plugins/memplugin.c \
    plugins/memplugin_table.c \
    plugins/memplugin_ion.c

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/omx_rpc/inc \
    $(LOCAL_PATH)/../omx_core/inc \
    $(LOCAL_PATH)/../mm_osal/inc \
    $(LOCAL_PATH)/profiling/inc \
    $(HARDWARE_TI_OMAP4_BASE)/hwc/ \
    $(HARDWARE_TI_OMAP4_BASE)/include/ \
    system/core/include/cutils \
    $(HARDWARE_TI_OMAP4_BASE)/../../libhardware/include \
    $(LOCAL_PATH)/plugins/inc/ \
    frameworks/native/include/media/openmax

LOCAL_CFLAGS += $(ANDROID_API_CFLAGS)
LOCAL_CFLAGS += -D_Android -DENABLE_GRALLOC_BUFFERS -DUSE_ENHANCED_PORTRECONFIG -DANDROID_QUIRK_LOCK_BUFFER -DUSE_ION
ifdef BOARD_USE_TI_DOMX_LOW_SECURE_HEAP
LOCAL_CFLAGS += -DDOMX_LOW_SECURE_HEAP
endif

LOCAL_SHARED_LIBRARIES := \
    libmm_osal \
    liblog \
    libcutils

ifeq ($(BOARD_USE_TI_LIBION),true)
LOCAL_SHARED_LIBRARIES += libion_ti
LOCAL_CFLAGS += -DUSE_TI_LIBION
else
LOCAL_SHARED_LIBRARIES += libion
LOCAL_SRC_FILES += ../../libion/ion_ti_custom.c
LOCAL_C_INCLUDES += $(HARDWARE_TI_OMAP4_BASE)/libion
endif

ifeq ($(TARGET_BOOTLOADER_BOARD_NAME),tuna)
	LOCAL_CFLAGS += -DDOMX_TUNA
endif

LOCAL_MODULE:= libdomx
LOCAL_MODULE_TAGS:= optional

include $(BUILD_HEAPTRACKED_SHARED_LIBRARY)
