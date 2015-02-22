# Copyright (C) 2015 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

OMAP4_NEXT_FOLDER := hardware/ti/omap4

# Processor
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_VARIANT := cortex-a9
TARGET_CPU_ABI2 := armeabi
TARGET_CPU_SMP := true
TARGET_ARCH := arm
TARGET_BOARD_PLATFORM := omap4
TARGET_BOARD_PLATFORM_VARIANT := omap4-next
TARGET_ARCH_VARIANT := armv7-a-neon

# Graphics
USE_OPENGL_RENDERER := true
BOARD_EGL_WORKAROUND_BUG_10194508 ?= true

# Global include changes
#TARGET_SPECIFIC_HEADER_PATH += $(OMAP4_NEXT_FOLDER)/include

# TI Enhancement Settings
OMAP_ENHANCEMENT := true
OMAP_ENHANCEMENT_MULTIGPU := true
BOARD_USE_TI_ENHANCED_DOMX := true
BOARD_USE_TI_DUCATI_H264_PROFILE := true
BOARD_USE_TI_DOMX_LOW_SECURE_HEAP := true
BOARD_USE_TI_LIBION ?= true
COMMON_GLOBAL_CFLAGS += -DENHANCED_DOMX
ENHANCED_DOMX := true
TARGET_SPECIFIC_HEADER_PATH += $(OMAP4_NEXT_FOLDER)/domx/omx_core/inc
BOARD_USE_TI_CUSTOM_DOMX := true
DOMX_PATH := $(OMAP4_NEXT_FOLDER)/domx

ifeq ($(BOARD_USE_TI_LIBION),true)
    COMMON_GLOBAL_CFLAGS += -DUSE_TI_LIBION
endif

ifdef OMAP_ENHANCEMENT
    COMMON_GLOBAL_CFLAGS += -DOMAP_ENHANCEMENT -DTARGET_OMAP4 -DFORCE_SCREENSHOT_CPU_PATH
endif

ifdef OMAP_ENHANCEMENT_BURST_CAPTURE
    COMMON_GLOBAL_CFLAGS += -DOMAP_ENHANCEMENT_BURST_CAPTURE
endif

ifdef OMAP_ENHANCEMENT_S3D
    COMMON_GLOBAL_CFLAGS += -DOMAP_ENHANCEMENT_S3D
endif

ifdef OMAP_ENHANCEMENT_CPCAM
    COMMON_GLOBAL_CFLAGS += -DOMAP_ENHANCEMENT_CPCAM
    PRODUCT_MAKEFILES += $(LOCAL_DIR)/sdk_addon/ti_omap_addon.mk
endif

ifdef OMAP_ENHANCEMENT_VTC
    COMMON_GLOBAL_CFLAGS += -DOMAP_ENHANCEMENT_VTC
endif

ifdef USE_ITTIAM_AAC
    COMMON_GLOBAL_CFLAGS += -DUSE_ITTIAM_AAC
endif

ifdef OMAP_ENHANCEMENT_MULTIGPU
    COMMON_GLOBAL_CFLAGS += -DOMAP_ENHANCEMENT_MULTIGPU
endif

# Bootanimation
TARGET_BOOTANIMATION_PRELOAD := false
TARGET_BOOTANIMATION_TEXTURE_CACHE := false
TARGET_BOOTANIMATION_USE_RGB565 := true

# SELinux
BOARD_SEPOLICY_DIRS += \
    $(OMAP4_NEXT_FOLDER)/sepolicy

# Misc
BOARD_USES_SECURE_SERVICES := true

