LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

#Creating Gralloc SymLink
GRALLOC_SYMLINK := $(TARGET_OUT_VENDOR)/lib/hw/gralloc.$(TARGET_BOARD_PLATFORM).so
$(GRALLOC_SYMLINK): GRALLOC_FILE := gralloc.omap$(TARGET_BOARD_OMAP_CPU).so
$(GRALLOC_SYMLINK): $(LOCAL_INSTALLED_MODULE) $(LOCAL_PATH)/Android.mk
	@echo "Symlink: $@ -> $(GRALLOC_FILE)"
	@mkdir -p $(TARGET_OUT_VENDOR)/lib/hw
	@rm -rf $@
	$(hide) ln -fs $(GRALLOC_FILE) $@

ALL_DEFAULT_INSTALLED_MODULES += $(GRALLOC_SYMLINK)

# for mm/mmm
all_modules: $(GRALLOC_SYMLINK)

include $(CLEAR_VARS)

ifeq ($(BOARD_USE_TI_LIBION),true)

LOCAL_MODULE := libion.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := FAKE

include $(BUILD_SYSTEM)/base_rules.mk

$(LOCAL_BUILT_MODULE): TARGET := /system/lib/libion_ti.so
$(LOCAL_BUILT_MODULE): SYMLINK := $(TARGET_OUT)/lib/$(LOCAL_MODULE)
$(LOCAL_BUILT_MODULE):
	$(hide) echo "Symlink: $(SYMLINK) -> $(TARGET)"
	$(hide) mkdir -p $(dir $@)
	$(hide) mkdir -p $(dir $(SYMLINK))
	$(hide) rm -rf $@
	$(hide) rm -rf $(SYMLINK)
	$(hide) ln -sf $(TARGET) $(SYMLINK)
	$(hide) touch $@

endif
