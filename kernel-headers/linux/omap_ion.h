/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef _LINUX_OMAP_ION_H
#define _LINUX_OMAP_ION_H
#include <linux/types.h>
struct omap_ion_tiler_alloc_data {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 size_t w;
 size_t h;
 int fmt;
 unsigned int flags;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct ion_handle *handle;
 size_t stride;
 size_t offset;
 __u32 out_align;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 __u32 token;
};
enum {
 OMAP_ION_HEAP_SYSTEM = ION_HEAP_TYPE_CUSTOM + 1,
 OMAP_ION_HEAP_SECURE_INPUT,
 OMAP_ION_HEAP_TILER,
 OMAP_ION_HEAP_NONSECURE_TILER,
 OMAP_ION_HEAP_TILER_RESERVATION,
};
#define OMAP_ION_HEAP_TILER_MASK (1 << OMAP_ION_HEAP_TILER)
#define OMAP_ION_HEAP_NONSECURE_TILER_MASK (1 << OMAP_ION_HEAP_NONSECURE_TILER)
#define OMAP_ION_HEAP_TILER_RESERVATION_MASK (1 << OMAP_ION_HEAP_TILER_RESERVATION)
enum {
 OMAP_ION_TILER_ALLOC,
};
enum {
 TILER_PIXEL_FMT_MIN = 0,
 TILER_PIXEL_FMT_8BIT = 0,
 TILER_PIXEL_FMT_16BIT = 1,
 TILER_PIXEL_FMT_32BIT = 2,
 TILER_PIXEL_FMT_PAGE = 3,
 TILER_PIXEL_FMT_MAX = 3
};
#endif
