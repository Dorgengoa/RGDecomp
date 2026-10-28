/* SPDX-License-Identifier: CC0-1.0
 * rg_spin: runtime side of ingest stage `spin` (docs/SPIN.md).
 *
 * The stage puts rg_spin_hint(SITE) in every busy-wait loop that
 * census/spin_loops.tsv classes HANDLER-FLAG (it waits for an interrupt
 * handler, another thread or the IOP to change memory), and rg_spin_halt(SITE)
 * in every HALT loop (a deliberate infinite loop: retail hangs there for
 * good).  SITE = (image index << 28) | retail loop-head address.
 *
 * rg_spin_hint() is one loop iteration's worth of virtual time:
 * ps2k_charge(cycles_per_iter), which also processes due events and delivers
 * interrupts (and so may switch to a thread a handler readied).  The charge
 * depends only on the iteration count, so a run stays a pure function of its
 * inputs.  Long waits are reported (once per episode) through a hook; a
 * thread that spins with interrupts disabled, or inside a handler, can never
 * be released and is reported at once.
 */
#ifndef RG_SPIN_H
#define RG_SPIN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rg_spin_config {
    uint32_t cycles_per_iter;  /* virtual bus cycles charged per hint (default 32) */
    uint64_t report_cycles;    /* report a wait longer than this (default 10 s virtual; 0 = never) */
} rg_spin_config;

enum {
    RG_SPIN_LONG_WAIT = 1,  /* one episode at a site exceeded report_cycles */
    RG_SPIN_DI,             /* spinning with EIE = 0: no interrupt can end it */
    RG_SPIN_IN_HANDLER,     /* spinning inside an interrupt handler */
    RG_SPIN_HALT            /* a HALT loop was entered (retail hangs here) */
};
typedef void (*rg_spin_report_fn)(int what, uint32_t site, uint64_t iterations, void *user);

void rg_spin_default_config(rg_spin_config *cfg);
void rg_spin_configure(const rg_spin_config *cfg);
/* Default hook prints to stderr.  For RG_SPIN_HALT the default then abort()s;
 * with a custom hook installed the halted thread is parked (SleepThread
 * forever) after the hook returns. */
void rg_spin_set_report_hook(rg_spin_report_fn fn, void *user);
void rg_spin_reset(void);              /* clear per-site statistics */

void rg_spin_hint(uint32_t site);      /* called by stage `spin` */
void rg_spin_halt(uint32_t site);      /* called by stage `spin`; never returns */

/* statistics (tests, trace tools) */
uint64_t rg_spin_iterations(uint32_t site);   /* total hints at a site */
uint64_t rg_spin_total(void);                 /* total hints, all sites */

#ifdef __cplusplus
}
#endif
#endif
