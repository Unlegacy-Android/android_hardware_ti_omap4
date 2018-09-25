# Copyright (C) 2016 The Unlegacy Android Project
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

PVR_KM_OUT ?= $(KERNEL_OUT)/pvr-km
PVR_MODULES ?= $(addsuffix .ko,$(addprefix \
		$(PVR_KM_OUT)/target/,pvrsrvkm omaplfb))
BUILD_PVR: MK_DIR ?= \
	$(OMAP4_NEXT_FOLDER)/pvr-source/eurasiacon/build/linux2/omap_android
BUILD_PVR: MK_CMD ?= $(MAKE) -C $(MK_DIR) ARCH=$(KERNEL_ARCH) \
	KERNELDIR=$(KERNEL_OUT) OUT=$(PVR_KM_OUT)

BUILD_PVR: TARGET_KERNEL_BINARIES
	$(MK_CMD) clean && $(MK_CMD) $(if $(ARM_CROSS_COMPILE),\
		$(ARM_CROSS_COMPILE),$(KERNEL_CROSS_COMPILE)) \
		TARGET_DEVICE=blaze$(if $(filter-out 4470,\
		$(TARGET_BOARD_OMAP_CPU)),,.4470)
	$(if $(ARM_EABI_TOOLCHAIN),$(ARM_EABI_TOOLCHAIN)/arm-eabi-strip, \
		$(KERNEL_TOOLCHAIN_PATH)strip) --strip-unneeded $(PVR_MODULES)

$(PVR_MODULES): BUILD_PVR

PVR_MODULES: $(PVR_MODULES)
	mv $(PVR_MODULES) $(KERNEL_MODULES_OUT)

BOARD_BOOT_KERNEL_MODULES += $(PVR_MODULES)
