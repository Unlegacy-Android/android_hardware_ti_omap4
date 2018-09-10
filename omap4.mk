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

OMAP4_NEXT_FOLDER := hardware/ti/omap4

PRODUCT_PACKAGES += \
    android.hardware.power@1.0-impl \
    power.omap4

PRODUCT_VENDOR_KERNEL_HEADERS := hardware/ti/omap4/kernel-headers

# Init
PRODUCT_COPY_FILES += \
    $(OMAP4_NEXT_FOLDER)/rootdir/init.omap4.rc:root/init.omap4.rc

# Disable dirty regions invalidation
PRODUCT_PROPERTY_OVERRIDES += \
    debug.hwui.render_dirty_regions=false

# We don't support eglSwapBuffersWithDamageKHR; this avoids some unnecessary code
PRODUCT_PROPERTY_OVERRIDES += \
    debug.hwui.swap_with_damage=false

# We don't support the new camera API
PRODUCT_PROPERTY_OVERRIDES += \
    camera2.portability.force_api=1

# Ensure release of EGL buffer in the ColorFade class
PRODUCT_PROPERTY_OVERRIDES += \
    ro.egl.destroy_after_detach=true

$(call inherit-product, hardware/ti/omap4/common.mk)
$(call inherit-product-if-exists, vendor/ti/omap4/omap4-vendor.mk)
$(call inherit-product-if-exists, vendor/widevine/arm-generic/widevine-vendor.mk)
