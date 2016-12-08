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

PVR_MODULES:
	make clean -C $(OMAP4_NEXT_FOLDER)/pvr-source/eurasiacon/build/linux2/omap4430_android
	make -j8 -C $(OMAP4_NEXT_FOLDER)/pvr-source/eurasiacon/build/linux2/omap4430_android \
			ARCH=arm $(if $(ARM_CROSS_COMPILE),$(ARM_CROSS_COMPILE),$(KERNEL_CROSS_COMPILE)) \
			TARGET_SGX=$(if $(filter-out 4470,$(TARGET_BOARD_OMAP_CPU)),540,544sc) \
			KERNELDIR=$(KERNEL_OUT) BUILD=release
	mv $(KERNEL_OUT)/../../target/kbuild/pvrsrvkm.ko $(KERNEL_MODULES_OUT)
	$(if $(ARM_EABI_TOOLCHAIN),$(ARM_EABI_TOOLCHAIN)/arm-eabi-strip, \
			$(KERNEL_TOOLCHAIN_PATH)strip) --strip-unneeded \
			$(KERNEL_MODULES_OUT)/pvrsrvkm.ko

TARGET_KERNEL_MODULES += PVR_MODULES
