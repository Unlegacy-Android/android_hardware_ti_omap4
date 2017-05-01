OMAP4_SEPOLICY_BASE := hardware/ti/omap4/sepolicy

# <=5.1
ifeq ($(shell test $(PLATFORM_SDK_VERSION) -lt 23 || echo 1),)
BOARD_SEPOLICY_UNION += \
	file.te \
	file_contexts \
	init.te \
	pvrsrvinit.te

# 5.x
ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 19 || echo 1),)
BOARD_SEPOLICY_UNION += \
	defines.te \
	system_server.te
endif
endif

# >=5.0
ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 19 || echo 1),)
BOARD_SEPOLICY_DIRS += $(OMAP4_SEPOLICY_BASE)/compat/lp
endif

# >=7.0
ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 24 || echo 1),)
BOARD_SEPOLICY_M4DEFS += android_api_n_or_later=true
endif

BOARD_SEPOLICY_DIRS += $(OMAP4_SEPOLICY_BASE)
