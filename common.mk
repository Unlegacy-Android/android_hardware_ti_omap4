# Copyright (C) 2011 The Android Open Source Project
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

# This file lists the modules that are specific to OMAP4 but are used by
# all OMAP4 devices.

ifndef ANDROID_API_CFLAGS
include $(LOCAL_PATH)/android-api.mk
endif

ifeq ($(ANDROID_API_LP_OR_LATER),true)
DEVICE_PACKAGE_OVERLAYS += hardware/ti/omap4/overlay
endif

PRODUCT_PACKAGES += \
    android.hardware.graphics.allocator@2.0-impl \
    android.hardware.graphics.composer@2.1-impl \
    android.hardware.graphics.mapper@2.0-impl \
    android.hardware.memtrack@1.0-impl \
    libdomx \
    libOMX_Core \
    libOMX.TI.DUCATI1.VIDEO.H264E \
    libOMX.TI.DUCATI1.VIDEO.H264SVCE \
    libOMX.TI.DUCATI1.VIDEO.VC1E \
    libOMX.TI.DUCATI1.VIDEO.MPEG4E \
    libOMX.TI.DUCATI1.VIDEO.DECODER \
    libOMX.TI.DUCATI1.VIDEO.DECODER.secure \
    libOMX.TI.DUCATI1.VIDEO.CAMERA \
    libOMX.TI.DUCATI1.MISC.SAMPLE \
    libstagefrighthw \
    $(if $(ANDROID_API_LP_OR_LATER),,libI420colorconvert) \
    libtiutils \
    android.hardware.keymaster@3.0-impl \
    smc_pa_ctrl \
    tf_daemon \
    libtf_crypto_sst

ifdef ANDROID_API_O_OR_LATER
# Vendor seccomp policy files for media components
PRODUCT_COPY_FILES += \
    $(OMAP4_NEXT_FOLDER)/seccomp/mediacodec-seccomp.policy:$(TARGET_COPY_OUT_VENDOR)/etc/seccomp_policy/mediacodec.policy
endif

PRODUCT_PACKAGES += \
    libion

# pvr-related objects
PRODUCT_PACKAGES += \
    pvrsrvinit \
    libPVRScopeServices.so
