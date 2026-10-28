/* SPDX-License-Identifier: CC0-1.0
 * The native kernel table (docs/NATIVE-THREADS.md "Native kernel table"): the
 * frame-driven implementation of the ps2k API (RG_THREADS=native).
 *
 * - Flows: the game threads that are neither driven steps nor service threads (on the
 *   golden route: main and the loading screen) are coroutines on fixed-address stacks
 *   (src/native/threads/fiber).  A flow runs until it waits (semaphore, kernel-private
 *   wait, SleepThread, DelayThread, a charge); it is never preempted, a signal never
 *   switches; ready flows run FIFO, priorities only order simultaneous wakes.
 * - The driver loop (ps2k_step): the pass (due events, the latched handler chains as
 *   explicit calls, kernel-private wakes, the phase hook = the frame driver's driven
 *   steps), then a ready flow, else logic time jumps to the next event.
 * - Game-visible ids: thread objects (ids, status, Refer / Terminate / Delete), driven
 *   threads (parked, real semaphore waiters), semaphores (ids, counts, waiter lists),
 *   handler ids (rg_nk_irq.c).
 *
 * Derived from the HLE's frame-driven mode (src/ps2/kernel, now the oracle only): the
 * same semantics and trace records, without the scheduler, preemption, delivery at kernel
 * calls, service threads or modelled kernel-call costs. */
#include <stdlib.h>
#include <string.h>

#include "rg_nk_internal.h"

nkstate NK;
unsigned nk_guest_csr;
ps2k_tap_fn nk_tap;
ps2k_start_hook_fn nk_start_hook;
ps2k_signal_hook_fn nk_signal_hook;
ps2k_phase_hook_fn nk_phase_hook;
ps2k_parked_hook_fn nk_parked_hook;
ps2k_block_hook_fn nk_block_hook;

void ps2k_set_census_tap(ps2k_tap_fn fn) { nk_tap = fn; }
void ps2k_set_start_hook(ps2k_start_hook_fn fn) { nk_start_hook = fn; }
void ps2k_set_signal_hook(ps2k_signal_hook_fn fn) { nk_signal_hook = fn; }
void ps2k_set_phase_hook(ps2k_phase_hook_fn fn) { nk_phase_hook = fn; }
void ps2k_set_parked_hook(ps2k_parked_hook_fn fn) { nk_parked_hook = fn; }
void ps2k_set_block_hook(ps2k_block_hook_fn fn) { nk_block_hook = fn; }
int ps2k_native(void) { return NK.inited; }
void ps2k_get_native_stats(ps2k_native_stats *out)
{
    if (out)
        *out = NK.nst;
}

/* ======================================================================
 * trace (the run hash folds it every field)
 * ==================================================================== */

static void fnv(uint64_t *h, uint64_t v, int bytes)
{
    for (int i = 0; i < bytes; i++) {
        *h ^= (uint8_t)(v >> (8 * i));
        *h *= 0x100000001b3ull;
    }
}

void nk_trace(int type, int32_t a, int32_t b)
{
    ps2k_trace_rec r;
    r.seq = NK.trace_n++;
    r.time = NK.now;
    r.type = type;
    r.a = a;
    r.b = b;
    fnv(&NK.trace_hash, r.time, 8);
    fnv(&NK.trace_hash, (uint32_t)type, 4);
    fnv(&NK.trace_hash, (uint32_t)a, 4);
    fnv(&NK.trace_hash, (uint32_t)b, 4);
    NK.ring[r.seq % NKTRACE_RING] = r;
    if (NK.trace_hook)
        NK.trace_hook(&r, NK.trace_user);
}

uint64_t ps2k_trace_hash(void) { return NK.trace_hash; }
uint64_t ps2k_trace_count(void) { return NK.trace_n; }

void ps2k_set_trace_hook(ps2k_trace_fn fn, void *user)
{
    NK.trace_hook = fn;
    NK.trace_user = user;
}

static const char *trace_name(int t)
{
    static const char *const n[] = {"?", "switch", "idle-jump", "intc", "dmac", "alarm", "thread",
                                    "sema-signal", "sema-wait", "wakeup", "preempt", "raise", "violation"};
    return t >= 0 && t < (int)(sizeof n / sizeof n[0]) ? n[t] : "?";
}

void ps2k_trace_dump(FILE *f, int last_n)
{
    uint64_t n = NK.trace_n, start = 0;
    if (last_n > NKTRACE_RING)
        last_n = NKTRACE_RING;
    if (last_n >= 0 && n > (uint64_t)last_n)
        start = n - (uint64_t)last_n;
    if (n > NKTRACE_RING && start < n - NKTRACE_RING)
        start = n - NKTRACE_RING;
    for (uint64_t i = start; i < n; i++) {
        const ps2k_trace_rec *r = &NK.ring[i % NKTRACE_RING];
        fprintf(f, "%8llu t=%12llu %-11s %d %d\n", (unsigned long long)r->seq, (unsigned long long)r->time,
                trace_name(r->type), r->a, r->b);
    }
}

/* ======================================================================
 * violations
 * ==================================================================== */

int nk_violation(const char *call, const char *why)
{
    NK.violations++;
    nk_trace(PS2K_TR_VIOLATION, 0, 0);
    if (NK.violation) {
        NK.violation(call, why);
    } else {
        fprintf(stderr, "ps2k (native): context violation in %s: %s\n", call, why);
        fflush(stderr);
        abort();
    }
    return PS2K_ERR;
}

void ps2k_set_violation_hook(ps2k_violation_fn fn) { NK.violation = fn; }
uint32_t ps2k_violation_count(void) { return NK.violations; }

/* ======================================================================
 * lifetime
 * ==================================================================== */

void ps2k_default_config(ps2k_config *cfg)
{
    memset(cfg, 0, sizeof *cfg);
    cfg->host_stack_size = 1u << 20;
    cfg->vblank_enable = 1;
    cfg->vblank_start_line = 240;
    cfg->native = 1;
}

int ps2k_init(const ps2k_config *cfg)
{
    if (NK.running)
        return -1;
    ps2k_violation_fn keep_violation = NK.violation;
    for (int i = 0; i < PS2K_MAX_THREADS; i++)
        if (NK.threads[i].fiber)
            ps2k_fiber_destroy(NK.threads[i].fiber);
    memset(&NK, 0, sizeof NK);
    NK.violation = keep_violation;
    if (cfg)
        NK.cfg = *cfg;
    else
        ps2k_default_config(&NK.cfg);
    NK.cfg.native = 1;      /* the only mode this table has */
    NK.cfg.kcall_cycles = 0;/* a flow's own work costs no logic time */
    if (NK.cfg.host_stack_size < 64 * 1024)
        NK.cfg.host_stack_size = 64 * 1024;
    NK.trace_hash = 0xcbf29ce484222325ull;
    NK.eie = 1;
    NK.thread_eie = 1;
    NK.next_handler_id = 1;
    /* VALIDATION.md 2c: sema ids from 0, last freed = first reused; threads from 2 (main 1) */
    for (int i = 0; i < PS2K_MAX_SEMAS; i++)
        NK.semas[i].free_next = i + 1 < PS2K_MAX_SEMAS ? i + 1 : -1;
    NK.sema_free = 0;
    NK.next_thread_id = 2;
    NK.inited = 1;
    nk_irq_reset();
    {
        /* EE FPU mode for game code (rg_nk_internal.h): round toward zero + FTZ + DAZ,
         * the retail rounding (docs/BRINGUP.md "Retail parity"; USER decision, default
         * since 2026-10-24).  RG_EE_FPU=ieee: the host's round to nearest (opt-out). */
        const char *m = getenv("RG_EE_FPU");
        nk_guest_csr = (m && !strcmp(m, "ieee")) ? 0u : (0x1F80u | 0x6000u | 0x8040u);
    }
    return 0;
}

void ps2k_shutdown(void)
{
    if (NK.running)
        return;
    for (int i = 0; i < PS2K_MAX_THREADS; i++)
        if (NK.threads[i].fiber)
            ps2k_fiber_destroy(NK.threads[i].fiber);
    ps2k_violation_fn keep_violation = NK.violation;
    memset(&NK, 0, sizeof NK);
    NK.violation = keep_violation;
}

int ps2k_stop_code(void) { return NK.stop_code; }
const char *ps2k_backend_name(void) { return ps2k_fiber_backend_name(); }

/* ======================================================================
 * ready flows (FIFO per priority: priorities only order simultaneous wakes)
 * ==================================================================== */

static void rq_push_tail(nkthread *t)
{
    int p = t->prio;
    t->qnext = NULL;
    t->qprev = NK.rq_tail[p];
    if (NK.rq_tail[p])
        NK.rq_tail[p]->qnext = t;
    else
        NK.rq_head[p] = t;
    NK.rq_tail[p] = t;
}

static void rq_push_head(nkthread *t)
{
    int p = t->prio;
    t->qprev = NULL;
    t->qnext = NK.rq_head[p];
    if (NK.rq_head[p])
        NK.rq_head[p]->qprev = t;
    else
        NK.rq_tail[p] = t;
    NK.rq_head[p] = t;
}

static void rq_remove(nkthread *t)
{
    int p = t->prio;
    if (t->qprev)
        t->qprev->qnext = t->qnext;
    else
        NK.rq_head[p] = t->qnext;
    if (t->qnext)
        t->qnext->qprev = t->qprev;
    else
        NK.rq_tail[p] = t->qprev;
    t->qnext = t->qprev = NULL;
}

static nkthread *ready_top(void)
{
    for (int p = 0; p <= PS2K_PRIO_MAX; p++)
        if (NK.rq_head[p])
            return NK.rq_head[p];
    return NULL;
}

static void set_status(nkthread *t, int st)
{
    t->status = st;
    nk_trace(PS2K_TR_THREAD, t->id, st);
}

/* A wait finished (sema signalled / deleted, wakeup, release, a kernel-private wake). */
void nk_make_ready(nkthread *t)
{
    if (t->driven == 2) { /* parked: its WaitSema returned; the frame driver runs it */
        t->wait_type = PS2K_TSW_KWAIT;
        t->wait_id = 0;
        t->kwait = KW_DRIVEN;
        t->driven_woken = 1;
        nk_trace(PS2K_TR_THREAD, t->id, PS2K_THS_READY);
        return;
    }
    t->wait_type = PS2K_TSW_NONE;
    t->wait_id = 0;
    if (t->status == PS2K_THS_WAITSUSPEND) {
        set_status(t, PS2K_THS_SUSPEND);
    } else {
        set_status(t, PS2K_THS_READY);
        rq_push_tail(t);
    }
}

/* ======================================================================
 * switching: only a flow that waits (or a stop request) returns to the driver
 * ==================================================================== */

static void save_eie(nkthread *t)
{
    if (NK.cfg.eie_per_thread)
        t->eie = NK.eie;
    else
        NK.thread_eie = NK.eie;
}

static int switch_in_eie(const nkthread *t) { return NK.cfg.eie_per_thread ? t->eie : NK.thread_eie; }

static void switch_to_driver(void)
{
    nkthread *t = NK.cur;
    if (NK.in_step) { /* a driven step has no stack of its own to block on */
        fprintf(stderr, "ps2k: driven step of thread %d blocked (status %d, wait %d/%d); a step must run to "
                        "completion (docs/NATIVE-THREADS.md \"Slice 5\")\n",
                t->id, t->status, t->wait_type, t->wait_id);
        fflush(stderr);
        abort();
    }
    save_eie(t);
    ps2k_fiber_switch(t->fiber, NK.sched);
}

static int block_current(void)
{
    switch_to_driver();
    return NK.cur->wait_result;
}

/* a flow runs until it waits; only a stop request switches it out */
static void maybe_stop(void)
{
    nkthread *c = NK.cur;
    if (!c || NK.in_handler || !NK.stop_req || NK.in_step)
        return;
    if (c->status == PS2K_THS_RUN) {
        set_status(c, PS2K_THS_READY);
        rq_push_head(c);
    }
    switch_to_driver();
}

/* Every kernel call starts here (context checks only: no delivery inside a flow). */
int nk_enter(const char *call, int isr)
{
    if (isr) {
        if (!NK.in_handler)
            return nk_violation(call, "i-variant called outside interrupt handler context");
        return 0;
    }
    if (NK.in_handler)
        return nk_violation(call, "thread-context call made from an interrupt handler");
    return 0;
}

static int need_thread(const char *call)
{
    if (!NK.cur)
        return nk_violation(call, "blocking call outside a guest thread");
    return 0;
}

static nkthread *thread_get(int id)
{
    if (id <= 0 || id >= PS2K_MAX_THREADS)
        return NULL;
    nkthread *t = &NK.threads[id];
    return t->used ? t : NULL;
}

static nkthread *thread_get_self_ok(int id)
{
    if (id == PS2K_TH_SELF)
        return NK.cur;
    return thread_get(id);
}

static void flow_trampoline(void *p)
{
    nkthread *t = (nkthread *)p;
    nk_fpu_enter(); /* a new fiber's float state need not be its creator's */
    t->entry(t->arg);
    ps2k_exit_thread();
}

static void reap(void)
{
    for (int i = 1; i < PS2K_MAX_THREADS; i++) {
        nkthread *t = &NK.threads[i];
        if (!t->used || !t->fiber_dead)
            continue;
        if (t->fiber)
            ps2k_fiber_destroy(t->fiber);
        t->fiber = NULL;
        t->fiber_dead = 0;
        if (t->delete_pending)
            memset(t, 0, sizeof *t);
    }
}

/* service threads belong to the HLE (RG_THREADS=service): none here */
int ps2k_thread_set_service(int id, ps2k_svc_wait_fn wait, ps2k_entry_fn step)
{
    (void)id;
    (void)wait;
    (void)step;
    return PS2K_ERR;
}
uint32_t ps2k_svc_deferred_count(void) { return 0; }
uint32_t ps2k_svc_step_count(void) { return 0; }

/* ======================================================================
 * the driver loop
 * ==================================================================== */

void ps2k_request_stop(void)
{
    if (!NK.stop_req) {
        NK.stop_req = 1;
        NK.stop_reason = PS2K_RUN_STOPPED;
    }
    maybe_stop();
}

int ps2k_running(void) { return NK.running; }

int ps2k_start(ps2k_entry_fn main_entry, void *arg, int main_priority)
{
    if (!NK.inited || NK.running)
        return PS2K_RUN_ERROR;
    NK.sched = ps2k_fiber_adopt_host();
    if (!NK.sched)
        return PS2K_RUN_ERROR;
    NK.running = 1;
    NK.cur = NULL;
    NK.eie = 1;
    NK.thread_eie = 1;
    NK.want_main_id = 1; /* retail: the main thread is id 1 (VALIDATION.md 2c) */
    int id = ps2k_create_thread(main_entry, NULL, 0, NULL, main_priority, 0, 0);
    NK.want_main_id = 0;
    if (id < 0 || ps2k_start_thread(id, arg) < 0) {
        ps2k_finish(PS2K_RUN_ERROR);
        return PS2K_RUN_ERROR;
    }
    NK.main_id = id;
    NK.idle_since = NK.now;
    return 0;
}

/* Run the flows (main, the loading screen) one at a time until each waits; every pass
 * delivers what is latched (VBLANK_START / END handlers, the VIF1 completion) as explicit
 * calls in kernel context, then the phase hook runs the driven steps that are due; when
 * every flow waits, logic time jumps to the next event (VBlank edge, timed wait). */
int ps2k_step(uint64_t until_vblank)
{
    if (!NK.running || NK.cur || NK.in_handler)
        return PS2K_RUN_ERROR;
    int rc = PS2K_RUN_ERROR;
    unsigned host_csr = nk_fpu_enter(); /* EE FPU mode for game code (rg_nk_internal.h) */
    for (;;) {
        reap();
        if (NK.stop_req) {
            rc = NK.stop_reason;
            break;
        }
        nk_process_due();
        nk_deliver();
        if (nk_phase_hook) {
            NK.nst.passes++;
            nk_phase_hook();
            nk_deliver(); /* a step's signals can make poll waiters due */
        }
        if (NK.stop_req)
            continue;
        if (until_vblank && NK.vblank_count >= until_vblank) {
            rc = PS2K_RUN_YIELD;
            break;
        }
        nk_poll_wake(0);
        nkthread *t = ready_top();
        if (t) {
            rq_remove(t);
            set_status(t, PS2K_THS_RUN);
            if (!t->fiber) {
                t->fiber = ps2k_fiber_create(NK.cfg.host_stack_size, flow_trampoline, t);
                if (!t->fiber) {
                    rc = PS2K_RUN_ERROR;
                    break;
                }
                NK.nst.flows++;
            }
            NK.cur = t;
            NK.eie = switch_in_eie(t);
            NK.activity++;
            NK.nst.flow_switches++;
            nk_trace(PS2K_TR_SWITCH, t->id, t->prio);
            NK_TAP(PS2K_TAP_SWITCH, t->id, t->prio, (const void *)t->entry);
            ps2k_fiber_switch(NK.sched, t->fiber);
            NK.cur = NULL;
            NK.eie = 1;
            NK.idle_since = NK.now;
            continue;
        }
        /* every flow waits: logic time jumps to the next event */
        uint64_t next;
        if (!nk_next_due(&next) && NK.kwait_n > 0) {
            nk_poll_wake(1);
            if (ready_top())
                continue;
        }
        if (!nk_next_due(&next)) {
            rc = PS2K_RUN_DEADLOCK;
            break;
        }
        if (NK.cfg.stop_at_cycles && next > NK.cfg.stop_at_cycles) {
            if (NK.cfg.stop_at_cycles > NK.now)
                NK.now = NK.cfg.stop_at_cycles;
            rc = PS2K_RUN_TIME_LIMIT;
            break;
        }
        if (NK.cfg.stall_cycles && next - NK.idle_since > NK.cfg.stall_cycles) {
            rc = PS2K_RUN_STALL;
            break;
        }
        if (next > NK.now) {
            if (NK.pacing) {
                nk_fpu_leave(host_csr);
                NK.pacing(NK.now, next, NK.pacing_user);
                nk_fpu_enter();
            }
            NK.now = next;
            nk_trace(PS2K_TR_IDLE_JUMP, (int32_t)(uint32_t)next, (int32_t)(uint32_t)(next >> 32));
        }
    }
    nk_fpu_leave(host_csr);
    return rc;
}

void *ps2k_step_enter(int id)
{
    nkthread *t = (id > 0 && id < PS2K_MAX_THREADS && NK.threads[id].used) ? &NK.threads[id] : NULL;
    if (!t || t->driven != 2 || NK.in_handler)
        return NULL;
    uintptr_t tok = (uintptr_t)NK.cur | (uintptr_t)(NK.in_step ? 1 : 0);
    NK.cur = t;
    NK.in_step = 1;
    NK.activity++;
    return (void *)(tok | 2u); /* never NULL */
}

void ps2k_step_leave(void *token)
{
    if (!token)
        return;
    uintptr_t tok = (uintptr_t)token;
    NK.cur = (nkthread *)(tok & ~(uintptr_t)3);
    NK.in_step = (int)(tok & 1);
}

int ps2k_in_step(void) { return NK.in_step; }
int ps2k_ready_at(int priority) { return priority >= 0 && priority <= PS2K_PRIO_MAX && NK.rq_head[priority] != NULL; }

void ps2k_finish(int code)
{
    if (!NK.running)
        return;
    for (int i = 1; i < PS2K_MAX_THREADS; i++) {
        if (NK.threads[i].fiber) {
            ps2k_fiber_destroy(NK.threads[i].fiber);
            NK.threads[i].fiber = NULL;
        }
    }
    ps2k_fiber_release_host(NK.sched);
    NK.sched = NULL;
    NK.running = 0;
    NK.cur = NULL;
    NK.stop_code = code;
}

int ps2k_run(ps2k_entry_fn main_entry, void *arg, int main_priority)
{
    if (ps2k_start(main_entry, arg, main_priority) != 0)
        return PS2K_RUN_ERROR;
    int rc = ps2k_step(0);
    ps2k_finish(rc);
    return rc;
}

/* ======================================================================
 * thread objects (game-visible ids)
 * ==================================================================== */

int ps2k_create_thread(ps2k_entry_fn entry, void *stack, int32_t stack_size, void *gp, int32_t priority,
                       uint32_t attr, uint32_t option)
{
    if (nk_enter("CreateThread", 0))
        return PS2K_ERR;
    if (!entry || priority < 0 || priority > PS2K_PRIO_MAX)
        return PS2K_ERR;
    /* VALIDATION.md 2c: next-fit from the cursor (2 at init; main takes 1), wrapping */
    int i = -1;
    if (NK.want_main_id && !NK.threads[NK.want_main_id].used) {
        i = NK.want_main_id;
    } else {
        for (int n = 0; n < PS2K_MAX_THREADS - 1; n++) {
            int c = 1 + (NK.next_thread_id - 1 + n) % (PS2K_MAX_THREADS - 1);
            if (!NK.threads[c].used) {
                i = c;
                break;
            }
        }
        if (i < 0)
            return PS2K_ERR;
        NK.next_thread_id = 1 + i % (PS2K_MAX_THREADS - 1);
    }
    nkthread *t = &NK.threads[i];
    memset(t, 0, sizeof *t);
    t->used = 1;
    t->id = i;
    t->entry = entry;
    t->stack = stack;
    t->stack_size = stack_size;
    t->gp = gp;
    t->init_prio = t->prio = priority;
    t->attr = attr;
    t->option = option;
    t->eie = 1;
    set_status(t, PS2K_THS_DORMANT);
    return i;
}

int ps2k_delete_thread(int id)
{
    if (nk_enter("DeleteThread", 0))
        return PS2K_ERR;
    nkthread *t = thread_get(id);
    if (!t || t == NK.cur || t->status != PS2K_THS_DORMANT)
        return PS2K_ERR;
    if (t->fiber)
        ps2k_fiber_destroy(t->fiber);
    memset(t, 0, sizeof *t);
    return id;
}

int ps2k_start_thread(int id, void *arg)
{
    if (nk_enter("StartThread", 0))
        return PS2K_ERR;
    nkthread *t = thread_get(id);
    if (!t || t->status != PS2K_THS_DORMANT || t->fiber_dead)
        return PS2K_ERR;
    if (t->fiber) {
        ps2k_fiber_destroy(t->fiber);
        t->fiber = NULL;
    }
    t->arg = arg;
    t->prio = t->init_prio;
    t->wakeup_count = 0;
    t->eie = 1;
    t->wait_type = PS2K_TSW_NONE;
    t->wait_id = 0;
    if (nk_start_hook)
        nk_start_hook(id, t->entry, arg);
    if (t->driven) { /* parked: the frame driver runs its body (no fiber, never readied) */
        t->driven = 2;
        t->driven_woken = 0;
        t->kwait = KW_DRIVEN;
        t->wait_type = PS2K_TSW_KWAIT;
        set_status(t, PS2K_THS_WAIT);
        if (nk_parked_hook)
            nk_parked_hook(id);
        return id;
    }
    set_status(t, PS2K_THS_READY); /* a flow: it runs when the running one waits */
    rq_push_tail(t);
    maybe_stop();
    return id;
}

static void exit_common(const char *call, int del)
{
    if (nk_enter(call, 0) || need_thread(call))
        return;
    nkthread *t = NK.cur;
    set_status(t, PS2K_THS_DORMANT);
    t->fiber_dead = 1;
    t->delete_pending = del;
    if (t->id == NK.main_id && !NK.stop_req) {
        NK.stop_req = 1;
        NK.stop_reason = PS2K_RUN_MAIN_EXIT;
    }
    save_eie(t);
    ps2k_fiber_switch(t->fiber, NK.sched);
    abort(); /* never resumed */
}

void ps2k_exit_thread(void) { exit_common("ExitThread", 0); }
void ps2k_exit_delete_thread(void) { exit_common("ExitDeleteThread", 1); }

/* ======================================================================
 * kernel-private waits (no game-visible ids)
 * ==================================================================== */

static void kwait_remove(nkthread *t)
{
    int j = 0;
    for (int i = 0; i < NK.kwait_n; i++)
        if (NK.kwait_fifo[i] != t->id)
            NK.kwait_fifo[j++] = NK.kwait_fifo[i];
    NK.kwait_n = j;
    if (t->kwait == KW_TIME || t->kwait == KW_POLL)
        nk_ev_remove(NEV_KWAKE, t->id);
    if (t->kwait == KW_DRIVEN)
        t->driven = 0;
    t->kwait = KW_NONE;
    t->poll_due = 0;
}

void nk_kwait_wake(int tid, int kind)
{
    for (int i = 0; i < NK.kwait_n;) {
        nkthread *t = &NK.threads[NK.kwait_fifo[i]];
        int due = t->used && t->kwait == kind && (kind == KW_TIME ? t->id == tid : NK.vblank_count >= t->kwait_arg);
        if (!due) {
            i++;
            continue;
        }
        memmove(&NK.kwait_fifo[i], &NK.kwait_fifo[i + 1], (size_t)(NK.kwait_n - i - 1) * sizeof(int));
        NK.kwait_n--;
        t->kwait = KW_NONE;
        t->wait_result = 0;
        nk_make_ready(t);
    }
}

void nk_poll_wake(int idle)
{
    for (int i = 0; i < NK.kwait_n;) {
        nkthread *t = &NK.threads[NK.kwait_fifo[i]];
        if (!(t->used && t->kwait == KW_POLL && t->poll_due && (idle || NK.activity != t->poll_seen))) {
            i++;
            continue;
        }
        memmove(&NK.kwait_fifo[i], &NK.kwait_fifo[i + 1], (size_t)(NK.kwait_n - i - 1) * sizeof(int));
        NK.kwait_n--;
        t->kwait = KW_NONE;
        t->poll_due = 0;
        t->wait_result = 0;
        nk_make_ready(t);
    }
}

static int kwait_block2(const char *call, int kind, uint64_t arg, int entered)
{
    if (!entered && nk_enter(call, 0))
        return PS2K_ERR;
    if (!NK.cur)
        return nk_violation(call, "blocking call outside a guest thread");
    if (kind == KW_TIME && arg <= NK.now)
        return 0;
    if (kind == KW_VBLANK && NK.vblank_count >= arg)
        return 0;
    nkthread *c = NK.cur;
    NK_TAP(PS2K_TAP_KWAIT, kind, (int32_t)arg, NULL);
    if (NK.kwait_n >= PS2K_MAX_THREADS)
        return PS2K_ERR;
    if ((kind == KW_TIME || kind == KW_POLL) && nk_ev_add(arg, NEV_KWAKE, c->id) < 0)
        return PS2K_ERR;
    NK.kwait_fifo[NK.kwait_n++] = c->id;
    c->kwait = kind;
    c->kwait_arg = arg;
    c->poll_due = 0;
    c->wait_type = PS2K_TSW_KWAIT;
    c->wait_id = 0;
    c->wait_result = PS2K_ERR;
    set_status(c, PS2K_THS_WAIT);
    return block_current() < 0 ? PS2K_ERR : 0;
}

static int kwait_block(const char *call, int kind, uint64_t arg) { return kwait_block2(call, kind, arg, 0); }

int ps2k_wait_poll(uint64_t time)
{
    if (NK.in_handler || !NK.cur)
        return PS2K_ERR;
    if (nk_enter("WaitPoll", 0))
        return PS2K_ERR;
    nkthread *c = NK.cur;
    int kind = NK.activity != c->poll_seen ? KW_TIME : KW_POLL;
    int r;
    if (kind == KW_POLL && time <= NK.now) { /* due already: wait for the next activity only */
        c->poll_due = 1;
        if (NK.kwait_n >= PS2K_MAX_THREADS)
            return PS2K_ERR;
        NK_TAP(PS2K_TAP_KWAIT, 3, (int32_t)time, NULL);
        NK.kwait_fifo[NK.kwait_n++] = c->id;
        c->kwait = KW_POLL;
        c->kwait_arg = time;
        c->wait_type = PS2K_TSW_KWAIT;
        c->wait_id = 0;
        c->wait_result = PS2K_ERR;
        set_status(c, PS2K_THS_WAIT);
        r = block_current() < 0 ? PS2K_ERR : 0;
    } else {
        r = kwait_block2("WaitPoll", kind, time, 1);
    }
    NK.cur->poll_seen = NK.activity;
    return r;
}

uint64_t ps2k_activity(void) { return NK.activity; }

int ps2k_wait_vblank(void)
{
    if (NK.in_handler || !NK.cur || !NK.cfg.vblank_enable)
        return PS2K_ERR;
    return kwait_block("WaitVblank", KW_VBLANK, NK.vblank_count + 1);
}

int ps2k_wait_until(uint64_t time)
{
    if (NK.in_handler || !NK.cur)
        return PS2K_ERR;
    return kwait_block("WaitUntil", KW_TIME, time);
}

/* ======================================================================
 * driven threads (docs/NATIVE-THREADS.md "Driven threads")
 * ==================================================================== */

static nkthread *any_thread(int id)
{
    return (id > 0 && id < PS2K_MAX_THREADS && NK.threads[id].used) ? &NK.threads[id] : NULL;
}

int ps2k_thread_set_driven(int id)
{
    nkthread *t = any_thread(id);
    if (!t || t->status != PS2K_THS_DORMANT || t->fiber || id == NK.main_id)
        return PS2K_ERR;
    t->driven = 1;
    return 0;
}

int ps2k_thread_driven_state(int id)
{
    nkthread *t = any_thread(id);
    if (!t || !t->driven)
        return 0;
    return t->driven == 2 && (t->status & PS2K_THS_WAIT) ? 2 : 1;
}

static nksema *sema_get(int id);

int ps2k_driven_wait(int id, int sema)
{
    nkthread *t = any_thread(id);
    if (!t || t->driven != 2 || !(t->status & PS2K_THS_WAIT) || t->wait_type == PS2K_TSW_SEMA)
        return PS2K_ERR;
    nksema *s = sema_get(sema);
    t->driven_woken = 0;
    if (!s || s->count > 0) { /* WaitSema returns at once (an invalid id: -1) */
        if (s)
            s->count--;
        t->driven_woken = 1;
        return 0;
    }
    t->kwait = KW_NONE;
    t->wnext = NULL;
    if (s->wtail)
        s->wtail->wnext = t;
    else
        s->whead = t;
    s->wtail = t;
    s->nwait++;
    t->wait_type = PS2K_TSW_SEMA;
    t->wait_id = sema;
    t->wait_result = PS2K_ERR;
    nk_trace(PS2K_TR_SEMA_WAIT, sema, t->id);
    return 0;
}

int ps2k_driven_take(int id)
{
    nkthread *t = any_thread(id);
    if (!t || t->driven != 2 || !t->driven_woken)
        return 0;
    t->driven_woken = 0;
    return 1;
}

int ps2k_driven_woken(int id)
{
    nkthread *t = any_thread(id);
    return t && t->driven == 2 && t->driven_woken;
}

static void unlink_thread(nkthread *t);

int ps2k_driven_exit(int id, int del)
{
    nkthread *t = any_thread(id);
    if (!t || t->driven != 2 || !(t->status & PS2K_THS_WAIT))
        return PS2K_ERR;
    unlink_thread(t);
    t->kwait = KW_NONE;
    t->wait_type = PS2K_TSW_NONE;
    t->driven = 0;
    t->driven_woken = 0;
    set_status(t, PS2K_THS_DORMANT);
    if (del)
        memset(t, 0, sizeof *t);
    return 0;
}

static void unlink_thread(nkthread *t)
{
    if (t->status == PS2K_THS_READY) {
        rq_remove(t);
    } else if ((t->status & PS2K_THS_WAIT) && t->wait_type == PS2K_TSW_SEMA) {
        nksema *s = &NK.semas[t->wait_id];
        nkthread **pp = &s->whead;
        nkthread *prev = NULL;
        while (*pp && *pp != t) {
            prev = *pp;
            pp = &(*pp)->wnext;
        }
        if (*pp) {
            *pp = t->wnext;
            if (s->wtail == t)
                s->wtail = prev;
            s->nwait--;
        }
        t->wnext = NULL;
    } else if ((t->status & PS2K_THS_WAIT) && t->wait_type == PS2K_TSW_KWAIT) {
        kwait_remove(t);
    }
}

/* ======================================================================
 * the rest of the thread API
 * ==================================================================== */

int ps2k_terminate_thread(int id, int isr)
{
    if (nk_enter(isr ? "iTerminateThread" : "TerminateThread", isr))
        return PS2K_ERR;
    nkthread *t = thread_get(id);
    if (!t || t == NK.cur || t->status == PS2K_THS_DORMANT)
        return PS2K_ERR;
    unlink_thread(t);
    t->driven = 0;
    t->driven_woken = 0;
    t->wait_type = PS2K_TSW_NONE;
    t->wait_id = 0;
    set_status(t, PS2K_THS_DORMANT);
    if (t->fiber) {
        ps2k_fiber_destroy(t->fiber);
        t->fiber = NULL;
    }
    if (t->id == NK.main_id && !NK.stop_req) {
        NK.stop_req = 1;
        NK.stop_reason = PS2K_RUN_MAIN_EXIT;
    }
    return id;
}

/* VALIDATION.md 2d: the running thread goes to the TAIL of its (new) priority's queue,
 * so a change to its own priority yields to an equal-priority ready flow (a real switch
 * between flows; no other thread kind can be ready) */
int ps2k_change_thread_priority(int id, int priority, int isr)
{
    if (nk_enter(isr ? "iChangeThreadPriority" : "ChangeThreadPriority", isr))
        return PS2K_ERR;
    nkthread *t = thread_get_self_ok(id);
    if (!t || t->status == PS2K_THS_DORMANT || priority < 0 || priority > PS2K_PRIO_MAX)
        return PS2K_ERR;
    int old = t->prio;
    if (t->status == PS2K_THS_READY) {
        rq_remove(t);
        t->prio = priority;
        rq_push_tail(t);
    } else {
        t->prio = priority;
    }
    if (t == NK.cur && t->status == PS2K_THS_RUN) {
        if (!isr) {
            nkthread *h = ready_top();
            if (h && h->prio <= t->prio) {
                set_status(t, PS2K_THS_READY);
                rq_push_tail(t);
                nk_trace(PS2K_TR_PREEMPT, t->id, h->id);
                switch_to_driver();
            }
        }
        return old;
    }
    if (!isr)
        maybe_stop();
    return old;
}

int ps2k_rotate_thread_ready_queue(int priority, int isr)
{
    if (nk_enter(isr ? "iRotateThreadReadyQueue" : "RotateThreadReadyQueue", isr))
        return PS2K_ERR;
    if (priority < 0 || priority > PS2K_PRIO_MAX)
        return PS2K_ERR;
    nkthread *c = NK.cur;
    if (c && c->status == PS2K_THS_RUN && c->prio == priority) {
        /* yield to the next ready flow of the same priority (none: return at once) */
        if (!isr && NK.rq_head[priority]) {
            set_status(c, PS2K_THS_READY);
            rq_push_tail(c);
            switch_to_driver();
        }
        return priority;
    }
    nkthread *h = NK.rq_head[priority];
    if (h && h != NK.rq_tail[priority]) {
        rq_remove(h);
        rq_push_tail(h);
    }
    return priority;
}

int ps2k_release_wait_thread(int id, int isr)
{
    if (nk_enter(isr ? "iReleaseWaitThread" : "ReleaseWaitThread", isr))
        return PS2K_ERR;
    nkthread *t = thread_get(id);
    if (!t || !(t->status & PS2K_THS_WAIT) || t->driven == 2)
        return PS2K_ERR;
    unlink_thread(t);
    t->wait_result = PS2K_ERR;
    nk_make_ready(t);
    if (!isr)
        maybe_stop();
    return id;
}

int ps2k_get_thread_id(void) { return NK.cur ? NK.cur->id : 0; }

int ps2k_refer_thread_status(int id, ps2k_thread_info *out, int isr)
{
    if (nk_enter(isr ? "iReferThreadStatus" : "ReferThreadStatus", isr))
        return PS2K_ERR;
    nkthread *t = thread_get_self_ok(id);
    if (!t)
        return PS2K_ERR;
    if (out) {
        out->status = t->status;
        out->entry = (void *)t->entry;
        out->stack = t->stack;
        out->stack_size = t->stack_size;
        out->gp = t->gp;
        out->init_priority = t->init_prio;
        out->current_priority = t->prio;
        out->attr = t->attr;
        out->option = t->option;
        out->wait_type = ((t->status & PS2K_THS_WAIT) && t->wait_type != PS2K_TSW_KWAIT) ? t->wait_type : 0;
        out->wait_id = (t->status & PS2K_THS_WAIT) ? t->wait_id : 0;
        out->wakeup_count = t->wakeup_count;
    }
    return t->status;
}

int ps2k_sleep_thread(void)
{
    if (nk_enter("SleepThread", 0) || need_thread("SleepThread"))
        return PS2K_ERR;
    nkthread *c = NK.cur;
    if (c->wakeup_count > 0) {
        c->wakeup_count--;
        nk_trace(PS2K_TR_WAKEUP, c->id, c->wakeup_count);
        return c->id;
    }
    c->wait_type = PS2K_TSW_SLEEP;
    c->wait_id = 0;
    c->wait_result = c->id;
    set_status(c, PS2K_THS_WAIT);
    return block_current();
}

int ps2k_wakeup_thread(int id, int isr)
{
    if (nk_enter(isr ? "iWakeupThread" : "WakeupThread", isr))
        return PS2K_ERR;
    nkthread *t = thread_get(id);
    if (!t || t->status == PS2K_THS_DORMANT || (!isr && t == NK.cur))
        return PS2K_ERR;
    if ((t->status & PS2K_THS_WAIT) && t->wait_type == PS2K_TSW_SLEEP) {
        t->wait_result = t->id;
        nk_make_ready(t);
        nk_trace(PS2K_TR_WAKEUP, t->id, -1);
    } else {
        t->wakeup_count++;
        nk_trace(PS2K_TR_WAKEUP, t->id, t->wakeup_count);
    }
    if (!isr)
        maybe_stop();
    return id;
}

int ps2k_cancel_wakeup_thread(int id, int isr)
{
    if (nk_enter(isr ? "iCancelWakeupThread" : "CancelWakeupThread", isr))
        return PS2K_ERR;
    nkthread *t = thread_get_self_ok(id);
    if (!t)
        return PS2K_ERR;
    int n = t->wakeup_count;
    t->wakeup_count = 0;
    return n;
}

int ps2k_suspend_thread(int id, int isr)
{
    if (nk_enter(isr ? "iSuspendThread" : "SuspendThread", isr))
        return PS2K_ERR;
    nkthread *t = thread_get(id);
    if (!t || (!isr && t == NK.cur))
        return PS2K_ERR;
    switch (t->status) {
    case PS2K_THS_READY:
        rq_remove(t);
        set_status(t, PS2K_THS_SUSPEND);
        break;
    case PS2K_THS_RUN:
        set_status(t, PS2K_THS_SUSPEND);
        break;
    case PS2K_THS_WAIT:
        set_status(t, PS2K_THS_WAITSUSPEND);
        break;
    default:
        return PS2K_ERR;
    }
    return id;
}

int ps2k_resume_thread(int id, int isr)
{
    if (nk_enter(isr ? "iResumeThread" : "ResumeThread", isr))
        return PS2K_ERR;
    nkthread *t = thread_get(id);
    if (!t)
        return PS2K_ERR;
    if (t->status == PS2K_THS_SUSPEND) {
        if (t == NK.cur) {
            set_status(t, PS2K_THS_RUN);
        } else {
            set_status(t, PS2K_THS_READY);
            rq_push_tail(t);
        }
    } else if (t->status == PS2K_THS_WAITSUSPEND) {
        set_status(t, PS2K_THS_WAIT);
    } else {
        return PS2K_ERR;
    }
    if (!isr)
        maybe_stop();
    return id;
}

/* ======================================================================
 * semaphores (game-visible ids)
 * ==================================================================== */

static nksema *sema_get(int id)
{
    if (id < 0 || id >= PS2K_MAX_SEMAS)
        return NULL;
    nksema *s = &NK.semas[id];
    return s->used ? s : NULL;
}

int ps2k_peek_sema(int id, int32_t *count, int32_t *nwait)
{
    nksema *s = sema_get(id);
    if (!s)
        return -1;
    if (count)
        *count = s->count;
    if (nwait)
        *nwait = s->nwait;
    return 0;
}

int ps2k_peek_priority(void) { return NK.cur ? NK.cur->prio : -1; }

int ps2k_create_sema(int32_t init_count, int32_t max_count, uint32_t attr, uint32_t option)
{
    if (nk_enter("CreateSema", 0))
        return PS2K_ERR;
    if (init_count < 0)
        return PS2K_ERR;
    int i = NK.sema_free;
    if (i < 0)
        return PS2K_ERR;
    nksema *s = &NK.semas[i];
    NK.sema_free = s->free_next;
    memset(s, 0, sizeof *s);
    s->free_next = -1;
    s->used = 1;
    s->count = init_count;
    s->init = init_count;
    s->max = max_count;
    s->attr = attr;
    s->option = option;
    return i;
}

int ps2k_delete_sema(int id, int isr)
{
    if (nk_enter(isr ? "iDeleteSema" : "DeleteSema", isr))
        return PS2K_ERR;
    nksema *s = sema_get(id);
    if (!s)
        return PS2K_ERR;
    nkthread *w = s->whead;
    s->whead = s->wtail = NULL;
    s->nwait = 0;
    s->used = 0;
    s->free_next = NK.sema_free;
    NK.sema_free = id;
    while (w) {
        nkthread *n = w->wnext;
        w->wnext = NULL;
        w->wait_result = PS2K_ERR;
        nk_make_ready(w);
        w = n;
    }
    if (!isr)
        maybe_stop();
    return id;
}

int ps2k_signal_sema(int id, int isr)
{
    if (nk_enter(isr ? "iSignalSema" : "SignalSema", isr))
        return PS2K_ERR;
    nksema *s = sema_get(id);
    if (!s)
        return PS2K_ERR;
    nkthread *w = s->whead;
    if (w) {
        s->whead = w->wnext;
        if (!s->whead)
            s->wtail = NULL;
        w->wnext = NULL;
        s->nwait--;
        w->wait_result = id;
        nk_trace(PS2K_TR_SEMA_SIGNAL, id, w->id);
        nk_make_ready(w);
        if (w->driven == 2) { /* a parked thread woke: the frame driver may run it here */
            if (!isr && nk_signal_hook && NK.cur)
                nk_signal_hook(id);
            return id;
        }
        if (!isr)
            maybe_stop();
        return id;
    }
    s->count++; /* VALIDATION.md 2b: no cap */
    nk_trace(PS2K_TR_SEMA_SIGNAL, id, 0);
    return id;
}

int ps2k_wait_sema(int id)
{
    if (nk_enter("WaitSema", 0) || need_thread("WaitSema"))
        return PS2K_ERR;
    nksema *s = sema_get(id);
    if (!s)
        return PS2K_ERR;
    if (s->count <= 0 && NK.in_step && nk_block_hook) {
        /* a driven step would block: the driver runs other woken steps that may signal it */
        nk_block_hook(id);
        s = sema_get(id);
        if (!s)
            return PS2K_ERR;
    }
    if (s->count > 0) {
        s->count--;
        return id;
    }
    nkthread *c = NK.cur;
    c->wnext = NULL;
    if (s->wtail)
        s->wtail->wnext = c;
    else
        s->whead = c;
    s->wtail = c;
    s->nwait++;
    c->wait_type = PS2K_TSW_SEMA;
    c->wait_id = id;
    c->wait_result = PS2K_ERR;
    nk_trace(PS2K_TR_SEMA_WAIT, id, c->id);
    set_status(c, PS2K_THS_WAIT);
    return block_current();
}

int ps2k_poll_sema(int id, int isr)
{
    if (nk_enter(isr ? "iPollSema" : "PollSema", isr))
        return PS2K_ERR;
    nksema *s = sema_get(id);
    if (!s || s->count <= 0)
        return PS2K_ERR;
    s->count--;
    return id;
}

int ps2k_refer_sema_status(int id, ps2k_sema_info *out, int isr)
{
    if (nk_enter(isr ? "iReferSemaStatus" : "ReferSemaStatus", isr))
        return PS2K_ERR;
    nksema *s = sema_get(id);
    if (!s)
        return PS2K_ERR;
    if (out) {
        out->current_count = s->count;
        out->max_count = s->max;
        out->init_count = s->init;
        out->num_wait_threads = s->nwait;
        out->attr = s->attr;
        out->option = s->option;
    }
    return id;
}

/* ======================================================================
 * DelayThread: a kernel-private timed wait (no semaphore, no alarm)
 * ==================================================================== */

uint64_t ps2k_usec_to_cycles(uint32_t usec) { return (uint64_t)usec * 147456u / 1000u; }

int ps2k_delay_thread(uint32_t usec)
{
    if ((NK.cur || NK.in_handler) && !NK.eie)
        return PS2K_DELAY_E_DISABLED; /* libkernl checks EIE first */
    if (NK.in_handler)
        return nk_violation("DelayThread", "thread-context call made from an interrupt handler");
    if (need_thread("DelayThread"))
        return PS2K_ERR;
    NK.nst.delays++;
    return kwait_block("DelayThread", KW_TIME, NK.now + ps2k_usec_to_cycles(usec)) < 0 ? PS2K_ERR : 0;
}

/* The HLE's deliberately wrong preemption (its non-preemption controls): a frame-driven
 * kernel has nothing to preempt with. */
void ps2k_debug_force_preempt(void) {}
