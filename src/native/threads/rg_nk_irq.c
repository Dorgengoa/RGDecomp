/* SPDX-License-Identifier: CC0-1.0
 * The native kernel table, part 2 (docs/NATIVE-THREADS.md "Native kernel table"): the
 * logic clock and its event list (VBlank edges, timed waits, posted causes), the
 * game-visible handler ids with their chains and the INTC / DMAC STAT / MASK latch
 * (delivered only in the driver's pass, as explicit calls), the timers T0..T3 over logic
 * time (a flow's own work costs nothing: T0_COUNT reads give the nominal frame profile).
 *
 * Nothing becomes due inside a flow: ps2k_poll is a no-op, ps2k_charge from a flow is a
 * timed wait (the callers that still charge wait for time to pass: memory-card / DMA-busy
 * polls, spin hints), EI / EnableIntc are not delivery points. */
#include <string.h>

#include "rg_nk_internal.h"

/* ======================================================================
 * clock (exact NTSC field arithmetic, the same grid as the HLE: PS2K_FIELD_SUB)
 * ==================================================================== */

uint64_t nk_hsync_index(uint64_t t) { return t * PS2K_SUB / PS2K_HSYNC_SUB; }

static uint64_t hsync_time(uint64_t k) { return (k * PS2K_HSYNC_SUB + PS2K_SUB - 1) / PS2K_SUB; }

static uint64_t vbs_time(uint64_t k)
{
    return (k * PS2K_FIELD_SUB + (uint64_t)NK.cfg.vblank_start_line * PS2K_HSYNC_SUB) / PS2K_SUB;
}

static uint64_t vbe_time(uint64_t k) { return ((k + 1) * PS2K_FIELD_SUB) / PS2K_SUB; }

uint64_t ps2k_now(void) { return NK.now; }
uint64_t ps2k_hsync_count(void) { return nk_hsync_index(NK.now); }
uint64_t ps2k_vblank_count(void) { return NK.vblank_count; }
uint64_t ps2k_vblank_end_count(void) { return NK.vbe_k; }

void ps2k_set_pacing_hook(ps2k_pacing_fn fn, void *user)
{
    NK.pacing = fn;
    NK.pacing_user = user;
}

uint32_t ps2k_vblank_start_line(void) { return NK.cfg.vblank_start_line; }
int ps2k_vblank_enabled(void) { return NK.cfg.vblank_enable != 0; }
uint64_t ps2k_vblank_start_time(uint64_t field) { return vbs_time(field); }
uint64_t ps2k_vblank_end_time(uint64_t field) { return vbe_time(field); }

/* ======================================================================
 * VBlank observers and devices (platform glue)
 * ==================================================================== */

int ps2k_add_vblank_observer(ps2k_vblank_fn fn, void *user)
{
    if (!fn || NK.nobs >= PS2K_MAX_OBSERVERS)
        return PS2K_ERR;
    nkobserver *o = &NK.obs[NK.nobs++];
    o->id = ++NK.next_glue_id;
    o->fn = fn;
    o->user = user;
    return o->id;
}

int ps2k_remove_vblank_observer(int id)
{
    for (int i = 0; i < NK.nobs; i++) {
        if (NK.obs[i].id == id) {
            memmove(&NK.obs[i], &NK.obs[i + 1], (size_t)(NK.nobs - i - 1) * sizeof(nkobserver));
            NK.nobs--;
            return id;
        }
    }
    return PS2K_ERR;
}

/* A device: a model with its own completion clock (the oracle builds' CDVD sector model;
 * no native service needs one: SIF / CD completions are native, docs/NATIVE-IOP.md) */
int ps2k_add_device(const ps2k_device *dev)
{
    if (!dev || !dev->poll || NK.ndev >= PS2K_MAX_DEVICES)
        return PS2K_ERR;
    nkdevice *d = &NK.dev[NK.ndev++];
    d->id = ++NK.next_glue_id;
    d->d = *dev;
    return d->id;
}

int ps2k_remove_device(int id)
{
    for (int i = 0; i < NK.ndev; i++) {
        if (NK.dev[i].id == id) {
            memmove(&NK.dev[i], &NK.dev[i + 1], (size_t)(NK.ndev - i - 1) * sizeof(nkdevice));
            NK.ndev--;
            return id;
        }
    }
    return PS2K_ERR;
}

/* ======================================================================
 * event list: sorted by (time, insertion order) -> deterministic
 * ==================================================================== */

int nk_ev_add(uint64_t time, int kind, int a)
{
    if (NK.nev >= NKEVMAX)
        return -1;
    nkevent e;
    e.time = time;
    e.seq = NK.ev_seq++;
    e.kind = kind;
    e.a = a;
    int i = NK.nev;
    while (i > 0 && NK.ev[i - 1].time > time)
        i--;
    memmove(&NK.ev[i + 1], &NK.ev[i], (size_t)(NK.nev - i) * sizeof(nkevent));
    NK.ev[i] = e;
    NK.nev++;
    return 0;
}

void nk_ev_remove(int kind, int a)
{
    int j = 0;
    for (int i = 0; i < NK.nev; i++) {
        if (NK.ev[i].kind == kind && NK.ev[i].a == a)
            continue;
        NK.ev[j++] = NK.ev[i];
    }
    NK.nev = j;
}

static void timer_arm(int n);

static void raise_intc_bit(int cause)
{
    NK.intc_stat |= 1u << cause;
    nk_trace(PS2K_TR_RAISE, cause, 0);
}

static void raise_dmac_bit(int ch)
{
    NK.dmac_stat |= 1u << ch;
    nk_trace(PS2K_TR_RAISE, 0x100 + ch, 0);
}

static void notify_observers(int which, uint64_t field)
{
    nkobserver snap[PS2K_MAX_OBSERVERS];
    int n = NK.nobs;
    memcpy(snap, NK.obs, (size_t)n * sizeof(nkobserver));
    for (int i = 0; i < n; i++)
        snap[i].fn(which, field, snap[i].user);
}

static void poll_devices(void)
{
    if (NK.ndev == 0 || NK.in_device_poll)
        return;
    nkdevice snap[PS2K_MAX_DEVICES];
    int n = NK.ndev;
    memcpy(snap, NK.dev, (size_t)n * sizeof(nkdevice));
    int saved_h = NK.in_handler, saved_eie = NK.eie;
    NK.in_device_poll = 1;
    NK.in_handler = 1;
    NK.eie = 0;
    for (int i = 0; i < n; i++)
        if (snap[i].d.poll)
            snap[i].d.poll(snap[i].d.user, NK.now);
    NK.in_handler = saved_h;
    NK.eie = saved_eie;
    NK.in_device_poll = 0;
}

int nk_next_due(uint64_t *due)
{
    int have = 0;
    uint64_t t = 0;
    if (NK.nev > 0) {
        t = NK.ev[0].time;
        have = 1;
    }
    for (int i = 0; i < NK.ndev; i++) {
        uint64_t d;
        if (NK.dev[i].d.next && NK.dev[i].d.next(NK.dev[i].d.user, &d)) {
            if (d < NK.now)
                d = NK.now;
            if (!have || d < t)
                t = d;
            have = 1;
        }
    }
    if (have && due)
        *due = t;
    return have;
}

void nk_process_due(void)
{
    while (NK.nev > 0 && NK.ev[0].time <= NK.now) {
        nkevent e = NK.ev[0];
        NK.nev--;
        memmove(&NK.ev[0], &NK.ev[1], (size_t)NK.nev * sizeof(nkevent));
        switch (e.kind) {
        case NEV_VBS:
            NK.vblank_count++;
            raise_intc_bit(PS2K_INTC_VBLANK_START);
            NK.vbs_k++;
            nk_ev_add(vbs_time(NK.vbs_k), NEV_VBS, 0);
            NK_TAP(PS2K_TAP_VBLANK, 0, (int32_t)(NK.vbs_k - 1), NULL);
            notify_observers(PS2K_VBLANK_START, NK.vbs_k - 1);
            break;
        case NEV_VBE:
            raise_intc_bit(PS2K_INTC_VBLANK_END);
            NK.vbe_k++;
            nk_ev_add(vbe_time(NK.vbe_k), NEV_VBE, 0);
            NK_TAP(PS2K_TAP_VBLANK, 1, (int32_t)(NK.vbe_k - 1), NULL);
            notify_observers(PS2K_VBLANK_END, NK.vbe_k - 1);
            break;
        case NEV_KWAKE:
            if (e.a > 0 && e.a < PS2K_MAX_THREADS && NK.threads[e.a].kwait == KW_POLL) {
                NK.threads[e.a].poll_due = 1;
                nk_poll_wake(0);
            } else {
                nk_kwait_wake(e.a, KW_TIME);
            }
            break;
        case NEV_TCMP:
            NK.timers[e.a].mode |= 0x400; /* EQUF */
            raise_intc_bit(PS2K_INTC_TIMER0 + e.a);
            timer_arm(e.a);
            break;
        case NEV_TOVF:
            NK.timers[e.a].mode |= 0x800; /* OVFF */
            raise_intc_bit(PS2K_INTC_TIMER0 + e.a);
            timer_arm(e.a);
            break;
        case NEV_ALARM:
            if (NK.alarms[e.a].used && !NK.alarms[e.a].fired) {
                NK.alarms[e.a].fired = 1;
                NK.fired_fifo[NK.fired_n++] = e.a;
            }
            break;
        case NEV_POST_INTC:
            raise_intc_bit(e.a);
            break;
        case NEV_POST_DMAC:
            raise_dmac_bit(e.a);
            break;
        }
    }
    poll_devices();
}

void nk_irq_reset(void)
{
    NK.nev = 0;
    for (int n = 0; n < 4; n++)
        memset(&NK.timers[n], 0, sizeof NK.timers[n]);
    if (NK.cfg.vblank_enable) {
        NK.vbs_k = 0;
        NK.vbe_k = 0;
        nk_ev_add(vbs_time(0), NEV_VBS, 0);
        nk_ev_add(vbe_time(0), NEV_VBE, 0);
    }
}

/* ======================================================================
 * delivery: only in the driver's pass (explicit calls in handler context)
 * ==================================================================== */

static void run_chain(int slot, int cause)
{
    nkhandler snap[NKCHAINMAX];
    int n = NK.chain_len[slot];
    memcpy(snap, NK.chain[slot], (size_t)n * sizeof(nkhandler));
    int saved_eie = NK.eie;
    NK.in_handler = 1;
    NK.eie = 0;
    NK.activity++;
    for (int i = 0; i < n; i++) {
        int r;
        NK_TAP(PS2K_TAP_HANDLER, slot < PS2K_INTC_COUNT ? slot : 0x100 + (slot - PS2K_INTC_COUNT), i, snap[i].fn);
        if (snap[i].v2)
            r = ((ps2k_handler2_fn)snap[i].fn)(cause, snap[i].arg, NULL);
        else
            r = ((ps2k_handler_fn)snap[i].fn)(cause);
        if (r < 0) /* VALIDATION.md 2a: only a negative return ends the chain */
            break;
    }
    NK.in_handler = 0;
    NK.eie = saved_eie;
}

static int lowest_bit(uint32_t v)
{
    for (int i = 0; i < 32; i++)
        if (v & (1u << i))
            return i;
    return -1;
}

/* INTC causes ascending, then DMAC channels ascending, then alarms in firing order */
void nk_deliver(void)
{
    if (NK.in_handler)
        return;
    for (;;) {
        int c = lowest_bit(NK.intc_stat & NK.intc_mask);
        if (c >= 0) {
            NK.intc_stat &= ~(1u << c);
            nk_trace(PS2K_TR_INTC, c, NK.chain_len[c]);
            run_chain(c, c);
            continue;
        }
        int ch = lowest_bit(NK.dmac_stat & NK.dmac_mask);
        if (ch >= 0) {
            NK.dmac_stat &= ~(1u << ch);
            nk_trace(PS2K_TR_DMAC, ch, NK.chain_len[PS2K_INTC_COUNT + ch]);
            run_chain(PS2K_INTC_COUNT + ch, ch);
            continue;
        }
        if (NK.fired_n > 0) {
            int id = NK.fired_fifo[0];
            NK.fired_n--;
            memmove(&NK.fired_fifo[0], &NK.fired_fifo[1], (size_t)NK.fired_n * sizeof(int));
            nkalarm a = NK.alarms[id];
            memset(&NK.alarms[id], 0, sizeof NK.alarms[id]); /* one-shot */
            nk_trace(PS2K_TR_ALARM, id, 0);
            NK.activity++;
            NK_TAP(PS2K_TAP_ALARM, id, 0, (const void *)a.fn);
            int saved_eie = NK.eie;
            NK.in_handler = 1;
            NK.eie = 0;
            a.fn(id, (uint16_t)nk_hsync_index(a.time), a.arg);
            NK.in_handler = 0;
            NK.eie = saved_eie;
            continue;
        }
        break;
    }
    /* ps2k_wait_vblank waiters: after the VBLANK_START handlers and the alarms due with it */
    nk_kwait_wake(0, KW_VBLANK);
    nk_poll_wake(0);
}

/* nothing becomes due inside a flow: delivery is the driver's pass */
void ps2k_poll(void) {}

void ps2k_charge(uint64_t cycles)
{
    /* a flow's own work costs no logic time; the callers left that charge wait for time
     * to pass: a timed wait.  Pure costs (DMAC, hwbus) are configured to 0 by the runtime. */
    if (cycles && NK.cur && !NK.in_step && !NK.in_handler) {
        NK.nst.charge_waits++;
        ps2k_wait_until(NK.now + cycles);
    } else if (cycles) {
        NK.nst.charges_dropped++;
    }
}

void ps2k_raise_intc(int cause)
{
    if (cause >= 0 && cause < PS2K_INTC_COUNT)
        raise_intc_bit(cause);
}

void ps2k_raise_dmac(int ch)
{
    if (ch >= 0 && ch < PS2K_DMAC_COUNT)
        raise_dmac_bit(ch);
}

void ps2k_post_intc(int cause, uint64_t delay)
{
    if (cause < 0 || cause >= PS2K_INTC_COUNT)
        return;
    if (delay == 0)
        raise_intc_bit(cause);
    else
        nk_ev_add(NK.now + delay, NEV_POST_INTC, cause);
}

void ps2k_post_dmac(int ch, uint64_t delay)
{
    if (ch < 0 || ch >= PS2K_DMAC_COUNT)
        return;
    if (delay == 0)
        raise_dmac_bit(ch);
    else
        nk_ev_add(NK.now + delay, NEV_POST_DMAC, ch);
}

/* ======================================================================
 * DI / EI / COP0 Status (EI is not a delivery point)
 * ==================================================================== */

int ps2k_di(void)
{
    if (!NK.cur && !NK.in_handler)
        return 1;
    int old = NK.eie;
    NK.eie = 0;
    return old;
}

int ps2k_ei(void)
{
    if (!NK.cur && !NK.in_handler)
        return 1;
    int old = NK.eie;
    NK.eie = 1;
    return old;
}

int ps2k_in_handler(void) { return NK.in_handler; }

uint32_t ps2k_cop0_status(void) { return (NK.in_handler ? 0u : 1u) | (NK.eie ? 0x10000u : 0u); }

/* ======================================================================
 * handler ids and chains (VALIDATION.md 2c: INTC and DMAC share 1..128, next-fit)
 * ==================================================================== */

static int handler_id_used(int id)
{
    for (int c = 0; c < NKCHAINS; c++)
        for (int i = 0; i < NK.chain_len[c]; i++)
            if (NK.chain[c][i].id == id)
                return 1;
    return 0;
}

static int alloc_handler_id(void)
{
    for (int n = 0; n < PS2K_HANDLER_ID_MAX; n++) {
        int id = 1 + (NK.next_handler_id - 1 + n) % PS2K_HANDLER_ID_MAX;
        if (!handler_id_used(id)) {
            NK.next_handler_id = 1 + id % PS2K_HANDLER_ID_MAX;
            return id;
        }
    }
    return PS2K_ERR;
}

static int add_handler(const char *call, int slot, void *fn, int next, int v2, void *arg)
{
    if (nk_enter(call, 0))
        return PS2K_ERR;
    if (!fn || NK.chain_len[slot] >= NKCHAINMAX)
        return PS2K_ERR;
    nkhandler h;
    h.id = alloc_handler_id();
    if (h.id < 0)
        return PS2K_ERR;
    h.v2 = v2;
    h.fn = fn;
    h.arg = arg;
    int n = NK.chain_len[slot];
    if (next == 0) {
        memmove(&NK.chain[slot][1], &NK.chain[slot][0], (size_t)n * sizeof(nkhandler));
        NK.chain[slot][0] = h;
    } else {
        NK.chain[slot][n] = h;
    }
    NK.chain_len[slot] = n + 1;
    return h.id;
}

static int remove_handler(const char *call, int slot, int id)
{
    if (nk_enter(call, 0))
        return PS2K_ERR;
    int n = NK.chain_len[slot];
    for (int i = 0; i < n; i++) {
        if (NK.chain[slot][i].id == id) {
            memmove(&NK.chain[slot][i], &NK.chain[slot][i + 1], (size_t)(n - i - 1) * sizeof(nkhandler));
            NK.chain_len[slot] = n - 1;
            return id;
        }
    }
    return PS2K_ERR;
}

#define VALID_CAUSE(c) ((c) >= 0 && (c) < PS2K_INTC_COUNT)
#define VALID_CH(c)    ((c) >= 0 && (c) < PS2K_DMAC_COUNT)

int ps2k_add_intc_handler(int cause, ps2k_handler_fn fn, int next)
{
    return VALID_CAUSE(cause) ? add_handler("AddIntcHandler", cause, (void *)fn, next, 0, NULL) : PS2K_ERR;
}
int ps2k_add_intc_handler2(int cause, ps2k_handler2_fn fn, int next, void *arg)
{
    return VALID_CAUSE(cause) ? add_handler("AddIntcHandler2", cause, (void *)fn, next, 1, arg) : PS2K_ERR;
}
int ps2k_remove_intc_handler(int cause, int id)
{
    return VALID_CAUSE(cause) ? remove_handler("RemoveIntcHandler", cause, id) : PS2K_ERR;
}
int ps2k_add_dmac_handler(int ch, ps2k_handler_fn fn, int next)
{
    return VALID_CH(ch) ? add_handler("AddDmacHandler", PS2K_INTC_COUNT + ch, (void *)fn, next, 0, NULL) : PS2K_ERR;
}
int ps2k_add_dmac_handler2(int ch, ps2k_handler2_fn fn, int next, void *arg)
{
    return VALID_CH(ch) ? add_handler("AddDmacHandler2", PS2K_INTC_COUNT + ch, (void *)fn, next, 1, arg) : PS2K_ERR;
}
int ps2k_remove_dmac_handler(int ch, int id)
{
    return VALID_CH(ch) ? remove_handler("RemoveDmacHandler", PS2K_INTC_COUNT + ch, id) : PS2K_ERR;
}

/* the mask is the latch's gate: a cause raised before EnableIntc is delivered in the next
 * pass after it (the VIF1 protocol) */
static int mask_change(const char *call, int isr, uint32_t *mask, int bit, int enable)
{
    if (nk_enter(call, isr))
        return PS2K_ERR;
    uint32_t b = 1u << bit;
    int changed = enable ? !(*mask & b) : !!(*mask & b);
    if (enable)
        *mask |= b;
    else
        *mask &= ~b;
    return changed;
}

int ps2k_enable_intc(int cause, int isr)
{
    return VALID_CAUSE(cause) ? mask_change(isr ? "iEnableIntc" : "EnableIntc", isr, &NK.intc_mask, cause, 1)
                              : PS2K_ERR;
}
int ps2k_disable_intc(int cause, int isr)
{
    return VALID_CAUSE(cause) ? mask_change(isr ? "iDisableIntc" : "DisableIntc", isr, &NK.intc_mask, cause, 0)
                              : PS2K_ERR;
}
int ps2k_enable_dmac(int ch, int isr)
{
    return VALID_CH(ch) ? mask_change(isr ? "iEnableDmac" : "EnableDmac", isr, &NK.dmac_mask, ch, 1) : PS2K_ERR;
}
int ps2k_disable_dmac(int ch, int isr)
{
    return VALID_CH(ch) ? mask_change(isr ? "iDisableDmac" : "DisableDmac", isr, &NK.dmac_mask, ch, 0) : PS2K_ERR;
}

/* ======================================================================
 * alarms (SetAlarm: none on the golden route natively; kept for the API)
 * ==================================================================== */

static int alarm_add(const char *call, uint64_t when, ps2k_alarm_fn fn, void *arg, int isr)
{
    if (nk_enter(call, isr))
        return PS2K_ERR;
    if (!fn)
        return PS2K_ERR;
    for (int i = 0; i < PS2K_MAX_ALARMS; i++) {
        nkalarm *a = &NK.alarms[i];
        if (a->used)
            continue;
        a->used = 1;
        a->fired = 0;
        a->time = when;
        a->fn = fn;
        a->arg = arg;
        if (nk_ev_add(when, NEV_ALARM, i) < 0) {
            a->used = 0;
            return PS2K_ERR;
        }
        return i;
    }
    return PS2K_ERR;
}

int ps2k_set_alarm(uint16_t time, ps2k_alarm_fn fn, void *arg, int isr)
{
    uint64_t when = hsync_time(nk_hsync_index(NK.now) + time);
    return alarm_add(isr ? "iSetAlarm" : "SetAlarm", when, fn, arg, isr);
}

int ps2k_set_cycle_alarm(uint64_t cycles, ps2k_alarm_fn fn, void *arg, int isr)
{
    return alarm_add(isr ? "iSetTimerAlarm" : "SetTimerAlarm", NK.now + cycles, fn, arg, isr);
}

int ps2k_release_alarm(int id, int isr)
{
    if (nk_enter(isr ? "iReleaseAlarm" : "ReleaseAlarm", isr))
        return PS2K_ERR;
    if (id < 0 || id >= PS2K_MAX_ALARMS || !NK.alarms[id].used)
        return PS2K_ERR;
    if (NK.alarms[id].fired) {
        int j = 0;
        for (int i = 0; i < NK.fired_n; i++)
            if (NK.fired_fifo[i] != id)
                NK.fired_fifo[j++] = NK.fired_fifo[i];
        NK.fired_n = j;
    } else {
        nk_ev_remove(NEV_ALARM, id);
    }
    memset(&NK.alarms[id], 0, sizeof NK.alarms[id]);
    return id;
}

/* ======================================================================
 * timers T0..T3 over logic time (T0_COUNT: GfxEndFrame / GfxFlipBuffersMaybe / the VIF1
 * latch: a frame's own work reads 0 here, the nominal profile).
 *   MODE: CLKS[1:0] (0 BUSCLK, 1 /16, 2 /256, 3 HBLNK), ZRET bit6, CUE bit7, CMPE bit8,
 *   OVFE bit9, EQUF bit10, OVFF bit11 (w1c)
 * ==================================================================== */

static uint64_t abs_tick(uint32_t clks, uint64_t t)
{
    switch (clks & 3) {
    case 0: return t;
    case 1: return t / 16;
    case 2: return t / 256;
    default: return nk_hsync_index(t);
    }
}

static uint64_t tick_time(uint32_t clks, uint64_t k)
{
    switch (clks & 3) {
    case 0: return k;
    case 1: return k * 16;
    case 2: return k * 256;
    default: return hsync_time(k);
    }
}

static uint32_t timer_count(int n)
{
    nktimer *tm = &NK.timers[n];
    if (!(tm->mode & 0x80))
        return tm->count_base;
    uint64_t d = abs_tick(tm->mode, NK.now) - tm->tick_base;
    uint64_t c = tm->count_base + d;
    if (tm->mode & 0x40) { /* ZRET */
        uint64_t p = (uint64_t)tm->comp + 1;
        if (tm->count_base <= tm->comp)
            return (uint32_t)(c % p);
        if (c <= 0xFFFF)
            return (uint32_t)c;
        return (uint32_t)((c - 0x10000) % p);
    }
    return (uint32_t)(c & 0xFFFF);
}

static void timer_rebase(int n)
{
    nktimer *tm = &NK.timers[n];
    tm->count_base = timer_count(n);
    tm->tick_base = abs_tick(tm->mode, NK.now);
}

static void timer_arm(int n)
{
    nktimer *tm = &NK.timers[n];
    nk_ev_remove(NEV_TCMP, n);
    nk_ev_remove(NEV_TOVF, n);
    if (!(tm->mode & 0x80))
        return;
    timer_rebase(n);
    uint64_t c = tm->count_base, cmp = tm->comp, T = tm->tick_base, dk;
    int zret = (tm->mode & 0x40) != 0;
    if (tm->mode & 0x100) { /* CMPE */
        if (!zret) {
            dk = (cmp - c) & 0xFFFF;
            if (dk == 0)
                dk = 0x10000;
        } else if (c <= cmp) {
            dk = (cmp - c) % (cmp + 1);
            if (dk == 0)
                dk = cmp + 1;
        } else {
            dk = (0x10000 - c) + cmp;
        }
        nk_ev_add(tick_time(tm->mode, T + dk), NEV_TCMP, n);
    }
    if ((tm->mode & 0x200) && (!zret || c > cmp)) { /* OVFE */
        dk = 0x10000 - c;
        nk_ev_add(tick_time(tm->mode, T + dk), NEV_TOVF, n);
    }
}

static int timer_index(uint32_t addr, uint32_t *reg)
{
    uint32_t base;
    int n;
    if ((addr & 0xFFFFFF00u) == 0x10000000u) { base = 0x10000000u; n = 0; }
    else if ((addr & 0xFFFFFF00u) == 0x10000800u) { base = 0x10000800u; n = 1; }
    else if ((addr & 0xFFFFFF00u) == 0x10001000u) { base = 0x10001000u; n = 2; }
    else if ((addr & 0xFFFFFF00u) == 0x10001800u) { base = 0x10001800u; n = 3; }
    else return -1;
    uint32_t off = addr - base;
    if (off != 0x00 && off != 0x10 && off != 0x20 && off != 0x30)
        return -1;
    if (off == 0x30 && n >= 2)
        return -1;
    *reg = off;
    return n;
}

int ps2k_hw_claims(uint32_t addr)
{
    uint32_t reg;
    if (timer_index(addr, &reg) >= 0)
        return 1;
    return addr == PS2K_INTC_STAT || addr == PS2K_INTC_MASK || addr == PS2K_D_STAT;
}

uint32_t ps2k_hw_read32(uint32_t addr)
{
    uint32_t reg;
    int n = timer_index(addr, &reg);
    if (n >= 0) {
        nktimer *tm = &NK.timers[n];
        NK_TAP(PS2K_TAP_TIMER_READ, (int32_t)addr, 0, NULL);
        switch (reg) {
        case 0x00: return timer_count(n);
        case 0x10: return tm->mode;
        case 0x20: return tm->comp;
        default: return tm->hold;
        }
    }
    if (addr == PS2K_INTC_STAT)
        return NK.intc_stat;
    if (addr == PS2K_INTC_MASK)
        return NK.intc_mask;
    if (addr == PS2K_D_STAT)
        return (NK.dmac_mask << 16) | NK.dmac_stat;
    return 0;
}

void ps2k_hw_write32(uint32_t addr, uint32_t v)
{
    uint32_t reg;
    int n = timer_index(addr, &reg);
    if (n >= 0) {
        nktimer *tm = &NK.timers[n];
        switch (reg) {
        case 0x00:
            tm->count_base = v & 0xFFFF;
            tm->tick_base = abs_tick(tm->mode, NK.now);
            break;
        case 0x10: {
            uint32_t c = timer_count(n);
            uint32_t flags = tm->mode & 0xC00 & ~(v & 0xC00);
            tm->mode = (v & 0x3FF) | flags;
            tm->count_base = c;
            tm->tick_base = abs_tick(tm->mode, NK.now);
            break;
        }
        case 0x20:
            timer_rebase(n);
            tm->comp = v & 0xFFFF;
            break;
        default:
            tm->hold = v & 0xFFFF;
            return;
        }
        timer_arm(n);
        return;
    }
    if (addr == PS2K_INTC_STAT)
        NK.intc_stat &= ~v;
    else if (addr == PS2K_INTC_MASK)
        NK.intc_mask ^= v & ((1u << PS2K_INTC_COUNT) - 1);
    else if (addr == PS2K_D_STAT) {
        NK.dmac_stat &= ~(v & 0x3FF);
        NK.dmac_mask ^= (v >> 16) & 0x3FF;
    }
}
