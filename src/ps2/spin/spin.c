/* SPDX-License-Identifier: CC0-1.0
 * rg_spin: runtime side of ingest stage `spin`.  See spin.h and docs/SPIN.md.
 */
#include "spin.h"

#include <stdio.h>
#include <stdlib.h>

#include "ps2k.h"
#include "rg_threads.h" /* frame driver (src/native/threads) */

#define RG_SPIN_SLOTS 256 /* open addressing; the census lists ~25 sites */

typedef struct {
    uint32_t site;
    uint8_t  used;
    uint8_t  reported;
    uint64_t total;
    uint64_t episode_iters;
    uint64_t episode_start;
    uint64_t last_now;
} spin_slot;

static rg_spin_config    g_cfg = {32u, 1474560000ull};
static rg_spin_report_fn g_hook;
static void             *g_hook_user;
static spin_slot         g_slots[RG_SPIN_SLOTS];
static uint64_t          g_total;

void rg_spin_default_config(rg_spin_config *cfg)
{
    cfg->cycles_per_iter = 32u;
    cfg->report_cycles = 10ull * PS2K_BUSCLK;
}

void rg_spin_configure(const rg_spin_config *cfg)
{
    g_cfg = *cfg;
    if (g_cfg.cycles_per_iter == 0)
        g_cfg.cycles_per_iter = 1;
}

void rg_spin_set_report_hook(rg_spin_report_fn fn, void *user)
{
    g_hook = fn;
    g_hook_user = user;
}

void rg_spin_reset(void)
{
    for (int i = 0; i < RG_SPIN_SLOTS; i++)
        g_slots[i].used = 0;
    g_total = 0;
}

static spin_slot *slot_of(uint32_t site)
{
    uint32_t h = (site * 2654435761u) >> 24;
    for (int i = 0; i < RG_SPIN_SLOTS; i++) {
        spin_slot *s = &g_slots[(h + (uint32_t)i) % RG_SPIN_SLOTS];
        if (!s->used) {
            s->used = 1;
            s->site = site;
            s->total = s->episode_iters = 0;
            s->reported = 0;
            s->episode_start = s->last_now = ps2k_now();
            return s;
        }
        if (s->site == site)
            return s;
    }
    return NULL; /* table full: statistics only are lost */
}

static void report(int what, uint32_t site, uint64_t iters)
{
    static const char *const names[] = {"?", "long wait", "spin with interrupts disabled",
                                        "spin inside an interrupt handler", "HALT loop entered"};
    if (g_hook) {
        g_hook(what, site, iters, g_hook_user);
        return;
    }
    fprintf(stderr, "rg_spin: %s at site 0x%08X (image %u, retail 0x%07X) after %llu iterations, t=%llu\n",
            names[what], (unsigned)site, (unsigned)(site >> 28), (unsigned)(site & 0x0FFFFFFF),
            (unsigned long long)iters, (unsigned long long)ps2k_now());
    if (what == RG_SPIN_HALT)
        abort();
}

void rg_spin_hint(uint32_t site)
{
    uint64_t now = ps2k_now();
    spin_slot *s = slot_of(site);
    g_total++;
    if (s) {
        /* a new episode starts when the site was last seen long ago */
        if (now - s->last_now > 64ull * g_cfg.cycles_per_iter) {
            s->episode_iters = 0;
            s->episode_start = now;
            s->reported = 0;
        }
        s->total++;
        s->episode_iters++;
        if (!s->reported) {
            if (ps2k_in_handler()) {
                s->reported = 1;
                report(RG_SPIN_IN_HANDLER, site, s->episode_iters);
            } else if (!(ps2k_cop0_status() & 0x10000u) && s->episode_iters > 1) {
                s->reported = 1;
                report(RG_SPIN_DI, site, s->episode_iters);
            } else if (g_cfg.report_cycles && now - s->episode_start > g_cfg.report_cycles) {
                s->reported = 1;
                report(RG_SPIN_LONG_WAIT, site, s->episode_iters);
            }
        }
    }
    /* native threads: a spin is a frame-driver point (the driven steps it may wait
     * for run here; docs/NATIVE-THREADS.md) */
    if (rg_frame_native())
        rg_frame_point();
    /* one iteration's worth of virtual time; delivers due interrupts and
     * switches to a thread a handler readied (ps2k_poll semantics) */
    ps2k_charge(g_cfg.cycles_per_iter);
    if (s)
        s->last_now = ps2k_now();
}

void rg_spin_halt(uint32_t site)
{
    spin_slot *s = slot_of(site);
    g_total++;
    if (s)
        s->total++;
    report(RG_SPIN_HALT, site, s ? s->total : 0);
    /* hook returned (tests, tools): park this thread for good, as retail
     * would spin here for good; other threads keep running */
    for (;;)
        ps2k_sleep_thread();
}

uint64_t rg_spin_iterations(uint32_t site)
{
    for (int i = 0; i < RG_SPIN_SLOTS; i++)
        if (g_slots[i].used && g_slots[i].site == site)
            return g_slots[i].total;
    return 0;
}

uint64_t rg_spin_total(void)
{
    return g_total;
}
