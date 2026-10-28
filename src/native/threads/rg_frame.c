/* SPDX-License-Identifier: CC0-1.0
 * The native frame driver (docs/NATIVE-THREADS.md "Frame driver", "Slice 5").
 *
 * Every wait of a game flow (WaitVsyncCount, DelayThread, the loading-screen
 * condition waits, spin hints, sceGsSyncV, ThreadYield) is a driver point.  At
 * a driver point the driver runs the driven steps that are due: game threads
 * converted from "a loop that waits on a semaphore and runs a body" into plain
 * function calls (VBlank services: tick, stream slot, disk watch; workers: file
 * requests, sound streams, the two sound workers).  Their semaphores stay the
 * game's (a parked thread is a real waiter, ps2k_driven_wait) and their ISRs /
 * the game signal them as before; a woken step runs at the first driver point
 * after the signal, or at once on the signaller when the HLE switched to that
 * thread there (sync conversions, signal hook).
 *
 * Two hosts:
 * - RG_THREADS=frame (slices 2-3): the EE kernel HLE schedules the flows (main,
 *   the loading screen) and keeps the clock; driver points are on the flows.
 * - RG_THREADS=native (slice 5): the kernel runs frame-driven (ps2k cfg.native):
 *   no scheduler, the flows are the only coroutines, interrupts are explicit
 *   calls in the driver's pass, and the pass calls rg_frame_phase (the phase
 *   hook) after the handlers: VBlank services run there, every VBlank, in the
 *   HLE's order.  A step runs in step context (the kernel's current thread is
 *   the step's own thread), on the driver's stack or on the signalling flow;
 *   it cannot block (fatal), but a wait on a semaphore with no count first runs
 *   the other woken steps (block hook).
 *
 * State here is model state (saved in port save states); the registries of
 * convertible threads and flows are filled by constructors of the game-side
 * overrides, identically in every process of one exe. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ps2k.h"
#include "rg_threads.h"

void rg_threads_log_at_exit(void); /* rg_threads.c */

#define MAX_CONV   16
#define MAX_DRIVEN 16
#define MAX_FLOWREG 8
#define MAX_FLOWLOG 16

typedef struct dslot {
    int                   tid;
    const rg_thread_conv *conv;
    void                 *arg;
    uint64_t              steps;
    int                   sema; /* the WaitSema it is parked in (-2 = not run yet) */
    int                   running; /* its step is on the stack */
} dslot;

static const rg_thread_conv *g_conv[MAX_CONV];
static int                   g_nconv;
static uint64_t              g_conv_steps[MAX_CONV]; /* per registry entry, all its threads */
static int                   g_conv_refused[MAX_CONV];

/* flows (native mode): registered entries + every thread that started as one */
static struct {
    void       *entry;
    const char *name;
} g_flowreg[MAX_FLOWREG];
static int g_nflowreg;
static struct {
    int   tid;
    void *entry;
    int   known; /* registered with rg_threads_flow */
} g_flowlog[MAX_FLOWLOG];
static int g_nflowlog, g_flows_unknown;

static dslot    g_ds[MAX_DRIVEN];
static int      g_nds;
static int      g_busy;       /* running driven steps (no nesting) */
static int      g_driven;     /* threads parked so far */
static uint64_t g_points, g_driven_steps, g_delays, g_cond_waits, g_cond_wakes, g_sync_runs;
static uint64_t g_phases, g_block_runs, g_yields, g_yield_waits, g_eager_starts;
static ps2k_native_stats g_kstats; /* the kernel's counters, copied at each field end */
/* starvation record: VBlank intervals with no driver point (RG_THREADS_LOG) */
#define GAPS 8
static uint64_t g_last_vbl;
static uint64_t g_gap_fields, g_gap_n;
static uint64_t g_gap_at[GAPS], g_gap_len[GAPS];

static void note_point(void)
{
    uint64_t v = ps2k_vblank_count();
    if (g_last_vbl && v > g_last_vbl + 1) {
        uint64_t len = v - g_last_vbl - 1; /* VBlanks with no driver point */
        g_gap_fields += len;
        g_gap_n++;
        int m = 0;
        for (int i = 1; i < GAPS; i++)
            if (g_gap_len[i] < g_gap_len[m])
                m = i;
        if (len > g_gap_len[m]) {
            g_gap_len[m] = len;
            g_gap_at[m] = g_last_vbl + 1;
        }
    }
    g_last_vbl = v;
}

static void signal_hook(int sema);
static void phase_hook(void);
static void parked_hook(int id);
static void block_hook(int sema);

int rg_frame_native(void)
{
    int m = rg_threads_mode();
    return m == RG_THREADS_NATIVE || m == RG_THREADS_FRAME;
}

/* native: kernel frame-driven (step context, phase hook) */
static int kn(void) { return rg_threads_mode() == RG_THREADS_NATIVE && ps2k_native(); }

static int conv_index(const rg_thread_conv *c)
{
    for (int i = 0; i < g_nconv; i++)
        if (g_conv[i] == c)
            return i;
    return -1;
}

static void note_flow(int id, ps2k_entry_fn entry)
{
    int known = id == 1; /* main (ps2k_start): the game coroutine itself */
    const char *name = known ? "main" : "?";
    for (int i = 0; i < g_nflowreg; i++)
        if (g_flowreg[i].entry == (void *)entry) {
            known = 1;
            name = g_flowreg[i].name;
        }
    if (!known)
        g_flows_unknown++;
    if (g_nflowlog < MAX_FLOWLOG) {
        g_flowlog[g_nflowlog].tid = id;
        g_flowlog[g_nflowlog].entry = (void *)entry;
        g_flowlog[g_nflowlog].known = known;
        g_nflowlog++;
    }
    if (getenv("RG_THREADS_LOG"))
        fprintf(stderr, "rg_frame: thread %d (entry %p%s%s) runs as a game coroutine (flow)%s\n", id,
                (void *)entry, known ? ": " : "", known ? name : "",
                known ? "" : ": not converted (fallback)");
}

/* StartThread hook (kernel): park a convertible thread for the driver */
static void start_hook(int id, ps2k_entry_fn entry, void *arg)
{
    if (!rg_frame_native())
        return;
    const rg_thread_conv *c = NULL;
    for (int i = 0; i < g_nconv; i++)
        if (g_conv[i]->entry == (void *)entry)
            c = g_conv[i];
    if (!c) {
        if (kn())
            note_flow(id, entry);
        return;
    }
    {
        /* RG_FRAME_KEEP=name,name: these stay HLE threads (bisecting a conversion) */
        const char *keep = getenv("RG_FRAME_KEEP");
        if (keep && *keep && strstr(keep, c->name)) {
            g_conv_refused[conv_index(c)]++;
            if (kn())
                note_flow(id, entry);
            return;
        }
    }
    if (c->allowed && !c->allowed()) {
        g_conv_refused[conv_index(c)]++;
        if (getenv("RG_THREADS_LOG"))
            fprintf(stderr, "rg_frame: %s (thread %d) stays an HLE thread (its step could block here)\n",
                    c->name, id);
        if (kn())
            note_flow(id, entry);
        return;
    }
    if (ps2k_thread_set_driven(id) != 0) {
        fprintf(stderr, "rg_frame: %s (thread %d) cannot be driven\n", c->name, id);
        return;
    }
    /* a slot of a dead thread with the same id is replaced */
    int k;
    for (k = 0; k < g_nds; k++)
        if (g_ds[k].tid == id)
            break;
    if (k == g_nds) {
        if (g_nds >= MAX_DRIVEN) {
            fprintf(stderr, "rg_frame: too many driven threads\n");
            abort();
        }
        g_nds++;
    }
    g_ds[k].tid = id;
    g_ds[k].conv = c;
    g_ds[k].arg = arg;
    g_ds[k].steps = 0;
    g_ds[k].sema = -2;
    g_ds[k].running = 0;
    /* keep (order, tid) order: the HLE ran simultaneously woken threads by priority
     * (inside a driver point the slot stays appended; compact() sorts it) */
    while (!g_busy && k > 0 && (g_ds[k - 1].conv->order > c->order ||
                     (g_ds[k - 1].conv->order == c->order && g_ds[k - 1].tid > id))) {
        dslot t = g_ds[k - 1];
        g_ds[k - 1] = g_ds[k];
        g_ds[k] = t;
        k--;
    }
    g_driven++;
    if (getenv("RG_THREADS_LOG"))
        fprintf(stderr, "rg_frame: %s (thread %d) is driven by the frame driver\n", c->name, id);
}

static void register_hooks(void)
{
    ps2k_set_start_hook(start_hook);
    ps2k_set_signal_hook(signal_hook);
    ps2k_set_phase_hook(phase_hook);
    ps2k_set_parked_hook(parked_hook);
    ps2k_set_block_hook(block_hook);
}

void rg_threads_convertible(const rg_thread_conv *c)
{
    if (!c || !c->entry || !c->wait || !c->step)
        return;
    if (conv_index(c) >= 0)
        return;
    if (g_nconv >= MAX_CONV) {
        fprintf(stderr, "rg_frame: too many convertible threads\n");
        abort();
    }
    g_conv[g_nconv++] = c;
    register_hooks();
}

void rg_threads_flow(void *entry, const char *name)
{
    if (!entry || g_nflowreg >= MAX_FLOWREG)
        return;
    for (int i = 0; i < g_nflowreg; i++)
        if (g_flowreg[i].entry == entry)
            return;
    g_flowreg[g_nflowreg].entry = entry;
    g_flowreg[g_nflowreg].name = name ? name : "?";
    g_nflowreg++;
    register_hooks();
}

/* native: run f(d) as the driven thread itself (step context) */
static void *enter_ctx(dslot *d) { return kn() && d->tid > 0 ? ps2k_step_enter(d->tid) : NULL; }

/* A parked thread is modelled as blocked in the WaitSema of its loop: `sema` is the
 * semaphore its loop condition gave when it last passed the top of the loop (-2: it has
 * not run yet; the HLE ran it first when it was scheduled after StartThread;
 * RG_CONV_READY: runnable without waiting).  While that semaphore has a count: one step,
 * then the condition again (< 0: the loop ends, the body's own exit). */
static int slot_top(dslot *d)
{
    if (d->sema == -2 && d->conv->prologue)
        d->conv->prologue(d->arg); /* the entry's code before its loop: once */
    int s = d->conv->wait(d->arg);
    if (s < 0) {
        if (d->conv->exit_tail)
            d->conv->exit_tail(d->arg);
        ps2k_driven_exit(d->tid, d->conv->exit_delete);
        d->tid = 0;
        return 0;
    }
    d->sema = s;
    if (s != RG_CONV_READY)
        ps2k_driven_wait(d->tid, s); /* the loop's WaitSema: a real waiter, as on the HLE */
    return 1;
}

/* Steps nest only through sync conversions (a step signals a higher-priority driven
 * thread, which the HLE ran at once) and the block hook.  g_depth > 0: inside a step;
 * g_prio: the priority the innermost running step had as a thread (the "signaller's
 * priority" there). */
static int g_depth, g_prio;

static void run_slot(dslot *d)
{
    if (d->running)
        return;
    /* nothing due (the common case at a driver point): no step context, no activity */
    if (d->tid > 0 && d->sema != -2 && d->sema != RG_CONV_READY && ps2k_thread_driven_state(d->tid) == 2 &&
        !ps2k_driven_woken(d->tid))
        return;
    d->running = 1;
    int saved = g_prio;
    g_depth++;
    g_prio = d->conv->order;
    void *ctx = enter_ctx(d);
    if (!(d->tid > 0 && d->sema == -2 && ps2k_thread_driven_state(d->tid) == 2 && !slot_top(d))) {
        for (;;) {
            if (d->tid <= 0 || ps2k_thread_driven_state(d->tid) != 2) {
                d->tid = 0; /* terminated / deleted by the game */
                break;
            }
            if (d->sema != RG_CONV_READY && !ps2k_driven_take(d->tid))
                break; /* its WaitSema has not returned: nothing due */
            d->conv->step(d->arg);
            d->steps++;
            g_driven_steps++;
            g_conv_steps[conv_index(d->conv)]++;
            if (!slot_top(d))
                break;
        }
    }
    ps2k_step_leave(ctx);
    g_prio = saved;
    g_depth--;
    d->running = 0;
}

static void compact(void)
{
    int j = 0;
    for (int i = 0; i < g_nds; i++)
        if (g_ds[i].tid > 0)
            g_ds[j++] = g_ds[i];
    g_nds = j;
    /* (order, tid) order; slots added during a step were appended */
    for (int i = 1; i < g_nds; i++)
        for (int k = i; k > 0 && (g_ds[k - 1].conv->order > g_ds[k].conv->order ||
                                  (g_ds[k - 1].conv->order == g_ds[k].conv->order && g_ds[k - 1].tid > g_ds[k].tid));
             k--) {
            dslot t = g_ds[k - 1];
            g_ds[k - 1] = g_ds[k];
            g_ds[k] = t;
        }
}

static void run_due(int pass)
{
    g_busy = 1;
    if (!pass)
        for (int i = 0; i < g_nconv; i++) /* host job completions enter game state here */
            if (g_conv[i]->point)
                g_conv[i]->point(NULL);
    for (int i = 0; i < g_nds; i++)
        if (!pass || g_ds[i].conv->anywhere)
            run_slot(&g_ds[i]);
    compact();
    g_busy = 0;
}

void rg_frame_point(void)
{
    if (g_busy || g_nconv == 0 || ps2k_in_handler() || ps2k_in_step() || ps2k_get_thread_id() <= 0 ||
        !rg_frame_native())
        return;
    g_points++;
    note_point();
    run_due(0);
}

/* native: the kernel's driver pass, after the handlers, before any flow resumes (kernel
 * context): the VBlank services woken by this pass's handlers that may run anywhere (tick,
 * disk watch) run here, every VBlank, whatever the flows are waiting in.  The others (they
 * take locks a waiting flow may hold) keep running at the flows' driver points. */
static void phase_hook(void)
{
    if (g_busy || g_nconv == 0 || !kn())
        return;
    g_phases++;
    run_due(1);
}

/* native: StartThread parked a driven thread; the HLE ran it at once (up to its first
 * WaitSema) when its priority was higher than the starter's */
static void parked_hook(int id)
{
    if (!kn())
        return;
    int prio = g_depth ? g_prio : ps2k_peek_priority();
    for (int i = 0; i < g_nds; i++) {
        dslot *d = &g_ds[i];
        if (d->tid != id || d->sema != -2 || d->running || d->conv->order >= prio)
            continue;
        int outer = !g_busy;
        g_busy = 1;
        g_eager_starts++;
        run_slot(d);
        if (outer) {
            compact();
            g_busy = 0;
        }
        return;
    }
}

/* native: a step is about to wait on `sema` with no count: run the other woken steps
 * (the HLE ran lower-priority ready threads while it waited); the kernel re-checks */
static void block_hook(int sema)
{
    (void)sema;
    if (!kn())
        return;
    g_block_runs++;
    int outer = !g_busy;
    g_busy = 1;
    for (int i = 0; i < g_nds; i++)
        if (!g_ds[i].running)
            run_slot(&g_ds[i]);
    if (outer) {
        compact();
        g_busy = 0;
    }
}

/* SignalSema hook: a converted thread whose priority is higher than the signaller's
 * ran at once on the HLE (the signal switched to it).  Inside a driver point the
 * signaller is the running step (its old priority); slots are not reordered then. */
static void signal_hook(int sema)
{
    if (ps2k_in_handler() || !rg_frame_native())
        return;
    int prio = g_depth ? g_prio : ps2k_peek_priority();
    int outer = !g_busy;
    static int dbg = -1;
    if (dbg < 0)
        dbg = getenv("RG_FRAME_DEBUG") != NULL;
    if (dbg)
        for (int i = 0; i < g_nds; i++)
            if (g_ds[i].conv->sync)
                fprintf(stderr, "sig %d: slot tid %d sema %d order %d prio %d running %d busy %d depth %d\n", sema, g_ds[i].tid,
                        g_ds[i].sema, g_ds[i].conv->order, prio, g_ds[i].running, g_busy, g_depth);
    for (int i = 0; i < g_nds; i++) {
        dslot *d = &g_ds[i];
        if (!d->conv->sync || d->tid <= 0 || d->running || d->conv->order >= prio)
            continue;
        /* the HLE ran a higher-priority thread inside StartThread: it reached its WaitSema */
        if (d->sema == -2 && ps2k_thread_driven_state(d->tid) == 2) {
            d->running = 1; /* its wait() may signal (a mutex): no re-entry */
            void *ctx = enter_ctx(d);
            slot_top(d);
            ps2k_step_leave(ctx);
            d->running = 0;
        }
        if (d->tid <= 0 || d->sema != sema)
            continue;
        g_busy = 1;
        g_sync_runs++;
        if (d->conv->point)
            d->conv->point(NULL);
        run_slot(d);
        if (outer) {
            compact();
            g_busy = 0;
        }
        return;
    }
}

static uint64_t g_logic_ticks; /* model state: the main flow's frame waits */
void rg_frame_frame_wait(void)
{
    if (ps2k_get_thread_id() == 1 && !ps2k_in_step())
        g_logic_ticks++;
}
uint64_t rg_frame_logic_ticks(void) { return g_logic_ticks; }

void rg_threads_field_end(void)
{
    for (int i = 0; i < g_nconv; i++)
        if (g_conv[i]->drain)
            g_conv[i]->drain();
    if (kn())
        ps2k_get_native_stats(&g_kstats); /* the kernel is gone at exit (report) */
}

int rg_frame_delay(uint32_t usec)
{
    /* libkernl DelayThread's own checks: a handler, EIE = 0 */
    if (ps2k_in_handler() || ps2k_get_thread_id() <= 0 || ps2k_in_step())
        return ps2k_delay_thread(usec);
    if (!(ps2k_cop0_status() & 0x10000u))
        return PS2K_DELAY_E_DISABLED;
    g_delays++;
    rg_frame_point();
    /* a kernel-private timed wait: the same virtual time as the alarm +
     * semaphore libkernl uses, without the ids (DelayThread's sema id was
     * freed again before it returned: LIFO reuse made it invisible) */
    ps2k_wait_until(ps2k_now() + ps2k_usec_to_cycles(usec));
    rg_frame_point();
    return 0;
}

void rg_frame_wait_cond(int (*cond)(void *arg), void *arg, const char *what)
{
    (void)what;
    rg_threads_log_at_exit();
    g_cond_waits++;
    for (;;) {
        rg_frame_point();
        if (cond(arg))
            break;
        ps2k_wait_poll(ps2k_now()); /* until anything else ran */
        g_cond_wakes++;
    }
}

/* ThreadYield_1d2b70 = RotateThreadReadyQueue(own priority): a driver point, then the
 * kernel's rotate: another ready flow of that priority runs first; with none it returns at
 * once, as on the HLE (MoviePlayerWaitTick_1d5810 yields 4 times per game frame with no
 * other thread of its priority: a no-op there, never a wait). */
void rg_frame_yield(int prio)
{
    g_yields++;
    rg_frame_point();
    if (kn() && ps2k_ready_at(prio))
        g_yield_waits++; /* natively: a real switch to the other flow */
    ps2k_rotate_thread_ready_queue(prio, 0);
}

void rg_frame_stats(rg_threads_stats *out)
{
    out->driven = g_driven;
    out->driven_steps = g_driven_steps;
    out->points = g_points;
    out->delays = g_delays;
    out->cond_waits = g_cond_waits;
    out->cond_wakes = g_cond_wakes;
    for (int i = 0; i < g_nconv; i++)
        out->refused += g_conv_refused[i];
}

void rg_frame_kernel_stats(ps2k_native_stats *out) { *out = g_kstats; }

void rg_frame_report(FILE *f)
{
    fprintf(f,
            "rg_frame: driven=%d points=%llu phases=%llu steps=%llu sync_runs=%llu eager_starts=%llu "
            "block_runs=%llu delays=%llu cond_waits=%llu cond_wakes=%llu yields=%llu yield_switches=%llu\n",
            g_driven, (unsigned long long)g_points, (unsigned long long)g_phases, (unsigned long long)g_driven_steps,
            (unsigned long long)g_sync_runs, (unsigned long long)g_eager_starts, (unsigned long long)g_block_runs,
            (unsigned long long)g_delays, (unsigned long long)g_cond_waits, (unsigned long long)g_cond_wakes,
            (unsigned long long)g_yields, (unsigned long long)g_yield_waits);
    for (int i = 0; i < g_nconv; i++)
        fprintf(f, "rg_frame:   %-36s steps=%llu refused=%d\n", g_conv[i]->name,
                (unsigned long long)g_conv_steps[i], g_conv_refused[i]);
    if (g_nflowlog || g_nflowreg) {
        fprintf(f, "rg_frame: flows started=%d (not converted: %d):", g_nflowlog, g_flows_unknown);
        for (int i = 0; i < g_nflowlog; i++) {
            const char *name = g_flowlog[i].tid == 1 ? "main" : "?";
            for (int k = 0; k < g_nflowreg; k++)
                if (g_flowreg[k].entry == g_flowlog[i].entry)
                    name = g_flowreg[k].name;
            fprintf(f, " %d:%s", g_flowlog[i].tid, g_flowlog[i].known ? name : "UNCONVERTED");
        }
        fprintf(f, "\n");
    }
    fprintf(f, "rg_frame: %llu VBlanks in %llu gaps without a driver point; longest:", (unsigned long long)g_gap_fields,
            (unsigned long long)g_gap_n);
    for (int i = 0; i < GAPS; i++)
        if (g_gap_len[i])
            fprintf(f, " %llu@vbl%llu", (unsigned long long)g_gap_len[i], (unsigned long long)g_gap_at[i]);
    fprintf(f, "\n");
}

int rg_frame_is_driven(void *entry)
{
    for (int i = 0; i < g_nds; i++)
        if (g_ds[i].tid > 0 && g_ds[i].conv->entry == entry && ps2k_thread_driven_state(g_ds[i].tid) == 2)
            return 1;
    return 0;
}
