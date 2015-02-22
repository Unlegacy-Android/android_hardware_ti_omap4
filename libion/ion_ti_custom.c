/*
 *  ion.c
 *
 * Memory Allocator functions for ion
 *
 * Copyright (C) Texas Instruments - http://www.ti.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <cutils/log.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>

#include <linux/ion.h>
#include <linux/omap_ion.h>
#include <ion/ion.h>

static int ion_ioctl(int fd, int req, void *arg)
{
        int ret = ioctl(fd, req, arg);
        if (ret < 0) {
                ALOGE("ioctl %x failed with code %d: %s\n", req,
                       ret, strerror(errno));
                return -errno;
        }
        return ret;
}


int ion_alloc_tiler(int fd, size_t w, size_t h, int fmt, unsigned int flags,
            ion_user_handle_t*handle, size_t *stride)
{
        int ret;
        struct omap_ion_tiler_alloc_data alloc_data = {
                .w = w,
                .h = h,
                .fmt = fmt,
                .flags = flags,
                .out_align = PAGE_SIZE,
                .token = 0,
        };

        struct ion_custom_data custom_data = {
                .cmd = OMAP_ION_TILER_ALLOC,
                .arg = (unsigned long)(&alloc_data),
        };

        ret = ion_ioctl(fd, ION_IOC_CUSTOM, &custom_data);
        if (ret < 0)
                return ret;
        *stride = alloc_data.stride;
        *handle = alloc_data.handle;
        return ret;
}

