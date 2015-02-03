#DOMX is not supported on J6 yet. Supported only on omap4 and omap5
ifeq ($(TARGET_BOARD_PLATFORM), $(filter $(TARGET_BOARD_PLATFORM), omap4 omap5))
ifeq ($(ENHANCED_DOMX),true)

    # DOMX not used in OMAP3 program
    ifneq ($(TARGET_BOARD_PLATFORM),omap3)

        LOCAL_PATH:= $(call my-dir)
        OMAP4_DEBUG_MEMLEAK:= false

        ifeq ($(OMAP4_DEBUG_MEMLEAK),true)

            OMAP4_DEBUG_CFLAGS:= -DHEAPTRACKER
            OMAP4_DEBUG_LDFLAGS:= $(foreach f, $(strip malloc realloc calloc free), -Wl,--wrap=$(f))
            OMAP4_DEBUG_SHARED_LIBRARIES:= liblog
            BUILD_HEAPTRACKED_SHARED_LIBRARY:= $(HARDWARE_TI_OMAP4_BASE)/heaptracked-shared-library.mk
            BUILD_HEAPTRACKED_EXECUTABLE:= $(HARDWARE_TI_OMAP4_BASE)/heaptracked-executable.mk

            LOCAL_PATH:= $(call my-dir)
            include $(CLEAR_VARS)
            LOCAL_SRC_FILES:= heaptracker.c stacktrace.c mapinfo.c
            LOCAL_MODULE:= libheaptracker
            LOCAL_MODULE_TAGS:= optional
            include $(BUILD_STATIC_LIBRARY)

            include $(CLEAR_VARS)
            LOCAL_SRC_FILES:= tm.c
            LOCAL_MODULE:= tm
            LOCAL_MODULE_TAGS:= test
            include $(BUILD_HEAPTRACKED_EXECUTABLE)

        else
            BUILD_HEAPTRACKED_SHARED_LIBRARY:=$(BUILD_SHARED_LIBRARY)
            BUILD_HEAPTRACKED_EXECUTABLE:= $(BUILD_EXECUTABLE)
        endif

        include $(call first-makefiles-under,$(LOCAL_PATH))
    endif # ifeq ($(TARGET_BOARD_PLATFORM),omap4)

endif #ifeq ($(ENHANCED_DOMX),true)
endif
