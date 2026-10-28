/* SPDX-License-Identifier: CC0-1.0
 * ps2k core: state, trace, scheduler, threads, semaphores (docs/KERNEL.md). */
#include <stdlib.h>
#include <string.h>

#include "internal.h"

kstate K;
ps2k_tap_fn k_tap; /* census tap: host state (src/savestate/ss_map.c) */
ps2k_start_hook_fn k_start_hook; /* frame driver: host state (src/savestate/ss_map.c) */
ps2k_signal_hook_fn k_signal_hook;
/* service-step counters: process totals (not reset by ps2k_init, read after shutdown) */
static uint32_t k_svc_steps, k_svc_deferred;

void ps2k_set_census_tap(ps2k_tap_fn fn) { k_tap = fn; }
void ps2k_set_start_hook(ps2k_start_hook_fn fn) { k_start_hook = fn; }
void ps2k_set_signal_hook(ps2k_signal_hook_fn fn) { k_signal_hook = fn; }
/* Frame-driven mode (RG_THREADS=native) is the native kernel table's (src/native/threads/
 * rg_nk*.c; kdispatch.c sends a cfg.native kernel there): the HLE has none of it. */
void ps2k_set_phase_hook(ps2k_phase_hook_fn fn) { (void)fn; }
void ps2k_set_parked_hook(ps2k_parked_hook_fn fn) { (void)fn; }
void ps2k_set_block_hook(ps2k_block_hook_fn fn) { (void)fn; }
int ps2k_native(void) { return 0; }
void ps2k_get_native_stats(ps2k_native_stats *out)
{
    if (out)
        memset(out, 0, sizeof *out);
}

/* ======================================================================
 * trace
 * ==================================================================== */

static void fnv(uint64_t *h, uint64_t v, int bytes)
{
    for (int i = 0; i < bytes; i++) {
        *h ^= (uint8_t)(v >> (8 * i));
        *h *= 0x100000001b3ull;
    }
}

void k_trace(int type, int32_t a, int32_t b)
{
    ps2k_trace_rec r;
    r.seq = K.trace_n++;
    r.time = K.now;
    r.type = type;
    r.a = a;
    r.b = b;
    fnv(&K.trace_hash, r.time, 8);
    fnv(&K.trace_hash, (uint32_t)type, 4);
    fnv(&K.trace_hash, (uint32_t)a, 4);
    fnv(&K.trace_hash, (uint32_t)b, 4);
    K.ring[r.seq % KTRACE_RING] = r;
    if (K.trace_hook)
        K.trace_hook(&r, K.trace_user);
}

uint64_t ps2k_trace_hash(void) { return K.trace_hash; }
uint64_t ps2k_trace_count(void) { return K.trace_n; }

void ps2k_set_trace_hook(ps2k_trace_fn fn, void *user)
{
    K.trace_hook = fn;
    K.trace_user = user;
}

static const char *trace_name(int t)
{
    switch (t) {
    case PS2K_TR_SWITCH: return "switch";
    case PS2K_TR_IDLE_JUMP: return "idle-jump";
    case PS2K_TR_INTC: return "intc";
    case PS2K_TR_DMAC: return "dmac";
    case PS2K_TR_ALARM: return "alarm";
    case PS2K_TR_THREAD: return "thread";
    case PS2K_TR_SEMA_SIGNAL: return "sema-signal";
    case PS2K_TR_SEMA_WAIT: return "sema-wait";
    case PS2K_TR_WAKEUP: return "wakeup";
    case PS2K_TR_PREEMPT: return "preempt";
    case PS2K_TR_RAISE: return "raise";
    case PS2K_TR_VIOLATION: return "violation";
    default: return "?";
    }
}

void ps2k_trace_dump(FILE *f, int last_n)
{
    uint64_t n = K.trace_n;
    uint64_t start = 0;
    if (last_n > KTRACE_RING)
        last_n = KTRACE_RING;
    if (last_n >= 0 && n > (uint64_t)last_n)
        start = n - (uint64_t)last_n;
    if (n > KTRACE_RING && start < n - KTRACE_RING)
        start = n - KTRACE_RING;
    for (uint64_t i = start; i < n; i++) {
        const ps2k_trace_rec *r = &K.ring[i % KTRACE_RING];
        fprintf(f, "%8llu t=%12llu %-11s %d %d\n", (unsigned long long)r->seq,
                (unsigned long long)r->time, trace_name(r->type), r->a, r->b);
    }
}

/* ======================================================================
 * violations
 * ==================================================================== */

int k_violation(const char *call, const char *why)
{
    K.violations++;
    k_trace(PS2K_TR_VIOLATION, 0, 0);
    if (K.violation) {
        K.violation(call, why);
    } else {
        fprintf(stderr, "ps2k: context violation in %s: %s\n", call, why);
        fflush(stderr);
        abort();
    }
    return PS2K_ERR;
}

void ps2k_set_violation_hook(ps2k_violation_fn fn) { K.violation = fn; }
uint32_t ps2k_violation_count(void) { return K.violations; }

/* ======================================================================
 * lifetime
 * ==================================================================== */

void ps2k_default_config(ps2k_config *cfg)
{
    memset(cfg, 0, sizeof *cfg);
    cfg->host_stack_size = 1u << 20;
    cfg->vblank_enable = 1;
    cfg->vblank_start_line = 240;
}

int ps2k_init(const ps2k_config *cfg)
{
    if (K.running)
        return -1;
    ps2k_violation_fn keep_violation = K.violation;
    for (int i = 0; i < PS2K_MAX_THREADS; i++)
        if (K.threads[i].fiber)
            ps2k_fiber_destroy(K.threads[i].fiber);
    memset(&K, 0, sizeof K);
    K.violation = keep_violation;
    if (cfg)
        K.cfg = *cfg;
    else
        ps2k_default_config(&K.cfg);
    K.cfg.native = 0; /* frame-driven mode is the native kernel table's (kdispatch.c) */
    if (K.cfg.host_stack_size < 64 * 1024)
        K.cfg.host_stack_size = 64 * 1024;
    K.trace_hash = 0xcbf29ce484222325ull;
    K.eie = 1;
    K.thread_eie = 1;
    K.next_handler_id = 1;
    /* VALIDATION.md 2c: sema ids start at 0 and the most recently freed id is
     * reused first (LIFO free list); created threads start at 2 (main = 1) and
     * advance next-fit */
    for (int i = 0; i < PS2K_MAX_SEMAS; i++)
        K.semas[i].free_next = i + 1 < PS2K_MAX_SEMAS ? i + 1 : -1;
    K.sema_free = 0;
    K.next_thread_id = 2;
    K.inited = 1;
    k_irq_reset();
    return 0;
}

void ps2k_shutdown(void)
{
    if (K.running)
        return;
    for (int i = 0; i < PS2K_MAX_THREADS; i++)
        if (K.threads[i].fiber)
            ps2k_fiber_destroy(K.threads[i].fiber);
    ps2k_violation_fn keep_violation = K.violation;
    memset(&K, 0, sizeof K);
    K.violation = keep_violation;
}

int ps2k_stop_code(void) { return K.stop_code; }
const char *ps2k_backend_name(void) { return ps2k_fiber_backend_name(); }

/* ======================================================================
 * ready queues
 * ==================================================================== */

static void rq_push_tail(kthread *t)
{
    int p = t->prio;
    t->qnext = NULL;
    t->qprev = K.rq_tail[p];
    if (K.rq_tail[p])
        K.rq_tail[p]->qnext = t;
    else
        K.rq_head[p] = t;
    K.rq_tail[p] = t;
}

static void rq_push_head(kthread *t)
{
    int p = t->prio;
    t->qprev = NULL;
    t->qnext = K.rq_head[p];
    if (K.rq_head[p])
        K.rq_head[p]->qprev = t;
    else
        K.rq_tail[p] = t;
    K.rq_head[p] = t;
}

static void rq_remove(kthread *t)
{
    int p = t->prio;
    if (t->qprev)
        t->qprev->qnext = t->qnext;
    else
        K.rq_head[p] = t->qnext;
    if (t->qnext)
        t->qnext->qprev = t->qprev;
    else
        K.rq_tail[p] = t->qprev;
    t->qnext = t->qprev = NULL;
}

kthread *k_ready_top(void)
{
    for (int p = 0; p <= PS2K_PRIO_MAX; p++)
        if (K.rq_head[p])
            return K.rq_head[p];
    return NULL;
}

static void set_status(kthread *t, int st)
{
    t->status = st;
    k_trace(PS2K_TR_THREAD, t->id, st);
}

/* A wait finished (sema signalled/deleted, wakeup, release). */
void k_make_ready(kthread *t)
{
    if (t->driven == 2) { /* parked: its WaitSema returned; the frame driver runs it */
        t->wait_type = PS2K_TSW_KWAIT;
        t->wait_id = 0;
        t->kwait = KW_DRIVEN;
        t->driven_woken = 1;
        k_trace(PS2K_TR_THREAD, t->id, PS2K_THS_READY);
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
 * switching
 * ==================================================================== */

/* EIE across a switch.  Retail (cfg.eie_per_thread = 0, VALIDATION.md 2e):
 * one global thread-context EIE that a switch neither saves per thread nor
 * restores; a DI before a blocking call carries over to the next thread.
 * Kernel/idle context still delivers pending interrupts (not measured). */
static void k_save_eie(kthread *t)
{
    if (K.cfg.eie_per_thread)
        t->eie = K.eie;
    else
        K.thread_eie = K.eie;
}

static int k_switch_in_eie(const kthread *t)
{
    return K.cfg.eie_per_thread ? t->eie : K.thread_eie;
}

/* From a thread fiber back to the scheduler.  Returns when the scheduler
 * switches this thread in again. */
static void switch_to_sched(void)
{
    kthread *t = K.cur;
    k_save_eie(t);
    if (t->svc_step) { /* service thread: no fiber; unwind to the scheduler */
        if (K.svc_in_step) {
            if (t->status != PS2K_THS_RUN) {
                fprintf(stderr, "ps2k: service step of thread %d blocked (status %d, wait %d/%d); "
                                "it must run to completion (docs/NATIVE-THREADS.md)\n",
                        t->id, t->status, t->wait_type, t->wait_id);
                abort();
            }
            k_svc_deferred++; /* preempted mid-step: the step finishes first */
        }
        K.svc_yield = 1;
        return;
    }
    ps2k_fiber_switch(t->fiber, K.sched);
    /* resumed: the scheduler has set K.cur = t and K.eie (k_switch_in_eie) */
}

static int block_current(void)
{
    switch_to_sched();
    return K.cur->wait_result;
}

void k_maybe_preempt(void)
{
    kthread *c = K.cur;
    if (!c || K.in_handler)
        return;
    if (K.stop_req) {
        if (c->status == PS2K_THS_RUN) {
            set_status(c, PS2K_THS_READY);
            rq_push_head(c);
        }
        switch_to_sched();
        return;
    }
    if (c->status != PS2K_THS_RUN) { /* a handler suspended it */
        K.yield_req = 0;
        switch_to_sched();
        return;
    }
    kthread *h = k_ready_top();
    if (K.yield_req) {
        K.yield_req = 0;
        if (h && h->prio <= c->prio) {
            set_status(c, PS2K_THS_READY);
            rq_push_tail(c);
            k_trace(PS2K_TR_PREEMPT, c->id, h->id);
            switch_to_sched();
            return;
        }
    }
    if (h && h->prio < c->prio) {
        set_status(c, PS2K_THS_READY);
        rq_push_head(c);
        k_trace(PS2K_TR_PREEMPT, c->id, h->id);
        switch_to_sched();
    }
}

/* Every kernel call starts here.  isr: 1 for the "i" variants.  Thread
 * context calls are a defined delivery point. */
int k_enter(const char *call, int isr)
{
    if (isr) {
        if (!K.in_handler)
            return k_violation(call, "i-variant called outside interrupt handler context");
        return 0;
    }
    if (K.in_handler)
        return k_violation(call, "thread-context call made from an interrupt handler");
    if (K.cur) {
        if (K.cfg.kcall_cycles)
            K.now += K.cfg.kcall_cycles;
        k_process_due();
        if (K.eie)
            k_deliver();
        k_maybe_preempt();
    }
    return 0;
}

/* blocking calls need a thread */
static int need_thread(const char *call)
{
    if (!K.cur)
        return k_violation(call, "blocking call outside a guest thread");
    return 0;
}

static kthread *thread_get(int id)
{
    if (id <= 0 || id >= PS2K_MAX_THREADS)
        return NULL;
    kthread *t = &K.threads[id];
    return t->used ? t : NULL;
}

/* id 0 means "the current thread" (TH_SELF) */
static kthread *thread_get_self_ok(int id)
{
    if (id == PS2K_TH_SELF)
        return K.cur;
    return thread_get(id);
}

static void thread_trampoline(void *p)
{
    kthread *t = (kthread *)p;
    t->entry(t->arg);
    ps2k_exit_thread();
}

static void reap(void)
{
    for (int i = 1; i < PS2K_MAX_THREADS; i++) {
        kthread *t = &K.threads[i];
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

/* ======================================================================
 * service threads (no fiber): the loop
 *     for (;;) { s = wait(arg); if (s < 0) break; WaitSema(s); step(arg); }
 * run on the scheduler's stack.  Every kernel-visible effect (k_enter
 * delivery points, preemption, the sema logic, trace records, EIE) is the one
 * ps2k_wait_sema / exit_common would produce; svc_pc remembers where to
 * resume after a switch-out.
 * ==================================================================== */

static ksema *sema_get(int id);

static void svc_exit(kthread *t)
{
    /* exit_common after its k_enter: the thread returns from its entry */
    set_status(t, PS2K_THS_DORMANT);
    t->svc_pc = SVC_TOP;
    if (t->id == K.main_id && !K.stop_req) {
        K.stop_req = 1;
        K.stop_reason = PS2K_RUN_MAIN_EXIT;
    }
    k_save_eie(t);
}

static void svc_run(kthread *t)
{
    K.svc_yield = 0;
    for (;;) {
        if (t->svc_pc == SVC_TOP) {
            int sid = t->svc_wait(t->arg);
            t->svc_pc = sid < 0 ? SVC_EXIT_ENTERED : SVC_WAIT_ENTERED;
            t->svc_sid = sid; /* kept across a preemption in k_enter */
            if (k_enter(sid < 0 ? "ExitThread" : "WaitSema", 0) == 0 && K.svc_yield)
                return; /* preempted inside k_enter: resume after it */
        }
        if (t->svc_pc == SVC_EXIT_ENTERED) {
            svc_exit(t);
            return;
        }
        if (t->svc_pc == SVC_WAIT_ENTERED) {
            int id = t->svc_sid;
            ksema *s = sema_get(id);
            if (s && s->count <= 0) {
                t->wnext = NULL;
                if (s->wtail)
                    s->wtail->wnext = t;
                else
                    s->whead = t;
                s->wtail = t;
                s->nwait++;
                t->wait_type = PS2K_TSW_SEMA;
                t->wait_id = id;
                t->wait_result = PS2K_ERR;
                k_trace(PS2K_TR_SEMA_WAIT, id, t->id);
                set_status(t, PS2K_THS_WAIT);
                t->svc_pc = SVC_WOKEN;
                k_save_eie(t);
                return;
            }
            if (s)
                s->count--;
            t->svc_pc = SVC_WOKEN; /* WaitSema returned (an invalid id returns -1 at once) */
        }
        /* SVC_WOKEN: WaitSema has returned; run the body */
        t->svc_pc = SVC_TOP;
        K.svc_in_step = 1;
        k_svc_steps++;
        t->svc_step(t->arg);
        K.svc_in_step = 0;
        if (K.svc_yield)
            return; /* a deferred preemption (status READY, queued) */
    }
}

int ps2k_thread_set_service(int id, ps2k_svc_wait_fn wait, ps2k_entry_fn step)
{
    kthread *t = (id > 0 && id < PS2K_MAX_THREADS && K.threads[id].used) ? &K.threads[id] : NULL;
    if (!t || !wait || !step || t->status != PS2K_THS_DORMANT || t->fiber)
        return PS2K_ERR;
    t->svc_wait = wait;
    t->svc_step = step;
    t->svc_pc = SVC_TOP;
    return 0;
}

uint32_t ps2k_svc_deferred_count(void) { return k_svc_deferred; }
uint32_t ps2k_svc_step_count(void) { return k_svc_steps; }

/* ======================================================================
 * scheduler loop
 * ==================================================================== */

void ps2k_request_stop(void)
{
    if (!K.stop_req) {
        K.stop_req = 1;
        K.stop_reason = PS2K_RUN_STOPPED;
    }
    k_maybe_preempt();
}

int ps2k_running(void) { return K.running; }

int ps2k_start(ps2k_entry_fn main_entry, void *arg, int main_priority)
{
    if (!K.inited || K.running)
        return PS2K_RUN_ERROR;
    K.sched = ps2k_fiber_adopt_host();
    if (!K.sched)
        return PS2K_RUN_ERROR;
    K.running = 1;
    K.cur = NULL;
    K.eie = 1;
    K.thread_eie = 1;
    K.want_main_id = 1; /* retail: the main thread is id 1 (VALIDATION.md 2c) */
    int id = ps2k_create_thread(main_entry, NULL, 0, NULL, main_priority, 0, 0);
    K.want_main_id = 0;
    if (id < 0 || ps2k_start_thread(id, arg) < 0) {
        ps2k_finish(PS2K_RUN_ERROR);
        return PS2K_RUN_ERROR;
    }
    K.main_id = id;
    K.idle_since = K.now;
    return 0;
}

int ps2k_step(uint64_t until_vblank)
{
    if (!K.running || K.cur || K.in_handler)
        return PS2K_RUN_ERROR;
    int rc = PS2K_RUN_ERROR;
    for (;;) {
        reap();
        if (K.stop_req) {
            rc = K.stop_reason;
            break;
        }
        /* kernel context: interrupts enabled */
        k_process_due();
        k_deliver();
        if (K.stop_req)
            continue;
        if (until_vblank && K.vblank_count >= until_vblank) {
            rc = PS2K_RUN_YIELD;
            break;
        }
        k_poll_wake(0);
        kthread *t = k_ready_top();
        if (t) {
            rq_remove(t);
            set_status(t, PS2K_THS_RUN);
            if (!t->fiber && !t->svc_step) {
                t->fiber = ps2k_fiber_create(K.cfg.host_stack_size, thread_trampoline, t);
                if (!t->fiber) {
                    rc = PS2K_RUN_ERROR;
                    break;
                }
            }
            K.cur = t;
            K.eie = k_switch_in_eie(t);
            K.activity++;
            k_trace(PS2K_TR_SWITCH, t->id, t->prio);
            K_TAP(PS2K_TAP_SWITCH, t->id, t->prio, (const void *)t->entry);
            if (t->svc_step)
                svc_run(t);
            else
                ps2k_fiber_switch(K.sched, t->fiber);
            K.cur = NULL;
            K.eie = 1;
            K.idle_since = K.now;
            continue;
        }
        /* idle: jump the clock to the next event (kernel event or device) */
        uint64_t next;
        if (!k_next_due(&next) && K.kwait_n > 0) {
            k_poll_wake(1); /* nothing else can happen: due poll waiters wake as timed waits */
            if (k_ready_top())
                continue;
        }
        if (!k_next_due(&next)) {
            rc = PS2K_RUN_DEADLOCK;
            break;
        }
        if (K.cfg.stop_at_cycles && next > K.cfg.stop_at_cycles) {
            if (K.cfg.stop_at_cycles > K.now)
                K.now = K.cfg.stop_at_cycles;
            rc = PS2K_RUN_TIME_LIMIT;
            break;
        }
        if (K.cfg.stall_cycles && next - K.idle_since > K.cfg.stall_cycles) {
            rc = PS2K_RUN_STALL;
            break;
        }
        if (next > K.now) {
            if (K.pacing)
                K.pacing(K.now, next, K.pacing_user);
            K.now = next;
            k_trace(PS2K_TR_IDLE_JUMP, (int32_t)(uint32_t)next, (int32_t)(uint32_t)(next >> 32));
        }
    }
    return rc;
}

/* driven steps run in step context only in the native kernel table */
void *ps2k_step_enter(int id)
{
    (void)id;
    return NULL;
}
void ps2k_step_leave(void *token) { (void)token; }
int ps2k_in_step(void) { return 0; }
int ps2k_ready_at(int priority) { return priority >= 0 && priority <= PS2K_PRIO_MAX && K.rq_head[priority] != NULL; }

void ps2k_finish(int code)
{
    if (!K.running)
        return;
    for (int i = 1; i < PS2K_MAX_THREADS; i++) {
        if (K.threads[i].fiber) {
            ps2k_fiber_destroy(K.threads[i].fiber);
            K.threads[i].fiber = NULL;
        }
    }
    ps2k_fiber_release_host(K.sched);
    K.sched = NULL;
    K.running = 0;
    K.cur = NULL;
    K.stop_code = code;
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
 * threads
 * ==================================================================== */

int ps2k_create_thread(ps2k_entry_fn entry, void *stack, int32_t stack_size, void *gp,
                       int32_t priority, uint32_t attr, uint32_t option)
{
    if (k_enter("CreateThread", 0))
        return PS2K_ERR;
    if (!entry || priority < 0 || priority > PS2K_PRIO_MAX)
        return PS2K_ERR;
    /* VALIDATION.md 2c: next-fit over 1..PS2K_MAX_THREADS-1 from the cursor
     * (2 at init; main takes 1), skipping ids in use, wrapping.  Freed ids are
     * not reused until the cursor comes round (the retail wrap point was not
     * reached in the measurements; wrapping here is an assumption). */
    int i = -1;
    if (K.want_main_id && !K.threads[K.want_main_id].used) {
        i = K.want_main_id;
    } else {
        for (int n = 0; n < PS2K_MAX_THREADS - 1; n++) {
            int c = 1 + (K.next_thread_id - 1 + n) % (PS2K_MAX_THREADS - 1);
            if (!K.threads[c].used) {
                i = c;
                break;
            }
        }
        if (i < 0)
            return PS2K_ERR;
        K.next_thread_id = 1 + i % (PS2K_MAX_THREADS - 1);
    }
    {
        kthread *t = &K.threads[i];
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
        t->eie = 1; /* used only with cfg.eie_per_thread */
        set_status(t, PS2K_THS_DORMANT);
        return i;
    }
    return PS2K_ERR;
}

int ps2k_delete_thread(int id)
{
    if (k_enter("DeleteThread", 0))
        return PS2K_ERR;
    kthread *t = thread_get(id);
    if (!t || t == K.cur || t->status != PS2K_THS_DORMANT)
        return PS2K_ERR;
    if (t->fiber)
        ps2k_fiber_destroy(t->fiber);
    memset(t, 0, sizeof *t);
    return id;
}

int ps2k_start_thread(int id, void *arg)
{
    if (k_enter("StartThread", 0))
        return PS2K_ERR;
    kthread *t = thread_get(id);
    if (!t || t->status != PS2K_THS_DORMANT || t->fiber_dead)
        return PS2K_ERR;
    if (t->fiber) { /* left over from a previous run of this thread */
        ps2k_fiber_destroy(t->fiber);
        t->fiber = NULL;
    }
    t->arg = arg;
    t->prio = t->init_prio;
    t->wakeup_count = 0;
    t->svc_pc = SVC_TOP;
    t->eie = 1;
    t->wait_type = PS2K_TSW_NONE;
    t->wait_id = 0;
    if (k_start_hook && !t->svc_step)
        k_start_hook(id, t->entry, arg);
    if (t->driven) { /* parked: the frame driver runs its body (no fiber, never readied) */
        t->driven = 2;
        t->driven_woken = 0;
        t->kwait = KW_DRIVEN;
        t->wait_type = PS2K_TSW_KWAIT;
        set_status(t, PS2K_THS_WAIT);
        return id;
    }
    set_status(t, PS2K_THS_READY);
    rq_push_tail(t);
    k_maybe_preempt();
    return id;
}

static void exit_common(const char *call, int del)
{
    if (k_enter(call, 0) || need_thread(call)) {
        /* cannot exit a non-thread; nothing sensible to return to */
        return;
    }
    kthread *t = K.cur;
    set_status(t, PS2K_THS_DORMANT);
    t->fiber_dead = 1;
    t->delete_pending = del;
    if (t->id == K.main_id && !K.stop_req) {
        K.stop_req = 1;
        K.stop_reason = PS2K_RUN_MAIN_EXIT;
    }
    k_save_eie(t);
    ps2k_fiber_switch(t->fiber, K.sched);
    /* never resumed: the scheduler destroys this fiber */
    abort();
}

void ps2k_exit_thread(void) { exit_common("ExitThread", 0); }
void ps2k_exit_delete_thread(void) { exit_common("ExitDeleteThread", 1); }

/* ======================================================================
 * kernel-private waits (ps2k_wait_vblank / ps2k_wait_until)
 * ==================================================================== */

static void kwait_remove(kthread *t)
{
    int j = 0;
    for (int i = 0; i < K.kwait_n; i++)
        if (K.kwait_fifo[i] != t->id)
            K.kwait_fifo[j++] = K.kwait_fifo[i];
    K.kwait_n = j;
    if (t->kwait == KW_TIME || t->kwait == KW_POLL)
        k_ev_remove(EV_KWAKE, t->id);
    if (t->kwait == KW_DRIVEN)
        t->driven = 0; /* terminated / released: no longer the driver's */
    t->kwait = KW_NONE;
    t->poll_due = 0;
}

void k_kwait_wake(int tid, int kind)
{
    for (int i = 0; i < K.kwait_n;) {
        kthread *t = &K.threads[K.kwait_fifo[i]];
        int due = t->used && t->kwait == kind &&
                  (kind == KW_TIME ? t->id == tid : K.vblank_count >= t->kwait_arg);
        if (!due) {
            i++;
            continue;
        }
        memmove(&K.kwait_fifo[i], &K.kwait_fifo[i + 1], (size_t)(K.kwait_n - i - 1) * sizeof(int));
        K.kwait_n--;
        t->kwait = KW_NONE;
        t->wait_result = 0;
        k_make_ready(t);
    }
}

void k_poll_wake(int idle)
{
    for (int i = 0; i < K.kwait_n;) {
        kthread *t = &K.threads[K.kwait_fifo[i]];
        if (!(t->used && t->kwait == KW_POLL && t->poll_due && (idle || K.activity != t->poll_seen))) {
            i++;
            continue;
        }
        memmove(&K.kwait_fifo[i], &K.kwait_fifo[i + 1], (size_t)(K.kwait_n - i - 1) * sizeof(int));
        K.kwait_n--;
        t->kwait = KW_NONE;
        t->poll_due = 0;
        t->wait_result = 0;
        k_make_ready(t);
    }
}

static int kwait_block2(const char *call, int kind, uint64_t arg, int entered)
{
    if (!entered && k_enter(call, 0))
        return PS2K_ERR;
    if (!K.cur)
        return k_violation(call, "blocking call outside a guest thread");
    if (kind == KW_TIME && arg <= K.now)
        return 0;
    if (kind == KW_VBLANK && K.vblank_count >= arg)
        return 0;
    kthread *c = K.cur;
    K_TAP(PS2K_TAP_KWAIT, kind, (int32_t)arg, NULL);
    if (K.kwait_n >= PS2K_MAX_THREADS)
        return PS2K_ERR;
    if ((kind == KW_TIME || kind == KW_POLL) && k_ev_add(arg, EV_KWAKE, c->id) < 0)
        return PS2K_ERR;
    K.kwait_fifo[K.kwait_n++] = c->id;
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
    if (K.in_handler || !K.cur)
        return PS2K_ERR;
    if (k_enter("WaitPoll", 0))
        return PS2K_ERR;
    kthread *c = K.cur;
    int kind = K.activity != c->poll_seen ? KW_TIME : KW_POLL;
    int r;
    if (kind == KW_POLL && time <= K.now) { /* due already: wait for the next activity only */
        c->poll_due = 1;
        if (K.kwait_n >= PS2K_MAX_THREADS)
            return PS2K_ERR;
        K_TAP(PS2K_TAP_KWAIT, 3, (int32_t)time, NULL);
        K.kwait_fifo[K.kwait_n++] = c->id;
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
    K.cur->poll_seen = K.activity;
    return r;
}

uint64_t ps2k_activity(void) { return K.activity; }

int ps2k_thread_set_driven(int id)
{
    kthread *t = (id > 0 && id < PS2K_MAX_THREADS && K.threads[id].used) ? &K.threads[id] : NULL;
    if (!t || t->status != PS2K_THS_DORMANT || t->fiber || t->svc_step || id == K.main_id)
        return PS2K_ERR;
    t->driven = 1;
    return 0;
}

int ps2k_thread_driven_state(int id)
{
    kthread *t = (id > 0 && id < PS2K_MAX_THREADS && K.threads[id].used) ? &K.threads[id] : NULL;
    if (!t || !t->driven)
        return 0;
    return t->driven == 2 && (t->status & PS2K_THS_WAIT) ? 2 : 1;
}

int ps2k_driven_wait(int id, int sema)
{
    kthread *t = (id > 0 && id < PS2K_MAX_THREADS && K.threads[id].used) ? &K.threads[id] : NULL;
    if (!t || t->driven != 2 || !(t->status & PS2K_THS_WAIT) || t->wait_type == PS2K_TSW_SEMA)
        return PS2K_ERR;
    ksema *s = sema_get(sema);
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
    k_trace(PS2K_TR_SEMA_WAIT, sema, t->id);
    return 0;
}

int ps2k_driven_take(int id)
{
    kthread *t = (id > 0 && id < PS2K_MAX_THREADS && K.threads[id].used) ? &K.threads[id] : NULL;
    if (!t || t->driven != 2 || !t->driven_woken)
        return 0;
    t->driven_woken = 0;
    return 1;
}

int ps2k_driven_woken(int id)
{
    kthread *t = (id > 0 && id < PS2K_MAX_THREADS && K.threads[id].used) ? &K.threads[id] : NULL;
    return t && t->driven == 2 && t->driven_woken;
}

static void unlink_thread(kthread *t);

int ps2k_driven_exit(int id, int del)
{
    kthread *t = (id > 0 && id < PS2K_MAX_THREADS && K.threads[id].used) ? &K.threads[id] : NULL;
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

int ps2k_wait_vblank(void)
{
    if (K.in_handler || !K.cur || !K.cfg.vblank_enable)
        return PS2K_ERR;
    return kwait_block("WaitVblank", KW_VBLANK, K.vblank_count + 1);
}

int ps2k_wait_until(uint64_t time)
{
    if (K.in_handler || !K.cur)
        return PS2K_ERR;
    return kwait_block("WaitUntil", KW_TIME, time);
}

/* remove t from whatever it is waiting on / queued in */
static void unlink_thread(kthread *t)
{
    if (t->status == PS2K_THS_READY) {
        rq_remove(t);
    } else if ((t->status & PS2K_THS_WAIT) && t->wait_type == PS2K_TSW_SEMA) {
        ksema *s = &K.semas[t->wait_id];
        kthread **pp = &s->whead;
        kthread *prev = NULL;
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

int ps2k_terminate_thread(int id, int isr)
{
    if (k_enter(isr ? "iTerminateThread" : "TerminateThread", isr))
        return PS2K_ERR;
    kthread *t = thread_get(id);
    if (!t || t == K.cur || t->status == PS2K_THS_DORMANT)
        return PS2K_ERR;
    unlink_thread(t);
    t->driven = 0;
    t->driven_woken = 0;
    t->wait_type = PS2K_TSW_NONE;
    t->wait_id = 0;
    set_status(t, PS2K_THS_DORMANT);
    t->svc_pc = SVC_TOP;
    if (t->fiber) {
        ps2k_fiber_destroy(t->fiber); /* not running: safe */
        t->fiber = NULL;
    }
    if (t->id == K.main_id && !K.stop_req) {
        K.stop_req = 1;
        K.stop_reason = PS2K_RUN_MAIN_EXIT;
    }
    return id;
}

int ps2k_change_thread_priority(int id, int priority, int isr)
{
    if (k_enter(isr ? "iChangeThreadPriority" : "ChangeThreadPriority", isr))
        return PS2K_ERR;
    kthread *t = thread_get_self_ok(id);
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
    if (t == K.cur && t->status == PS2K_THS_RUN) {
        /* VALIDATION.md 2d: the running thread goes to the TAIL of its (new)
         * priority's queue, so a change to its own unchanged priority yields
         * to a ready thread of equal priority. */
        if (isr) {
            K.yield_req = 1; /* applied when the handler returns */
        } else {
            kthread *h = k_ready_top();
            if (h && h->prio <= t->prio) {
                set_status(t, PS2K_THS_READY);
                rq_push_tail(t);
                k_trace(PS2K_TR_PREEMPT, t->id, h->id);
                switch_to_sched();
            }
        }
        return old;
    }
    if (!isr)
        k_maybe_preempt();
    return old;
}

int ps2k_rotate_thread_ready_queue(int priority, int isr)
{
    if (k_enter(isr ? "iRotateThreadReadyQueue" : "RotateThreadReadyQueue", isr))
        return PS2K_ERR;
    if (priority < 0 || priority > PS2K_PRIO_MAX)
        return PS2K_ERR;
    kthread *c = K.cur;
    if (c && c->status == PS2K_THS_RUN && c->prio == priority) {
        /* the running thread is the head of its queue: it yields to the next
         * ready thread of the same priority */
        if (isr) {
            K.yield_req = 1;
        } else if (K.rq_head[priority]) {
            set_status(c, PS2K_THS_READY);
            rq_push_tail(c);
            switch_to_sched();
        }
        return priority;
    }
    kthread *h = K.rq_head[priority];
    if (h && h != K.rq_tail[priority]) {
        rq_remove(h);
        rq_push_tail(h);
    }
    return priority;
}

int ps2k_release_wait_thread(int id, int isr)
{
    if (k_enter(isr ? "iReleaseWaitThread" : "ReleaseWaitThread", isr))
        return PS2K_ERR;
    kthread *t = thread_get(id);
    if (!t || !(t->status & PS2K_THS_WAIT) || t->driven == 2)
        return PS2K_ERR;
    unlink_thread(t);
    t->wait_result = PS2K_ERR;
    k_make_ready(t);
    if (!isr)
        k_maybe_preempt();
    return id;
}

int ps2k_get_thread_id(void)
{
    if (K.cur)
        return K.cur->id;
    return 0;
}

int ps2k_refer_thread_status(int id, ps2k_thread_info *out, int isr)
{
    if (k_enter(isr ? "iReferThreadStatus" : "ReferThreadStatus", isr))
        return PS2K_ERR;
    kthread *t = thread_get_self_ok(id);
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
    if (k_enter("SleepThread", 0) || need_thread("SleepThread"))
        return PS2K_ERR;
    kthread *c = K.cur;
    if (c->wakeup_count > 0) {
        c->wakeup_count--;
        k_trace(PS2K_TR_WAKEUP, c->id, c->wakeup_count);
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
    if (k_enter(isr ? "iWakeupThread" : "WakeupThread", isr))
        return PS2K_ERR;
    kthread *t = thread_get(id);
    if (!t || t->status == PS2K_THS_DORMANT || (!isr && t == K.cur))
        return PS2K_ERR;
    if ((t->status & PS2K_THS_WAIT) && t->wait_type == PS2K_TSW_SLEEP) {
        t->wait_result = t->id;
        k_make_ready(t);
        k_trace(PS2K_TR_WAKEUP, t->id, -1);
    } else {
        t->wakeup_count++;
        k_trace(PS2K_TR_WAKEUP, t->id, t->wakeup_count);
    }
    if (!isr)
        k_maybe_preempt();
    return id;
}

int ps2k_cancel_wakeup_thread(int id, int isr)
{
    if (k_enter(isr ? "iCancelWakeupThread" : "CancelWakeupThread", isr))
        return PS2K_ERR;
    kthread *t = thread_get_self_ok(id);
    if (!t)
        return PS2K_ERR;
    int n = t->wakeup_count;
    t->wakeup_count = 0;
    return n;
}

int ps2k_suspend_thread(int id, int isr)
{
    if (k_enter(isr ? "iSuspendThread" : "SuspendThread", isr))
        return PS2K_ERR;
    kthread *t = thread_get(id);
    if (!t || (!isr && t == K.cur))
        return PS2K_ERR;
    switch (t->status) {
    case PS2K_THS_READY:
        rq_remove(t);
        set_status(t, PS2K_THS_SUSPEND);
        break;
    case PS2K_THS_RUN: /* only reachable from a handler: stops at handler exit */
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
    if (k_enter(isr ? "iResumeThread" : "ResumeThread", isr))
        return PS2K_ERR;
    kthread *t = thread_get(id);
    if (!t)
        return PS2K_ERR;
    if (t->status == PS2K_THS_SUSPEND) {
        if (t == K.cur) { /* suspended by a handler, not yet switched out */
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
        k_maybe_preempt();
    return id;
}

/* ======================================================================
 * semaphores
 * ==================================================================== */

static ksema *sema_get(int id)
{
    if (id < 0 || id >= PS2K_MAX_SEMAS)
        return NULL;
    ksema *s = &K.semas[id];
    return s->used ? s : NULL;
}

int ps2k_peek_sema(int id, int32_t *count, int32_t *nwait)
{
    ksema *s = sema_get(id);
    if (!s)
        return -1;
    if (count)
        *count = s->count;
    if (nwait)
        *nwait = s->nwait;
    return 0;
}

int ps2k_peek_priority(void) { return K.cur ? K.cur->prio : -1; }

int ps2k_create_sema(int32_t init_count, int32_t max_count, uint32_t attr, uint32_t option)
{
    if (k_enter("CreateSema", 0))
        return PS2K_ERR;
    if (init_count < 0)
        return PS2K_ERR;
    /* VALIDATION.md 2c: ids from 0, last freed = first reused */
    {
        int i = K.sema_free;
        if (i < 0)
            return PS2K_ERR;
        ksema *s = &K.semas[i];
        K.sema_free = s->free_next;
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
    return PS2K_ERR;
}

int ps2k_delete_sema(int id, int isr)
{
    if (k_enter(isr ? "iDeleteSema" : "DeleteSema", isr))
        return PS2K_ERR;
    ksema *s = sema_get(id);
    if (!s)
        return PS2K_ERR;
    kthread *w = s->whead;
    s->whead = s->wtail = NULL;
    s->nwait = 0;
    s->used = 0;
    s->free_next = K.sema_free; /* LIFO: this id is the next one created */
    K.sema_free = id;
    while (w) {
        kthread *n = w->wnext;
        w->wnext = NULL;
        w->wait_result = PS2K_ERR;
        k_make_ready(w);
        w = n;
    }
    if (!isr)
        k_maybe_preempt();
    return id;
}

int ps2k_signal_sema(int id, int isr)
{
    if (k_enter(isr ? "iSignalSema" : "SignalSema", isr))
        return PS2K_ERR;
    ksema *s = sema_get(id);
    if (!s)
        return PS2K_ERR;
    kthread *w = s->whead;
    if (w) {
        s->whead = w->wnext;
        if (!s->whead)
            s->wtail = NULL;
        w->wnext = NULL;
        s->nwait--;
        w->wait_result = id;
        k_trace(PS2K_TR_SEMA_SIGNAL, id, w->id);
        k_make_ready(w);
        if (w->driven == 2) { /* a parked thread woke: the frame driver may run it here */
            if (!isr && k_signal_hook && K.cur)
                k_signal_hook(id);
            return id;
        }
        if (!isr)
            k_maybe_preempt();
        return id;
    }
    /* VALIDATION.md 2b: the retail kernel does not cap; SignalSema at max
     * succeeds and the count exceeds max_count. */
    s->count++;
    k_trace(PS2K_TR_SEMA_SIGNAL, id, 0);
    return id;
}

int ps2k_wait_sema(int id)
{
    if (k_enter("WaitSema", 0) || need_thread("WaitSema"))
        return PS2K_ERR;
    ksema *s = sema_get(id);
    if (!s)
        return PS2K_ERR;
    if (s->count > 0) {
        s->count--;
        return id;
    }
    kthread *c = K.cur;
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
    k_trace(PS2K_TR_SEMA_WAIT, id, c->id);
    set_status(c, PS2K_THS_WAIT);
    return block_current();
}

int ps2k_poll_sema(int id, int isr)
{
    if (k_enter(isr ? "iPollSema" : "PollSema", isr))
        return PS2K_ERR;
    ksema *s = sema_get(id);
    if (!s || s->count <= 0)
        return PS2K_ERR;
    s->count--;
    return id;
}

int ps2k_refer_sema_status(int id, ps2k_sema_info *out, int isr)
{
    if (k_enter(isr ? "iReferSemaStatus" : "ReferSemaStatus", isr))
        return PS2K_ERR;
    ksema *s = sema_get(id);
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
 * DelayThread (libkernl: CreateSema + timer alarm + WaitSema + DeleteSema)
 * ==================================================================== */

uint64_t ps2k_usec_to_cycles(uint32_t usec) { return (uint64_t)usec * 147456u / 1000u; }

static void delay_alarm_cb(int32_t id, uint16_t time, void *arg)
{
    (void)id;
    (void)time;
    ps2k_signal_sema((int)(intptr_t)arg, 1);
}

int ps2k_delay_thread(uint32_t usec)
{
    /* libkernl checks EIE first; inside a handler EIE is normally 0 */
    if ((K.cur || K.in_handler) && !K.eie)
        return PS2K_DELAY_E_DISABLED;
    if (K.in_handler)
        return k_violation("DelayThread", "thread-context call made from an interrupt handler");
    if (need_thread("DelayThread"))
        return PS2K_ERR;
    int s = ps2k_create_sema(0, 1, 0, 0);
    if (s < 0)
        return PS2K_DELAY_E_NOSEMA;
    int a = ps2k_set_cycle_alarm(ps2k_usec_to_cycles(usec), delay_alarm_cb, (void *)(intptr_t)s, 0);
    if (a < 0) {
        ps2k_delete_sema(s, 0);
        return a;
    }
    ps2k_wait_sema(s);
    ps2k_delete_sema(s, 0);
    return 0;
}

/* ======================================================================
 * debug
 * ==================================================================== */

void ps2k_debug_force_preempt(void)
{
    kthread *c = K.cur;
    if (!c || K.in_handler)
        return;
    k_process_due();
    k_deliver(); /* ignores EIE on purpose */
    kthread *h = k_ready_top();
    if (h && h->prio < c->prio) {
        set_status(c, PS2K_THS_READY);
        rq_push_head(c);
        k_trace(PS2K_TR_PREEMPT, c->id, h->id);
        switch_to_sched();
    }
}
