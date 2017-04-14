OMAP4_SEPOLICY_BASE := hardware/ti/omap4/sepolicy

# 4.4
ifeq ($(shell test $(PLATFORM_SDK_VERSION) -eq 19 || echo 1),)
BOARD_SEPOLICY_UNION += \
	file.te \
	file_contexts \
	init.te \
	pvrsrvinit.te
endif

# >=5.0
ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 20 || echo 1),)
BOARD_SEPOLICY_DIRS += $(OMAP4_SEPOLICY_BASE)/compat/lp
endif

BOARD_SEPOLICY_DIRS += $(OMAP4_SEPOLICY_BASE)
