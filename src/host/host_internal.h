/* SPDX-License-Identifier: CC0-1.0 */
/* Shared helpers inside src/host (not part of the public API). */
#ifndef RG_HOST_INTERNAL_H
#define RG_HOST_INTERNAL_H

#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>

#include "host.h"

static inline void rgh_err(char *err, size_t cap, const char *fmt, ...)
{
    if (!err || !cap) return;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(err, cap, fmt, ap);
    va_end(ap);
}

/* Reads a whole file (NUL-terminated); NULL on failure.  free() it. */
char *rgh_read_file(const char *path, size_t *len);

#endif
