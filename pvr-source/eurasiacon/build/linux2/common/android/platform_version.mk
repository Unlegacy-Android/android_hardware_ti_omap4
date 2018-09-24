########################################################################### ###
#@Copyright     Copyright (c) Imagination Technologies Ltd. All Rights Reserved
#@License       Dual MIT/GPLv2
# 
# The contents of this file are subject to the MIT license as set out below.
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# Alternatively, the contents of this file may be used under the terms of
# the GNU General Public License Version 2 ("GPL") in which case the provisions
# of GPL are applicable instead of those above.
# 
# If you wish to allow use of your version of this file only under the terms of
# GPL, and not to allow others to use your version of this file under the terms
# of the MIT license, indicate your decision by deleting the provisions above
# and replace them with the notice and other provisions required by GPL as set
# out in the file called "GPL-COPYING" included in this distribution. If you do
# not delete the provisions above, a recipient may use your version of this file
# under the terms of either the MIT license or GPL.
# 
# This License is also included in this distribution in the file called
# "MIT-COPYING".
# 
# EXCEPT AS OTHERWISE STATED IN A NEGOTIATED AGREEMENT: (A) THE SOFTWARE IS
# PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
# BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
# PURPOSE AND NONINFRINGEMENT; AND (B) IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
### ###########################################################################

define newline


endef

PLATFORM_BUILDID ?= UNKNOWN

# Figure out the version of Android we're building against.
#
ifeq ($(strip $(PLATFORM_RELEASE)),)
BUILD_PROP := $(ANDROID_PRODUCT_OUT)/system/build.prop
BUILD_DEFS := $(ANDROID_BUILD_TOP)/build/core/version_defaults.mk
ifneq ($(wildcard $(BUILD_PROP)),)
# Extract version.release and version.codename from the build.prop file.
# If either of the values aren't in the build.prop, the Make variables won't
# be defined, and fallback handling will take place.
#
$(eval $(subst #,$(newline),$(shell cat $(BUILD_PROP) | \
	grep '^ro.build.version.release=\|^ro.build.id=' | \
	sed -e 's,ro.build.version.release=,PLATFORM_RELEASE:=,' \
	    -e 's,ro.build.id=,PLATFORM_BUILDID:=,' | tr '\n' '#')))
else ifneq ($(wildcard $(BUILD_DEFS)),)
$(warning *** No device prop file ($(BUILD_PROP)). Extracting from \
	build/core/version_defaults.mk)
# Android version information doesn't permeate here. Set it up manually,
# but avoid including the whole of core/version_defaults.mk
$(eval $(subst #,$(newline),$(shell cat $(BUILD_DEFS) | \
	grep '\<PLATFORM_VERSION.*:=\s[1-9]\|\<BUILD_ID.*:=\s[A-Z]' | \
	sed -e 's,BUILD_ID.*=,PLATFORM_BUILDID:=,' \
	    -e 's,PLATFORM_VERSION.*=,PLATFORM_RELEASE:=,' | tr '\n' '#')))
else
$(warning *** No device prop file ($(BUILD_PROP)) or build env \
	($(BUILD_DEFS)). Falling back to KitKat default)
PLATFORM_RELEASE := 4.4
endif
endif

$(info PLATFORM_RELEASE=$(PLATFORM_RELEASE) & PLATFORM_BUILDID=$(PLATFORM_BUILDID))

define release-starts-with
$(shell echo $(PLATFORM_RELEASE) | grep -q ^$(1); \
	[ "$$?" = "0" ] && echo 1 || echo 0)
endef

# ro.build.version.release contains the version number for release builds, or
# the version codename otherwise. In this case we need to assume that the
# version of Android we're building against has the features that are in the
# final release of that version, so we set PLATFORM_RELEASE to the
# corresponding release number.
#
# NOTE: It's the _string_ ordering that matters here, not the version number
# ordering. You need to make sure that strings that are sub-strings of other
# checked strings appear _later_ in this list.
#
# e.g. 'LollipopMR1' starts with 'Lollipop', but it is not Lollipop.
#
# NOTE: The version codenames for Android stopped after KitKat, don't read
# too much into the below names. They are mostly placeholders/reminders.
#
ifeq ($(call release-starts-with,KitKatMR),1)
override PLATFORM_RELEASE := 4.4.1
else ifeq ($(call release-starts-with,KitKat),1)
override PLATFORM_RELEASE := 4.4
else ifeq ($(call release-starts-with,LollipopMR1),1)
override PLATFORM_RELEASE := 5.1
else ifeq ($(call release-starts-with,Lollipop),1)
override PLATFORM_RELEASE := 5.0
else ifeq ($(call release-starts-with,Marshmallow),1)
override PLATFORM_RELEASE := 6.0
else ifeq ($(call release-starts-with,NougatMR),1)
override PLATFORM_RELEASE := 7.1
else ifeq ($(call release-starts-with,Nougat),1)
override PLATFORM_RELEASE := 7.0
else ifeq ($(call release-starts-with,Oreo),1)
override PLATFORM_RELEASE := 8.0
else ifeq ($(PLATFORM_BUILDID),OC)
override PLATFORM_RELEASE := 8.0.80
else ifeq ($(shell echo $(PLATFORM_RELEASE) | grep -qE "[A-Za-z]+"; echo $$?),0)
override PLATFORM_RELEASE := 8.2
endif

# Workaround for master. Sometimes there is an AOSP version ahead of
# the current master version number, but master still has more features.
#
ifeq ($(PLATFORM_RELEASE),8.0.80)
override PLATFORM_RELEASE := 8.0
is_aosp_master := 1
endif

PLATFORM_RELEASE_MAJ   := $(shell echo $(PLATFORM_RELEASE) | cut -f1 -d'.')
PLATFORM_RELEASE_MIN   := $(shell echo $(PLATFORM_RELEASE) | cut -f2 -d'.')
PLATFORM_RELEASE_PATCH := $(shell echo $(PLATFORM_RELEASE) | cut -f3 -d'.')

# Not all versions have a patchlevel; fix that up here
#
ifeq ($(PLATFORM_RELEASE_PATCH),)
PLATFORM_RELEASE_PATCH := 0
endif

# Macros to help categorize support for features and API_LEVEL for tests.
#
is_at_least_kitkat := \
	$(shell ( test $(PLATFORM_RELEASE_MAJ) -gt 4 || \
				( test $(PLATFORM_RELEASE_MAJ) -eq 4 && \
				  test $(PLATFORM_RELEASE_MIN) -ge 4 ) ) && echo 1 || echo 0)
is_at_least_lollipop := \
	$(shell ( test $(PLATFORM_RELEASE_MAJ) -ge 5 ) && echo 1 || echo 0)
is_at_least_lollipop_mr1 := \
	$(shell ( test $(PLATFORM_RELEASE_MAJ) -gt 5 || \
				( test $(PLATFORM_RELEASE_MAJ) -eq 5 && \
				  test $(PLATFORM_RELEASE_MIN) -gt 0 ) ) && echo 1 || echo 0)
is_at_least_marshmallow := \
	$(shell ( test $(PLATFORM_RELEASE_MAJ) -ge 6 ) && echo 1 || echo 0)
is_at_least_nougat := \
	$(shell ( test $(PLATFORM_RELEASE_MAJ) -ge 7 ) && echo 1 || echo 0)
is_at_least_nougat_mr1 := \
	$(shell ( test $(PLATFORM_RELEASE_MAJ) -gt 7 || \
				( test $(PLATFORM_RELEASE_MAJ) -eq 7 && \
				  test $(PLATFORM_RELEASE_MIN) -gt 0 ) ) && echo 1 || echo 0)
is_at_least_oreo := \
	$(shell ( test $(PLATFORM_RELEASE_MAJ) -ge 8 ) && echo 1 || echo 0)

# Assume "future versions" are >7.1, but we don't really know
is_future_version := \
	$(shell ( test $(PLATFORM_RELEASE_MAJ) -gt 8 || \
				( test $(PLATFORM_RELEASE_MAJ) -eq 8 && \
				  test $(PLATFORM_RELEASE_MIN) -gt 0 ) ) && echo 1 || echo 0)

# Picking an exact match of API_LEVEL for the platform we're building
# against can avoid compatibility theming and affords better integration.
#
# This is also a good place to select the right jack toolchain.
#
ifeq ($(is_future_version),1)
JACK_VERSION ?= 4.32.CANDIDATE
API_LEVEL := 26
else ifeq ($(is_at_least_oreo),1)
ifeq ($(is_aosp_master),1)
override JACK_VERSION :=
else
JACK_VERSION ?= 4.31.CANDIDATE
endif
API_LEVEL := 26
else ifeq ($(is_at_least_nougat_mr1),1)
JACK_VERSION ?= 3.36.CANDIDATE
API_LEVEL := 25
else ifeq ($(is_at_least_nougat),1)
JACK_VERSION ?= 3.36.CANDIDATE
API_LEVEL := 24
else ifeq ($(is_at_least_marshmallow),1)
JACK_VERSION ?= 2.21.RELEASE
API_LEVEL := 23
else ifeq ($(is_at_least_lollipop_mr1),1)
# This early version had no version-file.version.code; fake it
JACK_VERSION ?= 1.0.RELEASE
API_LEVEL := 22
else ifeq ($(is_at_least_lollipop),1)
API_LEVEL := 21
#API_LEVEL := 20 was l-preview
else ifeq ($(is_at_least_kitkat),1)
API_LEVEL := 19
else
$(error Must build against Android >= 4.4)
endif

# If the NDK is enabled, check it has API_LEVEL support for us
ifneq ($(NDK_ROOT),)
 NDK_PLATFORMS_ROOT ?= $(NDK_ROOT)/platforms
 ifeq ($(strip $(wildcard $(NDK_PLATFORMS_ROOT)/android-*)),)
  $(error NDK_PLATFORMS_ROOT does not point to a valid location)
 endif
 override TARGET_PLATFORM := android-$(API_LEVEL)
 ifeq ($(strip $(wildcard $(NDK_PLATFORMS_ROOT)/$(TARGET_PLATFORM))),)
  $(error NDK support for $(TARGET_PLATFORM) is missing)
 endif
endif

# Each DDK is tested against only a single version of the platform.
# Warn if a different platform version is used.
#
ifeq ($(is_future_version),1)
$(info WARNING: Android version is newer than this DDK supports)
else ifneq ($(is_at_least_marshmallow),1)
$(info WARNING: Android version is older than this DDK supports)
endif
