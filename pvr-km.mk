PVR_MODULES:
	make clean -C $(OMAP4_NEXT_FOLDER)/pvr-source/eurasiacon/build/linux2/omap4430_android
	make -j8 -C $(OMAP4_NEXT_FOLDER)/pvr-source/eurasiacon/build/linux2/omap4430_android \
			ARCH=arm $(if $(ARM_CROSS_COMPILE),$(ARM_CROSS_COMPILE),$(KERNEL_CROSS_COMPILE)) \
			KERNELDIR=$(KERNEL_OUT) TARGET_PRODUCT="blaze_tablet" BUILD=release \
			TARGET_SGX=$(if $(filter-out 4470,$(TARGET_BOARD_OMAP_CPU)),540,544sc)
	mv $(KERNEL_OUT)/../../target/kbuild/pvrsrvkm.ko $(KERNEL_MODULES_OUT)
	$(if $(ARM_EABI_TOOLCHAIN),$(ARM_EABI_TOOLCHAIN)/arm-eabi-strip, \
			$(KERNEL_TOOLCHAIN_PATH)strip) --strip-unneeded \
			$(KERNEL_MODULES_OUT)/pvrsrvkm.ko

TARGET_KERNEL_MODULES += PVR_MODULES
