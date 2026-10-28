/* SPDX-License-Identifier: CC0-1.0
 * The spin stage's runtime (src/ps2/spin/spin.h, docs/SPIN.md) for the native kernel table
 * (RG_NATIVE_ONLY builds: target rg_native_spin replaces rg_ps2_spin).
 *
 * A HANDLER-FLAG busy-wait waits for something else to change memory.  Natively nothing
 * else runs inside a flow, so a hint is a frame-driver point (the driven steps it may wait
 * for run there) followed by one iteration's worth of logic time as a timed wait
 * (ps2k_charge from a flow: the event pass, handlers and the other flow run meanwhile).
 * The per-site statistics and reports are the HLE-era runtime's (src/ps2/spin/spin.c),
 * without its virtual-cycle charge model. */
#include <stdio.h>
#include <stdlib.h>

#include "ps2k.h"
#include "rg_threads.h"
#include "spin.h"

#define SLOTS 256

typedef struct {
    uint32_t site;
    uint8_t  used, reported;
    uint64_t total, episode_iters, episode_start, last_now;
} slot;

static rg_spin_config    g_cfg = {32u, 1474560000ull};
static rg_spin_report_fn g_hook;
static void             *g_hook_user;
static slot              g_slots[SLOTS];
static uint64_t          g_total;

void rg_spin_default_config(rg_spin_config *cfg)
{
    cfg->cycles_per_iter = 32u;
    cfg->report_cycles = 10ull * PS2K_BUSCLK;
}

void rg_spin_configure(const rg_spin_config *cfg)
{
    g_cfg = *cfg;
    if (!g_cfg.cycles_per_iter)
        g_cfg.cycles_per_iter = 1;
}

void rg_spin_set_report_hook(rg_spin_report_fn fn, void *user)
{
    g_hook = fn;
    g_hook_user = user;
}

void rg_spin_reset(void)
{
    for (int i = 0; i < SLOTS; i++)
        g_slots[i].used = 0;
    g_total = 0;
}

static slot *slot_of(uint32_t site)
{
    uint32_t h = (site * 2654435761u) >> 24;
    for (int i = 0; i < SLOTS; i++) {
        slot *s = &g_slots[(h + (uint32_t)i) % SLOTS];
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
    return NULL;
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
    slot *s = slot_of(site);
    g_total++;
    if (s) {
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
    rg_frame_point();                 /* the driven steps a spin may wait for */
    ps2k_charge(g_cfg.cycles_per_iter); /* natively: a timed wait (the pass runs meanwhile) */
    if (s)
        s->last_now = ps2k_now();
}

void rg_spin_halt(uint32_t site)
{
    slot *s = slot_of(site);
    g_total++;
    if (s)
        s->total++;
    report(RG_SPIN_HALT, site, s ? s->total : 0);
    for (;;) /* the hook returned: park this flow for good, as retail spins here for good */
        ps2k_sleep_thread();
}

uint64_t rg_spin_iterations(uint32_t site)
{
    for (int i = 0; i < SLOTS; i++)
        if (g_slots[i].used && g_slots[i].site == site)
            return g_slots[i].total;
    return 0;
}

uint64_t rg_spin_total(void) { return g_total; }
