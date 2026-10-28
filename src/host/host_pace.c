/* SPDX-License-Identifier: CC0-1.0 */
/* Real-time pacing of the kernel's virtual clock (docs/KERNEL.md "Virtual
 * clock": the scheduler calls the pacing hook before each idle jump). */
#include <SDL3/SDL.h>

#include "host_internal.h"

uint64_t rg_cycles_to_ns(uint64_t c)
{
    /* 1e9 / 147456000 = 15625 / 2304.  Split to avoid overflow. */
    uint64_t q = c / 2304, r = c % 2304;
    return q * 15625 + r * 15625 / 2304;
}

uint64_t rg_field_cycles(uint64_t k)
{
    /* PS2K_FIELD_SUB / PS2K_SUB = 2,460,060 (PCSX2: BUSCLK / 59.94) */
    return k * 2460060u;
}

static uint64_t sdl_now(void *u) { (void)u; return SDL_GetTicksNS(); }
static void sdl_sleep(void *u, uint64_t ns) { (void)u; SDL_DelayPrecise(ns); }

void rg_pacer_init(rg_pacer *p, int throttle)
{
    SDL_memset(p, 0, sizeof *p);
    p->throttle = throttle;
    p->max_lag_ns = 250000000u;
    p->now_ns = sdl_now;
    p->sleep_ns = sdl_sleep;
}

void rg_pacer_reset(rg_pacer *p) { p->anchored = 0; }

void rg_pacer_hook(uint64_t from_cycles, uint64_t to_cycles, void *user)
{
    rg_pacer *p = (rg_pacer *)user;
    if (!p->throttle) return;
    uint64_t now = p->now_ns(p->clock_user);
    if (!p->anchored || from_cycles < p->anchor_cycles) {
        /* first call, or virtual time went backwards (a fresh kernel run) */
        p->anchored = 1;
        p->anchor_cycles = from_cycles;
        p->anchor_ns = now;
    }
    uint64_t target = p->anchor_ns + rg_cycles_to_ns(to_cycles - p->anchor_cycles);
    if (now >= target) {
        if (now - target > p->max_lag_ns) {
            /* too far behind (debugger, load hitch): drop the debt instead of
             * running flat out to catch up */
            p->anchor_cycles = to_cycles;
            p->anchor_ns = now;
            p->resyncs++;
        }
        return;
    }
    uint64_t d = target - now;
    p->sleeps++;
    p->slept_ns += d;
    p->sleep_ns(p->clock_user, d);
}
