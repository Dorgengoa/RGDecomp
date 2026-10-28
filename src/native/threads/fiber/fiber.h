/* SPDX-License-Identifier: CC0-1.0
 *
 * Host fiber backend interface for the EE kernel HLE (docs/KERNEL.md).
 *
 * The scheduler needs exactly four operations: adopt the calling host thread
 * as the "scheduler" fiber, create a fiber with its own host stack, switch to
 * a fiber, and destroy a fiber that is not running.  Exactly one backend is
 * compiled in: fiber_win32.c (Windows Fibers API) or fiber_ucontext.c
 * (POSIX ucontext; untested so far).
 */
#ifndef PS2K_FIBER_H
#define PS2K_FIBER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ps2k_fiber ps2k_fiber;
typedef void (*ps2k_fiber_fn)(void *arg);

/* Adopt the calling host thread as a fiber (the scheduler fiber).  Returns
 * NULL on failure.  Must be paired with ps2k_fiber_release_host(). */
ps2k_fiber *ps2k_fiber_adopt_host(void);
void        ps2k_fiber_release_host(ps2k_fiber *host);

/* Create a fiber that will run fn(arg) on a fresh host stack of at least
 * stack_size bytes the first time it is switched to.  fn must never return
 * (the kernel's trampoline ends by switching away for good). */
ps2k_fiber *ps2k_fiber_create(size_t stack_size, ps2k_fiber_fn fn, void *arg);

/* Switch from the currently running fiber (`from`) to `to`.  Returns when
 * some other fiber switches back to `from`. */
void ps2k_fiber_switch(ps2k_fiber *from, ps2k_fiber *to);

/* Destroy a fiber that is not currently running. */
void ps2k_fiber_destroy(ps2k_fiber *f);

const char *ps2k_fiber_backend_name(void);

#ifdef __cplusplus
}
#endif
#endif
