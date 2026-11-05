/* SPDX-License-Identifier: CC0-1.0
 * Host-clock pacing of the frame driver: the bounded fixed-step accumulator (rg_pace.h,
 * docs/NATIVE-THREADS.md "Paced mode"). */
#include "rg_pace.h"

#include <string.h>

#define NS_U 2304ull /* 1 ns in accumulator units */

void rg_pace_default_config(rg_pace_config *c)
{
    memset(c, 0, sizeof *c);
    c->mode = RG_PACE_RETAIL;
    c->max_ticks = 4;
    c->catchup = 2;
}

static void sanitize(rg_pace_config *c)
{
    if (c->max_ticks < 1)
        c->max_ticks = 1;
    if (c->max_ticks > 60)
        c->max_ticks = 60;
    if (c->catchup < 1)
        c->catchup = 1;
    if (c->catchup > c->max_ticks)
        c->catchup = c->max_ticks;
    if (c->mode != RG_PACE_HOST)
        c->mode = RG_PACE_RETAIL;
}

void rg_pace_init(rg_pace *p, const rg_pace_config *c)
{
    memset(p, 0, sizeof *p);
    if (c)
        p->cfg = *c;
    else
        rg_pace_default_config(&p->cfg);
    sanitize(&p->cfg);
}

void rg_pace_configure(rg_pace *p, const rg_pace_config *c)
{
    int mode = p->cfg.mode;
    p->cfg = *c;
    sanitize(&p->cfg);
    if (p->cfg.mode != mode)
        rg_pace_reset(p);
    if (!p->cfg.cap_fps)
        p->next_present_ns = 0;
}

void rg_pace_reset(rg_pace *p)
{
    p->anchored = 0;
    p->acc = 0;
    p->next_present_ns = 0;
}

static uint64_t speed_q16(const rg_pace *p) { return p->speed_q16 ? p->speed_q16 : 65536u; }

void rg_pace_set_speed(rg_pace *p, double speed)
{
    if (!(speed >= 1.0)) speed = 1.0;
    if (speed > 8.0) speed = 8.0;
    p->speed_q16 = (uint32_t)(speed * 65536.0 + 0.5);
}

/* the frame cap in effect: with no cap a sped-up battle (gameplay.battle_speed) presents at most
 * at speed_cap_fps (display.frame_rate original: 60, once per host phase-time, not per phase) */
static uint32_t cap_fps(const rg_pace *p)
{
    /* (with VSync the display paces the presents) */
    return p->cfg.cap_fps ? p->cfg.cap_fps : speed_q16(p) > 65536u && !p->cfg.vsync ? p->cfg.speed_cap_fps : 0u;
}
/* phase counts that bound a batch scale with the battle speed: k phases (and the catch-up
 * threshold) per host phase-time of debt, so a sped-up battle on a 60 Hz present grid is not
 * cut back to max_ticks phases per present */
static uint32_t scaled(const rg_pace *p, uint32_t n) { return (uint32_t)(((uint64_t)n * speed_q16(p) + 65535u) / 65536u); }

static uint64_t cap_ns(const rg_pace *p) { return cap_fps(p) ? 1000000000ull / cap_fps(p) : 0; }

/* a present slot counts as come this close before it (sleep / wake jitter) */
static uint64_t slack_ns(const rg_pace *p)
{
    uint64_t q = cap_ns(p) / 4;
    return q < 2000000ull ? q : 2000000ull;
}

static void accumulate(rg_pace *p, uint64_t now_ns)
{
    if (!p->anchored) {
        p->anchored = 1;
        p->last_ns = now_ns;
        if (!p->t0_ns)
            p->t0_ns = now_ns;
        p->acc = RG_PACE_FIELD_U; /* the first phase is owed at once */
        return;
    }
    if (now_ns > p->last_ns) {
        uint64_t d = now_ns - p->last_ns;
        if (speed_q16(p) == 65536u) {
            p->acc += d * NS_U;
        } else {
            /* gameplay.battle_speed: host time owes phases faster (a long hitch is capped
             * before scaling; the debt beyond k phases is dropped below anyway) */
            if (d > 1000000000ull) d = 1000000000ull;
            p->acc += d * NS_U / 65536u * speed_q16(p) + (d * NS_U % 65536u) * speed_q16(p) / 65536u;
        }
        p->last_ns = now_ns;
    }
    uint64_t lim = (uint64_t)scaled(p, p->cfg.max_ticks) * RG_PACE_FIELD_U;
    if (p->acc > lim) {
        /* a hitch longer than k phases (debugger, load, window drag): the older debt is
         * dropped; logic never runs faster than k phases back to back */
        uint64_t over = p->acc - lim;
        p->dropped_u += over;
        p->dropped_ticks = p->dropped_u / RG_PACE_FIELD_U;
        if (over >= RG_PACE_FIELD_U)
            p->resyncs++; /* a real hitch (not a host merely slower than 59.94 Hz) */
        p->acc = lim;
    }
}

uint64_t rg_pace_until_tick(rg_pace *p, uint64_t now_ns)
{
    if (p->cfg.mode != RG_PACE_HOST)
        return 0;
    accumulate(p, now_ns);
    if (p->acc >= RG_PACE_FIELD_U) {
        p->phase_start_ns = now_ns;
        return 0;
    }
    uint64_t ns = (RG_PACE_FIELD_U - p->acc + NS_U - 1) / NS_U;
    return speed_q16(p) == 65536u ? ns : (ns * 65536u + speed_q16(p) - 1) / speed_q16(p) + 1;
}

void rg_pace_take_tick(rg_pace *p)
{
    p->ticks++;
    p->batch++;
    if (p->cfg.mode == RG_PACE_HOST)
        p->acc = p->acc >= RG_PACE_FIELD_U ? p->acc - RG_PACE_FIELD_U : 0;
}

/* the phase's host cost, averaged over ~8 phases (a 2-VBlank game alternates a heavy and a
 * light phase) */
static void cost_sample(rg_pace *p, uint64_t now_ns)
{
    if (!p->phase_start_ns || now_ns <= p->phase_start_ns)
        return;
    uint64_t c = now_ns - p->phase_start_ns;
    if (c > 4 * (RG_PACE_FIELD_U / NS_U))
        c = 4 * (RG_PACE_FIELD_U / NS_U); /* a hitch is not the host's speed */
    p->cost_ns = p->cost_ns ? p->cost_ns - p->cost_ns / 8 + c / 8 : c;
}

void rg_pace_phase_done(rg_pace *p, uint64_t now_ns)
{
    if (p->cfg.mode != RG_PACE_HOST || p->cfg.cost_at_decision)
        return;
    p->cost_ext = 1;
    cost_sample(p, now_ns);
}

int rg_pace_present_now(rg_pace *p, uint64_t now_ns)
{
    if (p->cfg.mode != RG_PACE_HOST)
        return 1;
    accumulate(p, now_ns);
    if (!p->cost_ext)
        cost_sample(p, now_ns); /* no rg_pace_phase_done caller: start -> this decision */
    /* a sped-up battle (gameplay.battle_speed): run the phases already owed before a present
     * (several per present by design) */
    if (speed_q16(p) > 65536u) {
        /* at most ceil(speed) phases per present: a host that cannot keep the full speed runs the
         * battle slower but keeps presenting (the debt beyond is dropped), instead of batches
         * of k x speed phases that are never shown */
        if (p->acc >= RG_PACE_FIELD_U && p->batch < scaled(p, 1))
            return 0;
        if (p->batch >= scaled(p, 1))
            goto cap;
    }
    if (p->acc >= (uint64_t)p->cfg.catchup * RG_PACE_FIELD_U) { /* well behind: catch up first */
        /* only when skipping presents can win the time back: a phase costs < 90 % of one */
        int can = p->cost_ns * 10 * speed_q16(p) / 65536u < 9 * (RG_PACE_FIELD_U / NS_U);
        if (!can && p->cfg.catchup > 1) {
            p->skipped_slow++;
        } else {
            if (p->batch < p->cfg.max_ticks)
                return 0;
            p->forced++; /* k phases without a present: show one anyway */
        }
    }
cap:
    /* (phase-rate presents: the cap must keep up with the phases, 59.94 Hz x battle speed) */
    if (cap_fps(p) && !(p->cfg.phase_rate && (uint64_t)cap_fps(p) * 65536u >= 60u * speed_q16(p)) &&
        p->next_present_ns &&
        now_ns + slack_ns(p) < p->next_present_ns)
        return 0;
    return 1;
}

void rg_pace_presented(rg_pace *p, uint64_t now_ns)
{
    if (p->batch > 0 || p->cfg.mode != RG_PACE_HOST)
        p->hist[p->batch < RG_PACE_HIST - 1 ? p->batch : RG_PACE_HIST - 1]++;
    else
        p->between_presents++;
    p->presents++;
    p->batch = 0;
    uint64_t iv = cap_ns(p);
    if (iv) {
        /* slots on a fixed grid (lateness does not accumulate); re-anchor when a whole slot
         * was missed */
        if (!p->next_present_ns || now_ns >= p->next_present_ns + iv)
            p->next_present_ns = now_ns + iv;
        else
            p->next_present_ns += iv;
    }
}

int rg_pace_between(rg_pace *p, uint64_t now_ns, uint32_t *alpha)
{
    if (p->cfg.mode != RG_PACE_HOST)
        return 0;
    accumulate(p, now_ns);
    if (p->acc >= RG_PACE_FIELD_U)
        return 0; /* a phase is owed: run it first */
    if (alpha)
        *alpha = (uint32_t)((p->acc >> 16) * 65536ull / (RG_PACE_FIELD_U >> 16));
    if (cap_fps(p) && p->next_present_ns && now_ns + slack_ns(p) < p->next_present_ns)
        return 0;
    return 1;
}

uint64_t rg_pace_sleep_ns(const rg_pace *p, uint64_t until_tick_ns, uint64_t now_ns, int between)
{
    if (!between || p->cfg.mode != RG_PACE_HOST)
        return until_tick_ns;
    if (!cap_fps(p))
        return p->cfg.vsync ? until_tick_ns : 0; /* uncapped: present as fast as the presenter can */
    if (p->next_present_ns > now_ns && p->next_present_ns - now_ns < until_tick_ns)
        return p->next_present_ns - now_ns;
    return p->next_present_ns > now_ns ? until_tick_ns : 0;
}
