/* SPDX-License-Identifier: CC0-1.0
 * Fixed-address fiber backend (fiber_arena.c, ps2k_ss.h).  The platform
 * backend (fiber_win32.c) delegates to it while an arena is set. */
#ifndef PS2K_FIBER_ARENA_H
#define PS2K_FIBER_ARENA_H

#include "fiber.h"

int         fa_on(void);
ps2k_fiber *fa_adopt_host(void);
void        fa_release_host(ps2k_fiber *host);
ps2k_fiber *fa_create(size_t stack_size, ps2k_fiber_fn fn, void *arg);
void        fa_switch(ps2k_fiber *from, ps2k_fiber *to);
void        fa_destroy(ps2k_fiber *f);

#endif
