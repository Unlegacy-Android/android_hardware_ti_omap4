#ifndef __ION_TI_CUSTOM_H
#define __ION_TI_CUSTOM_H

#include <linux/omap_ion.h>

__BEGIN_DECLS

int ion_alloc_tiler(int fd, size_t w, size_t h, int fmt, unsigned int flags,
            ion_user_handle_t*handle, size_t *stride);

__END_DECLS

#endif /* __ION_TI_CUSTOM_H */
