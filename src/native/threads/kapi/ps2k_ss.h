/* SPDX-License-Identifier: CC0-1.0
 *
 * Kernel side of port save states (docs/TEST-FIXTURES.md "Save states").
 *
 * 1. Fixed-address fiber stacks.  A guest thread suspended at a field boundary
 *    is a host call chain on its fiber stack (return addresses, saved
 *    registers, pointers to its own locals).  A save state can only restore it
 *    if the stack comes back at the same address, and Windows fibers
 *    (CreateFiberEx) neither take a caller-provided stack nor expose their
 *    saved context.  ps2k_fiber_arena_set() switches the fiber backend to
 *    stacks carved from one caller-reserved range at a fixed address, with an
 *    own register switch (i686 Windows: callee-saved registers, the TEB stack
 *    bounds and SEH head, x87 control word, MXCSR).  The slot table, every
 *    saved context and every stack live inside the range, so a save is the
 *    range's header plus each live stack from its saved stack pointer up.
 *    Only i686 Windows has the arena; elsewhere ps2k_fiber_arena_set fails and
 *    the normal backend stays.
 *
 * 2. Kernel state (K): ps2k_ss_save copies the kernel state; ps2k_ss_load
 *    restores it and keeps the loading process's own host bindings (the
 *    scheduler fiber, VBlank observers, devices, trace / pacing / violation
 *    hooks), which are registered by that process's init, not by the game.
 *
 * Original CC0 code.
 */
#ifndef PS2K_SS_H
#define PS2K_SS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Use [base, base + size) for fiber stacks from now on.  The range must be
 * reserved (MEM_RESERVE) by the caller; pages are committed per slot.  Call
 * before the first ps2k_start.  0 ok, -1 unsupported / bad range / too late. */
int ps2k_fiber_arena_set(void *base, size_t size);
int ps2k_fiber_arena_on(void);
/* The slot table at the start of the range (always saved whole). */
void ps2k_fiber_arena_header(void **p, size_t *n);
/* The live part [lo, hi) of every created fiber stack except the running one
 * (its saved stack pointer up to the stack top).  Returns the count. */
int ps2k_fiber_arena_stacks(uintptr_t (*out)[2], int cap);
/* Commit the pages of [lo, hi) inside the arena (before writing a stack back). */
int ps2k_fiber_arena_commit(uintptr_t lo, uintptr_t hi);

/* Kernel state.  Only between fields: no guest thread running
 * (ps2k_step returned).  ps2k_ss_load keeps this process's host bindings. */
size_t ps2k_ss_size(void);
int ps2k_ss_save(void *buf, size_t cap);          /* bytes written, -1 */
int ps2k_ss_load(const void *buf, size_t n);      /* 0, -1 (size / not between fields) */

#ifdef __cplusplus
}
#endif
#endif
