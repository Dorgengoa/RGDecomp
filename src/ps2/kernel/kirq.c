/* SPDX-License-Identifier: CC0-1.0
 * ps2k: virtual clock, event queue, INTC/DMAC handlers and delivery, kernel
 * alarms, EE timers T0..T3 and their registers (docs/KERNEL.md). */
#include <string.h>

#include "internal.h"

/* ======================================================================
 * clock helpers
 * ==================================================================== */

uint64_t k_hsync_index(uint64_t t) { return t * PS2K_SUB / PS2K_HSYNC_SUB; }

static uint64_t hsync_time(uint64_t k) /* first bus cycle at/after hsync k */
{
    return (k * PS2K_HSYNC_SUB + PS2K_SUB - 1) / PS2K_SUB;
}

static uint64_t vbs_time(uint64_t k)
{
    return (k * PS2K_FIELD_SUB + (uint64_t)K.cfg.vblank_start_line * PS2K_HSYNC_SUB) / PS2K_SUB;
}

static uint64_t vbe_time(uint64_t k) { return ((k + 1) * PS2K_FIELD_SUB) / PS2K_SUB; }

uint64_t ps2k_now(void) { return K.now; }
uint64_t ps2k_hsync_count(void) { return k_hsync_index(K.now); }
uint64_t ps2k_vblank_count(void) { return K.vblank_count; }
uint64_t ps2k_vblank_end_count(void) { return K.vbe_k; }

void ps2k_set_pacing_hook(ps2k_pacing_fn fn, void *user)
{
    K.pacing = fn;
    K.pacing_user = user;
}

uint32_t ps2k_vblank_start_line(void) { return K.cfg.vblank_start_line; }
int ps2k_vblank_enabled(void) { return K.cfg.vblank_enable != 0; }
uint64_t ps2k_vblank_start_time(uint64_t field) { return vbs_time(field); }
uint64_t ps2k_vblank_end_time(uint64_t field) { return vbe_time(field); }

/* ======================================================================
 * VBlank observers and devices (platform glue)
 * ==================================================================== */

int ps2k_add_vblank_observer(ps2k_vblank_fn fn, void *user)
{
    if (!fn || K.nobs >= PS2K_MAX_OBSERVERS)
        return PS2K_ERR;
    kobserver *o = &K.obs[K.nobs++];
    o->id = ++K.next_glue_id;
    o->fn = fn;
    o->user = user;
    return o->id;
}

int ps2k_remove_vblank_observer(int id)
{
    for (int i = 0; i < K.nobs; i++) {
        if (K.obs[i].id == id) {
            memmove(&K.obs[i], &K.obs[i + 1], (size_t)(K.nobs - i - 1) * sizeof(kobserver));
            K.nobs--;
            return id;
        }
    }
    return PS2K_ERR;
}

int ps2k_add_device(const ps2k_device *dev)
{
    if (!dev || !dev->poll || K.ndev >= PS2K_MAX_DEVICES)
        return PS2K_ERR;
    kdevice *d = &K.dev[K.ndev++];
    d->id = ++K.next_glue_id;
    d->d = *dev;
    return d->id;
}

int ps2k_remove_device(int id)
{
    for (int i = 0; i < K.ndev; i++) {
        if (K.dev[i].id == id) {
            memmove(&K.dev[i], &K.dev[i + 1], (size_t)(K.ndev - i - 1) * sizeof(kdevice));
            K.ndev--;
            return id;
        }
    }
    return PS2K_ERR;
}

/* ======================================================================
 * event queue: sorted by (time, insertion seq) -> deterministic
 * ==================================================================== */

int k_ev_add(uint64_t time, int kind, int a)
{
    if (K.nev >= KEVMAX)
        return -1;
    kevent e;
    e.time = time;
    e.seq = K.ev_seq++;
    e.kind = kind;
    e.a = a;
    int i = K.nev;
    while (i > 0 && (K.ev[i - 1].time > time))
        i--;
    memmove(&K.ev[i + 1], &K.ev[i], (size_t)(K.nev - i) * sizeof(kevent));
    K.ev[i] = e;
    K.nev++;
    return 0;
}

void k_ev_remove(int kind, int a)
{
    int j = 0;
    for (int i = 0; i < K.nev; i++) {
        if (K.ev[i].kind == kind && K.ev[i].a == a)
            continue;
        K.ev[j++] = K.ev[i];
    }
    K.nev = j;
}

static void timer_arm(int n);

static void raise_intc_bit(int cause)
{
    K.intc_stat |= 1u << cause;
    k_trace(PS2K_TR_RAISE, cause, 0);
}

static void raise_dmac_bit(int ch)
{
    K.dmac_stat |= 1u << ch;
    k_trace(PS2K_TR_RAISE, 0x100 + ch, 0);
}

static void notify_observers(int which, uint64_t field)
{
    /* snapshot: an observer may remove itself */
    kobserver snap[PS2K_MAX_OBSERVERS];
    int n = K.nobs;
    memcpy(snap, K.obs, (size_t)n * sizeof(kobserver));
    for (int i = 0; i < n; i++)
        snap[i].fn(which, field, snap[i].user);
}

/* Poll every device once, in handler context (completion callbacks may make
 * "i" calls).  Not re-entered from a callback's own ps2k_poll. */
static void poll_devices(void)
{
    if (K.ndev == 0 || K.in_device_poll)
        return;
    kdevice snap[PS2K_MAX_DEVICES];
    int n = K.ndev;
    memcpy(snap, K.dev, (size_t)n * sizeof(kdevice));
    int saved_h = K.in_handler, saved_eie = K.eie;
    K.in_device_poll = 1;
    K.in_handler = 1;
    K.eie = 0;
    for (int i = 0; i < n; i++)
        if (snap[i].d.poll)
            snap[i].d.poll(snap[i].d.user, K.now);
    K.in_handler = saved_h;
    K.eie = saved_eie;
    K.in_device_poll = 0;
}

int k_next_due(uint64_t *due)
{
    int have = 0;
    uint64_t t = 0;
    if (K.nev > 0) {
        t = K.ev[0].time;
        have = 1;
    }
    for (int i = 0; i < K.ndev; i++) {
        uint64_t d;
        if (K.dev[i].d.next && K.dev[i].d.next(K.dev[i].d.user, &d)) {
            if (d < K.now)
                d = K.now;
            if (!have || d < t)
                t = d;
            have = 1;
        }
    }
    if (have && due)
        *due = t;
    return have;
}

void k_process_due(void)
{
    while (K.nev > 0 && K.ev[0].time <= K.now) {
        kevent e = K.ev[0];
        K.nev--;
        memmove(&K.ev[0], &K.ev[1], (size_t)K.nev * sizeof(kevent));
        switch (e.kind) {
        case EV_VBS:
            K.vblank_count++;
            raise_intc_bit(PS2K_INTC_VBLANK_START);
            K.vbs_k++;
            k_ev_add(vbs_time(K.vbs_k), EV_VBS, 0);
            K_TAP(PS2K_TAP_VBLANK, 0, (int32_t)(K.vbs_k - 1), NULL);
            notify_observers(PS2K_VBLANK_START, K.vbs_k - 1);
            break;
        case EV_VBE:
            raise_intc_bit(PS2K_INTC_VBLANK_END);
            K.vbe_k++;
            k_ev_add(vbe_time(K.vbe_k), EV_VBE, 0);
            K_TAP(PS2K_TAP_VBLANK, 1, (int32_t)(K.vbe_k - 1), NULL);
            notify_observers(PS2K_VBLANK_END, K.vbe_k - 1);
            break;
        case EV_KWAKE:
            if (e.a > 0 && e.a < PS2K_MAX_THREADS && K.threads[e.a].kwait == KW_POLL) {
                K.threads[e.a].poll_due = 1;
                k_poll_wake(0);
            } else {
                k_kwait_wake(e.a, KW_TIME);
            }
            break;
        case EV_TCMP:
            K.timers[e.a].mode |= 0x400; /* EQUF */
            raise_intc_bit(PS2K_INTC_TIMER0 + e.a);
            timer_arm(e.a);
            break;
        case EV_TOVF:
            K.timers[e.a].mode |= 0x800; /* OVFF */
            raise_intc_bit(PS2K_INTC_TIMER0 + e.a);
            timer_arm(e.a);
            break;
        case EV_ALARM:
            if (K.alarms[e.a].used && !K.alarms[e.a].fired) {
                K.alarms[e.a].fired = 1;
                K.fired_fifo[K.fired_n++] = e.a;
            }
            break;
        case EV_POST_INTC:
            raise_intc_bit(e.a);
            break;
        case EV_POST_DMAC:
            raise_dmac_bit(e.a);
            break;
        }
    }
    poll_devices();
}

void k_irq_reset(void)
{
    K.nev = 0;
    for (int n = 0; n < 4; n++) {
        memset(&K.timers[n], 0, sizeof K.timers[n]);
    }
    if (K.cfg.vblank_enable) {
        K.vbs_k = 0;
        K.vbe_k = 0;
        k_ev_add(vbs_time(0), EV_VBS, 0);
        k_ev_add(vbe_time(0), EV_VBE, 0);
    }
}

/* ======================================================================
 * interrupt delivery
 * ==================================================================== */

int k_deliverable(void)
{
    return (K.intc_stat & K.intc_mask) || (K.dmac_stat & K.dmac_mask) || K.fired_n > 0;
}

static void run_chain(int slot, int cause)
{
    khandler snap[KCHAINMAX];
    int n = K.chain_len[slot];
    memcpy(snap, K.chain[slot], (size_t)n * sizeof(khandler));
    int saved_eie = K.eie;
    K.in_handler = 1;
    K.eie = 0;
    K.activity++;
    for (int i = 0; i < n; i++) {
        int r;
        K_TAP(PS2K_TAP_HANDLER, slot < PS2K_INTC_COUNT ? slot : 0x100 + (slot - PS2K_INTC_COUNT), i, snap[i].fn);
        if (snap[i].v2)
            r = ((ps2k_handler2_fn)snap[i].fn)(cause, snap[i].arg, NULL);
        else
            r = ((ps2k_handler_fn)snap[i].fn)(cause);
        if (r < 0) /* VALIDATION.md 2a: only a negative return ends the chain */
            break;
    }
    K.in_handler = 0;
    K.eie = saved_eie;
}

static int lowest_bit(uint32_t v)
{
    for (int i = 0; i < 32; i++)
        if (v & (1u << i))
            return i;
    return -1;
}

/* Deliver everything pending, in a fixed order: INTC causes ascending, then
 * DMAC channels ascending, then kernel alarms in firing order.  The caller
 * decides whether the context allows delivery. */
void k_deliver(void)
{
    if (K.in_handler)
        return;
    for (;;) {
        int c = lowest_bit(K.intc_stat & K.intc_mask);
        if (c >= 0) {
            K.intc_stat &= ~(1u << c);
            k_trace(PS2K_TR_INTC, c, K.chain_len[c]);
            run_chain(c, c);
            continue;
        }
        int ch = lowest_bit(K.dmac_stat & K.dmac_mask);
        if (ch >= 0) {
            K.dmac_stat &= ~(1u << ch);
            k_trace(PS2K_TR_DMAC, ch, K.chain_len[PS2K_INTC_COUNT + ch]);
            run_chain(PS2K_INTC_COUNT + ch, ch);
            continue;
        }
        if (K.fired_n > 0) {
            int id = K.fired_fifo[0];
            K.fired_n--;
            memmove(&K.fired_fifo[0], &K.fired_fifo[1], (size_t)K.fired_n * sizeof(int));
            kalarm a = K.alarms[id];
            memset(&K.alarms[id], 0, sizeof K.alarms[id]); /* one-shot */
            k_trace(PS2K_TR_ALARM, id, 0);
            K.activity++;
            K_TAP(PS2K_TAP_ALARM, id, 0, (const void *)a.fn);
            int saved_eie = K.eie;
            K.in_handler = 1;
            K.eie = 0;
            a.fn(id, (uint16_t)k_hsync_index(a.time), a.arg);
            K.in_handler = 0;
            K.eie = saved_eie;
            continue;
        }
        break;
    }
    /* ps2k_wait_vblank waiters: after the VBLANK_START handlers and the alarms
     * due with it, as the alarm the old sceGsSyncV armed was */
    k_kwait_wake(0, KW_VBLANK);
    k_poll_wake(0);
}

void ps2k_poll(void)
{
    k_process_due();
    if (K.in_handler || !K.cur)
        return;
    if (K.eie)
        k_deliver();
    k_maybe_preempt();
}

void ps2k_charge(uint64_t cycles)
{
    K.now += cycles;
    ps2k_poll();
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
        k_ev_add(K.now + delay, EV_POST_INTC, cause);
}

void ps2k_post_dmac(int ch, uint64_t delay)
{
    if (ch < 0 || ch >= PS2K_DMAC_COUNT)
        return;
    if (delay == 0)
        raise_dmac_bit(ch);
    else
        k_ev_add(K.now + delay, EV_POST_DMAC, ch);
}

/* ======================================================================
 * DI / EI / COP0 Status
 * ==================================================================== */

int ps2k_di(void)
{
    if (!K.cur && !K.in_handler)
        return 1; /* host / scheduler context: interrupts always enabled */
    int old = K.eie;
    K.eie = 0;
    return old;
}

int ps2k_ei(void)
{
    if (!K.cur && !K.in_handler)
        return 1;
    int old = K.eie;
    K.eie = 1;
    if (!K.in_handler) { /* thread context: a delivery point */
        k_process_due();
        k_deliver();
        k_maybe_preempt();
    }
    return old;
}

int ps2k_in_handler(void) { return K.in_handler; }

uint32_t ps2k_cop0_status(void)
{
    return (K.in_handler ? 0u : 1u) | (K.eie ? 0x10000u : 0u);
}

/* ======================================================================
 * handler chains
 * ==================================================================== */

static int handler_id_used(int id)
{
    for (int c = 0; c < KCHAINS; c++)
        for (int i = 0; i < K.chain_len[c]; i++)
            if (K.chain[c][i].id == id)
                return 1;
    return 0;
}

/* VALIDATION.md 2c: INTC and DMAC handlers share one id range
 * 1..PS2K_HANDLER_ID_MAX, allocated next-fit from the id after the last one
 * given out, wrapping, skipping ids in use. */
static int alloc_handler_id(void)
{
    for (int n = 0; n < PS2K_HANDLER_ID_MAX; n++) {
        int id = 1 + (K.next_handler_id - 1 + n) % PS2K_HANDLER_ID_MAX;
        if (!handler_id_used(id)) {
            K.next_handler_id = 1 + id % PS2K_HANDLER_ID_MAX;
            return id;
        }
    }
    return PS2K_ERR;
}

static int add_handler(const char *call, int slot, void *fn, int next, int v2, void *arg)
{
    if (k_enter(call, 0))
        return PS2K_ERR;
    if (!fn || K.chain_len[slot] >= KCHAINMAX)
        return PS2K_ERR;
    khandler h;
    h.id = alloc_handler_id();
    if (h.id < 0)
        return PS2K_ERR;
    h.v2 = v2;
    h.fn = fn;
    h.arg = arg;
    int n = K.chain_len[slot];
    if (next == 0) {
        memmove(&K.chain[slot][1], &K.chain[slot][0], (size_t)n * sizeof(khandler));
        K.chain[slot][0] = h;
    } else {
        K.chain[slot][n] = h;
    }
    K.chain_len[slot] = n + 1;
    return h.id;
}

static int remove_handler(const char *call, int slot, int id)
{
    if (k_enter(call, 0))
        return PS2K_ERR;
    int n = K.chain_len[slot];
    for (int i = 0; i < n; i++) {
        if (K.chain[slot][i].id == id) {
            memmove(&K.chain[slot][i], &K.chain[slot][i + 1], (size_t)(n - i - 1) * sizeof(khandler));
            K.chain_len[slot] = n - 1;
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
    return VALID_CH(ch) ? add_handler("AddDmacHandler", PS2K_INTC_COUNT + ch, (void *)fn, next, 0, NULL)
                        : PS2K_ERR;
}
int ps2k_add_dmac_handler2(int ch, ps2k_handler2_fn fn, int next, void *arg)
{
    return VALID_CH(ch) ? add_handler("AddDmacHandler2", PS2K_INTC_COUNT + ch, (void *)fn, next, 1, arg)
                        : PS2K_ERR;
}
int ps2k_remove_dmac_handler(int ch, int id)
{
    return VALID_CH(ch) ? remove_handler("RemoveDmacHandler", PS2K_INTC_COUNT + ch, id) : PS2K_ERR;
}

static int mask_change(const char *call, int isr, uint32_t *mask, int bit, int enable)
{
    if (k_enter(call, isr))
        return PS2K_ERR;
    uint32_t b = 1u << bit;
    int changed = enable ? !(*mask & b) : !!(*mask & b);
    if (enable)
        *mask |= b;
    else
        *mask &= ~b;
    if (enable && !isr) /* re-enabling is a delivery point (libkernl ends with EI) */
        ps2k_poll();
    return changed;
}

int ps2k_enable_intc(int cause, int isr)
{
    return VALID_CAUSE(cause) ? mask_change(isr ? "iEnableIntc" : "EnableIntc", isr, &K.intc_mask, cause, 1)
                              : PS2K_ERR;
}
int ps2k_disable_intc(int cause, int isr)
{
    return VALID_CAUSE(cause) ? mask_change(isr ? "iDisableIntc" : "DisableIntc", isr, &K.intc_mask, cause, 0)
                              : PS2K_ERR;
}
int ps2k_enable_dmac(int ch, int isr)
{
    return VALID_CH(ch) ? mask_change(isr ? "iEnableDmac" : "EnableDmac", isr, &K.dmac_mask, ch, 1) : PS2K_ERR;
}
int ps2k_disable_dmac(int ch, int isr)
{
    return VALID_CH(ch) ? mask_change(isr ? "iDisableDmac" : "DisableDmac", isr, &K.dmac_mask, ch, 0) : PS2K_ERR;
}

/* ======================================================================
 * alarms
 * ==================================================================== */

static int alarm_add(const char *call, uint64_t when, ps2k_alarm_fn fn, void *arg, int isr)
{
    if (k_enter(call, isr))
        return PS2K_ERR;
    if (!fn)
        return PS2K_ERR;
    for (int i = 0; i < PS2K_MAX_ALARMS; i++) {
        kalarm *a = &K.alarms[i];
        if (a->used)
            continue;
        a->used = 1;
        a->fired = 0;
        a->time = when;
        a->fn = fn;
        a->arg = arg;
        if (k_ev_add(when, EV_ALARM, i) < 0) {
            a->used = 0;
            return PS2K_ERR;
        }
        return i;
    }
    return PS2K_ERR;
}

int ps2k_set_alarm(uint16_t time, ps2k_alarm_fn fn, void *arg, int isr)
{
    uint64_t when = hsync_time(k_hsync_index(K.now) + time);
    return alarm_add(isr ? "iSetAlarm" : "SetAlarm", when, fn, arg, isr);
}

int ps2k_set_cycle_alarm(uint64_t cycles, ps2k_alarm_fn fn, void *arg, int isr)
{
    return alarm_add(isr ? "iSetTimerAlarm" : "SetTimerAlarm", K.now + cycles, fn, arg, isr);
}

int ps2k_release_alarm(int id, int isr)
{
    if (k_enter(isr ? "iReleaseAlarm" : "ReleaseAlarm", isr))
        return PS2K_ERR;
    if (id < 0 || id >= PS2K_MAX_ALARMS || !K.alarms[id].used)
        return PS2K_ERR;
    if (K.alarms[id].fired) {
        int j = 0;
        for (int i = 0; i < K.fired_n; i++)
            if (K.fired_fifo[i] != id)
                K.fired_fifo[j++] = K.fired_fifo[i];
        K.fired_n = j;
    } else {
        k_ev_remove(EV_ALARM, id);
    }
    memset(&K.alarms[id], 0, sizeof K.alarms[id]);
    return id;
}

/* ======================================================================
 * EE timers T0..T3
 *   MODE: CLKS[1:0] (0 BUSCLK, 1 /16, 2 /256, 3 HBLNK), GATE bits ignored,
 *   ZRET bit6, CUE bit7, CMPE bit8, OVFE bit9, EQUF bit10, OVFF bit11 (w1c)
 * ==================================================================== */

static uint64_t abs_tick(uint32_t clks, uint64_t t)
{
    switch (clks & 3) {
    case 0: return t;
    case 1: return t / 16;
    case 2: return t / 256;
    default: return k_hsync_index(t);
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
    ktimer *tm = &K.timers[n];
    if (!(tm->mode & 0x80))
        return tm->count_base;
    uint64_t d = abs_tick(tm->mode, K.now) - tm->tick_base;
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
    ktimer *tm = &K.timers[n];
    tm->count_base = timer_count(n);
    tm->tick_base = abs_tick(tm->mode, K.now);
}

static void timer_arm(int n)
{
    ktimer *tm = &K.timers[n];
    k_ev_remove(EV_TCMP, n);
    k_ev_remove(EV_TOVF, n);
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
        k_ev_add(tick_time(tm->mode, T + dk), EV_TCMP, n);
    }
    if ((tm->mode & 0x200) && (!zret || c > cmp)) { /* OVFE */
        dk = 0x10000 - c;
        k_ev_add(tick_time(tm->mode, T + dk), EV_TOVF, n);
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
        return -1; /* T2/T3 have no HOLD */
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
        ktimer *tm = &K.timers[n];
        K_TAP(PS2K_TAP_TIMER_READ, (int32_t)addr, 0, NULL);
        switch (reg) {
        case 0x00: return timer_count(n);
        case 0x10: return tm->mode;
        case 0x20: return tm->comp;
        default: return tm->hold;
        }
    }
    if (addr == PS2K_INTC_STAT)
        return K.intc_stat;
    if (addr == PS2K_INTC_MASK)
        return K.intc_mask;
    if (addr == PS2K_D_STAT)
        return (K.dmac_mask << 16) | K.dmac_stat;
    return 0;
}

void ps2k_hw_write32(uint32_t addr, uint32_t v)
{
    uint32_t reg;
    int n = timer_index(addr, &reg);
    if (n >= 0) {
        ktimer *tm = &K.timers[n];
        switch (reg) {
        case 0x00:
            tm->count_base = v & 0xFFFF;
            tm->tick_base = abs_tick(tm->mode, K.now);
            break;
        case 0x10: {
            uint32_t c = timer_count(n);
            uint32_t flags = tm->mode & 0xC00 & ~(v & 0xC00);
            tm->mode = (v & 0x3FF) | flags;
            tm->count_base = c;
            tm->tick_base = abs_tick(tm->mode, K.now);
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
        K.intc_stat &= ~v;
    else if (addr == PS2K_INTC_MASK)
        K.intc_mask ^= v & ((1u << PS2K_INTC_COUNT) - 1);
    else if (addr == PS2K_D_STAT) {
        K.dmac_stat &= ~(v & 0x3FF);
        K.dmac_mask ^= (v >> 16) & 0x3FF;
    }
}
