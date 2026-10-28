/* SPDX-License-Identifier: CC0-1.0
 * EE kernel HLE tests (docs/KERNEL.md).  One executable, one test per argv[1].
 * Tests drive the SDK surface (eekernel.h) and inspect the core (ps2k.h).
 * Tests whose name ends in "_control" are deliberately wrong and are
 * registered with WILL_FAIL: they prove the corresponding check is armed. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eekernel.h"
#include "ps2k.h"
#include "rg_pace.h"
#include "rg_threads.h"

/* ---------------------------------------------------------------------- */
static int g_fail;
static int g_control; /* running a *_control variant */

#define CHECK(c)                                                                  \
    do {                                                                          \
        if (!(c)) {                                                               \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); \
            g_fail++;                                                             \
        }                                                                         \
    } while (0)
#define CHECK_EQ(a, b)                                                                       \
    do {                                                                                     \
        long long va_ = (long long)(a), vb_ = (long long)(b);                                \
        if (va_ != vb_) {                                                                    \
            fprintf(stderr, "%s:%d: CHECK_EQ failed: %s == %s (%lld vs %lld)\n", __FILE__, \
                    __LINE__, #a, #b, va_, vb_);                                             \
            g_fail++;                                                                        \
        }                                                                                    \
    } while (0)
#define CHECK_STR(a, b)                                                                         \
    do {                                                                                        \
        if (strcmp((a), (b)) != 0) {                                                            \
            fprintf(stderr, "%s:%d: CHECK_STR failed:\n  got  \"%s\"\n  want \"%s\"\n", __FILE__, \
                    __LINE__, (a), (b));                                                        \
            g_fail++;                                                                           \
        }                                                                                       \
    } while (0)

static char g_log[4096];
static void logf_(const char *fmt, ...)
{
    size_t n = strlen(g_log);
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(g_log + n, sizeof g_log - n, fmt, ap);
    va_end(ap);
}

static int g_violations;
static void on_violation(const char *call, const char *why)
{
    g_violations++;
    fprintf(stderr, "  (expected?) violation: %s: %s\n", call, why);
}

static char g_stack[16][0x800];
static int spawn_n;
static int spawn(void (*fn)(void *), int prio, void *arg)
{
    struct ThreadParam tp;
    memset(&tp, 0, sizeof tp);
    tp.entry = (void *)fn;
    tp.stack = g_stack[spawn_n++ & 15];
    tp.stackSize = sizeof g_stack[0];
    tp.initPriority = prio;
    int id = CreateThread(&tp);
    if (id >= 0)
        StartThread(id, arg);
    return id;
}

static int make_sema(int init, int max)
{
    struct SemaParam sp;
    memset(&sp, 0, sizeof sp);
    sp.initCount = init;
    sp.maxCount = max;
    return CreateSema(&sp);
}

static void reset(const ps2k_config *cfg)
{
    g_log[0] = 0;
    g_violations = 0;
    spawn_n = 0;
    ps2k_set_violation_hook(on_violation);
    ps2k_init(cfg);
}

static int run_main(void (*fn)(void *), int prio)
{
    return ps2k_run(fn, NULL, prio);
}

static uint64_t vbs_time(uint64_t k)
{
    return (k * PS2K_FIELD_SUB + 240ull * PS2K_HSYNC_SUB) / PS2K_SUB;
}

/* ======================================================================
 * priority order
 * ==================================================================== */
static int s_done;
static void w_log(void *arg)
{
    logf_("%s ", (const char *)arg);
    if (strcmp((const char *)arg, "A") == 0)
        SignalSema(s_done);
}

static void main_priority(void *unused)
{
    (void)unused;
    s_done = make_sema(0, 1);
    spawn(w_log, 30, "A");
    spawn(w_log, 20, "B");
    spawn(w_log, 20, "C");
    spawn(w_log, 5, "D"); /* higher than main: runs inside StartThread */
    logf_("m ");
    WaitSema(s_done);
    logf_("M");
}

static void t_priority_order(void)
{
    reset(NULL);
    CHECK_EQ(run_main(main_priority, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_STR(g_log, "D m B C A M");
}

/* ======================================================================
 * non-preemption (+ control)
 * ==================================================================== */
static int np_sema, np_poll_sema;
static volatile int np_counter;
static int np_seen = -1;
static int np_h_ran;

static int np_vif1_handler(int cause)
{
    (void)cause;
    iSignalSema(np_sema);
    return 0;
}

static void np_high(void *u)
{
    (void)u;
    WaitSema(np_sema);
    np_seen = np_counter;
    np_h_ran = 1;
}

static void main_nonpreempt(void *u)
{
    (void)u;
    np_sema = make_sema(0, 1);
    np_poll_sema = make_sema(0, 1);
    AddIntcHandler(INTC_VIF1, np_vif1_handler, -1);
    EnableIntc(INTC_VIF1);
    spawn(np_high, 10, NULL); /* runs at once, blocks on np_sema */
    for (int i = 0; i < 1000; i++) {
        np_counter = i + 1;
        if (i == 100)
            ps2k_raise_intc(PS2K_INTC_VIF1); /* a model raises VIF1: no kernel call */
        if (g_control && i == 200)
            ps2k_debug_force_preempt(); /* what a preemptive kernel would do */
    }
    CHECK_EQ(np_h_ran, 0); /* nothing ran during the loop */
    PollSema(np_poll_sema); /* defined point: VIF1 delivered, H preempts */
    CHECK_EQ(np_h_ran, 1);
}

static void t_non_preemption(void)
{
    reset(NULL);
    np_counter = 0;
    np_seen = -1;
    np_h_ran = 0;
    CHECK_EQ(run_main(main_nonpreempt, 50), PS2K_RUN_MAIN_EXIT);
    CHECK_EQ(np_seen, 1000); /* H saw the whole loop done */
}

/* ======================================================================
 * wakeup counting
 * ==================================================================== */
static int wk_tid, wk_s, wk_s2, wk_arm;
static int wk_vbs_handler(int cause)
{
    (void)cause;
    if (wk_arm) {
        wk_arm = 0;
        iWakeupThread(wk_tid);
    }
    return 0;
}

static void wk_worker(void *u)
{
    (void)u;
    for (int i = 0; i < 3; i++) {
        SleepThread(); /* consumes a banked wakeup, returns at once */
        logf_("s%d ", i);
    }
    SignalSema(wk_s); /* main (higher) preempts here */
    logf_("sleep ");
    SleepThread(); /* really blocks; woken by iWakeupThread */
    logf_("woke ");
    SignalSema(wk_s2);
}

static void wk_nop(void *u) { (void)u; }

static void main_wakeup(void *u)
{
    (void)u;
    struct ThreadParam info;
    wk_s = make_sema(0, 1);
    wk_s2 = make_sema(0, 1);
    AddIntcHandler(INTC_VBLANK_S, wk_vbs_handler, -1);
    EnableIntc(INTC_VBLANK_S);
    wk_tid = spawn(wk_worker, 20, NULL); /* READY, does not run yet */
    CHECK(WakeupThread(wk_tid) >= 0);
    CHECK(WakeupThread(wk_tid) >= 0);
    CHECK(WakeupThread(wk_tid) >= 0);
    CHECK(WakeupThread(GetThreadId()) < 0); /* self: error */
    ReferThreadStatus(wk_tid, &info);
    CHECK_EQ(info.wakeupCount, 3);
    WaitSema(wk_s);
    logf_("m ");
    ReferThreadStatus(wk_tid, &info);
    CHECK_EQ(info.status, THS_READY);
    CHECK_EQ(info.wakeupCount, 0);
    wk_arm = 1;
    WaitSema(wk_s2);
    logf_("M");
    /* cancel */
    int w2 = spawn(wk_nop, 30, NULL);
    WakeupThread(w2);
    WakeupThread(w2);
    CHECK_EQ(CancelWakeupThread(w2), 2);
    ReferThreadStatus(w2, &info);
    CHECK_EQ(info.wakeupCount, 0);
}

static void t_wakeup_counting(void)
{
    reset(NULL);
    CHECK_EQ(run_main(main_wakeup, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_STR(g_log, "s0 s1 s2 m sleep woke M");
}

/* ======================================================================
 * semaphores across threads and from handlers
 * ==================================================================== */
static int sm_items, sm_done, sm_vs, sm_fifo, sm_del;
static int sm_vbs_hits;

static void sm_consumer(void *u)
{
    (void)u;
    for (int i = 0; i < 4; i++) {
        WaitSema(sm_items);
        logf_("c%d ", i);
    }
    SignalSema(sm_done);
}

static void sm_producer(void *u)
{
    (void)u;
    for (int i = 0; i < 4; i++) {
        logf_("p%d ", i);
        SignalSema(sm_items); /* consumer is higher: switches at once */
    }
}

static void sm_fifo_waiter(void *arg)
{
    WaitSema(sm_fifo);
    logf_("%s", (const char *)arg);
    SignalSema(sm_done);
}

static int sm_del_result = 12345;
static void sm_del_waiter(void *u)
{
    (void)u;
    sm_del_result = WaitSema(sm_del);
    SignalSema(sm_done);
}

static int sm_vbs_handler(int cause)
{
    (void)cause;
    sm_vbs_hits++;
    iSignalSema(sm_vs);
    return 0;
}

static void main_sema(void *u)
{
    (void)u;
    struct SemaParam sp;
    sm_items = make_sema(0, 100);
    sm_done = make_sema(0, 1);
    spawn(sm_consumer, 20, NULL);
    spawn(sm_producer, 30, NULL);
    WaitSema(sm_done);
    logf_("| ");

    /* FIFO wake order among equal-priority waiters */
    sm_fifo = make_sema(0, 3);
    spawn(sm_fifo_waiter, 20, "X");
    spawn(sm_fifo_waiter, 20, "Y");
    spawn(sm_fifo_waiter, 20, "Z");
    DelayThread(10); /* let them block */
    ReferSemaStatus(sm_fifo, &sp);
    CHECK_EQ(sp.numWaitThreads, 3);
    CHECK_EQ(sp.maxCount, 3);
    SignalSema(sm_fifo);
    SignalSema(sm_fifo);
    SignalSema(sm_fifo);
    for (int i = 0; i < 3; i++)
        WaitSema(sm_done);
    logf_(" | ");

    /* max count is not a cap (VALIDATION.md 2b, real BIOS kernel): SignalSema
     * at max succeeds and the count exceeds max_count */
    int b = make_sema(1, 1);
    CHECK_EQ(SignalSema(b), b);
    ReferSemaStatus(b, &sp);
    CHECK_EQ(sp.currentCount, 2);
    CHECK_EQ(sp.maxCount, 1);
    CHECK_EQ(PollSema(b), b);
    CHECK_EQ(PollSema(b), b);
    CHECK(PollSema(b) < 0);
    ReferSemaStatus(b, &sp);
    CHECK_EQ(sp.currentCount, 0);
    int b2 = make_sema(0, 2);
    for (int i = 0; i < 3; i++)
        CHECK_EQ(SignalSema(b2), b2);
    ReferSemaStatus(b2, &sp);
    CHECK_EQ(sp.currentCount, 3);

    /* delete with a waiter */
    sm_del = make_sema(0, 1);
    spawn(sm_del_waiter, 20, NULL);
    DelayThread(10);
    CHECK(DeleteSema(sm_del) >= 0);
    WaitSema(sm_done);
    CHECK(sm_del_result < 0);
    CHECK(ReferSemaStatus(sm_del, &sp) < 0);

    /* from a handler: VBLANK_START signals, main waits 10 times */
    sm_vs = make_sema(0, 1);
    AddIntcHandler(INTC_VBLANK_S, sm_vbs_handler, 0);
    EnableIntc(INTC_VBLANK_S);
    for (int i = 0; i < 10; i++)
        WaitSema(sm_vs);
    logf_("v%d", sm_vbs_hits);
}

static void t_semaphores(void)
{
    reset(NULL);
    sm_vbs_hits = 0;
    CHECK_EQ(run_main(main_sema, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_STR(g_log, "p0 c0 p1 c1 p2 c2 p3 c3 | XYZ | v10");
}

/* ======================================================================
 * VBlank delivery over N virtual frames
 * ==================================================================== */
static int vb_s, vb_start, vb_end;
static int vb_start_h(int c) { (void)c; vb_start++; iSignalSema(vb_s); return 0; }
static int vb_end_h(int c) { (void)c; vb_end++; return 0; }

static void main_vblank(void *u)
{
    (void)u;
    vb_s = make_sema(0, 1);
    AddIntcHandler(INTC_VBLANK_S, vb_start_h, -1);
    AddIntcHandler(INTC_VBLANK_E, vb_end_h, -1);
    EnableIntc(INTC_VBLANK_S);
    EnableIntc(INTC_VBLANK_E);
    for (int i = 0; i < 600; i++)
        WaitSema(vb_s);
}

static void main_sleep_forever(void *u)
{
    (void)u;
    AddIntcHandler(INTC_VBLANK_S, vb_start_h, -1);
    EnableIntc(INTC_VBLANK_S);
    SleepThread();
}

static void t_vblank_count(void)
{
    reset(NULL);
    vb_start = vb_end = 0;
    CHECK_EQ(run_main(main_vblank, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_EQ(vb_start, 600);
    CHECK_EQ(vb_end, 599);
    CHECK_EQ(ps2k_vblank_count(), 600);
    CHECK_EQ(ps2k_now(), vbs_time(599));
    /* 600 fields of 59.94 Hz = 10.01 s virtual */
    CHECK(ps2k_now() > 10ull * PS2K_BUSCLK && ps2k_now() < 10ull * PS2K_BUSCLK + PS2K_BUSCLK / 50);

    /* time-limited run: 60 fields => exactly 60 VBLANK_START handler calls */
    ps2k_config cfg;
    ps2k_default_config(&cfg);
    cfg.stop_at_cycles = 60ull * PS2K_FIELD_SUB / PS2K_SUB;
    reset(&cfg);
    vb_start = 0;
    vb_s = make_sema(0, 1);
    CHECK_EQ(run_main(main_sleep_forever, 10), PS2K_RUN_TIME_LIMIT);
    CHECK_EQ(vb_start, 60);
    CHECK_EQ(ps2k_now(), cfg.stop_at_cycles);
}

/* ======================================================================
 * DelayThread in virtual time
 * ==================================================================== */
static uint64_t dl_t0;
static void dl_worker(void *arg)
{
    int usec = (int)(intptr_t)arg;
    CHECK_EQ(DelayThread(usec), 0);
    logf_("%d@%llu ", usec, (unsigned long long)(ps2k_now() - dl_t0));
    SignalSema(s_done);
}

static void main_delay(void *u)
{
    (void)u;
    uint64_t t0 = ps2k_now();
    CHECK_EQ(DelayThread(1000), 0);
    CHECK_EQ(ps2k_now() - t0, 147456); /* 1000 us * 147.456 cycles/us */

    s_done = make_sema(0, 3);
    int before = make_sema(0, 1);
    DeleteSema(before);
    dl_t0 = ps2k_now();
    spawn(dl_worker, 20, (void *)(intptr_t)5000);
    spawn(dl_worker, 20, (void *)(intptr_t)1000);
    spawn(dl_worker, 20, (void *)(intptr_t)3000);
    for (int i = 0; i < 3; i++)
        WaitSema(s_done);
    /* DelayThread's internal semas were all released */
    int after = make_sema(0, 1);
    CHECK_EQ(after, before);
    DeleteSema(after);

    DIntr();
    CHECK_EQ(DelayThread(100), (int)0x80008008u); /* libkernl: cannot wait with EIE=0 */
    EIntr();
    /* long delay spanning many vblanks: still exact */
    t0 = ps2k_now();
    DelayThread(2000000);
    CHECK_EQ(ps2k_now() - t0, ps2k_usec_to_cycles(2000000));
}

static void t_delay_thread(void)
{
    reset(NULL);
    CHECK_EQ(run_main(main_delay, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_STR(g_log, "1000@147456 3000@442368 5000@737280 ");
}

/* ======================================================================
 * DI / EI masking
 * ==================================================================== */
static int di_hits, di_sema, di_status_in_handler = -1;
static int di_handler(int cause)
{
    (void)cause;
    di_hits++;
    di_status_in_handler = CpuIntrDisabled_117070();
    EIntr(); /* handlers end with `ei` in the game: legal, handler-local */
    iSignalSema(di_sema);
    return 0;
}

static void di_other(void *u)
{
    (void)u;
    logf_("o%d ", (ps2k_cop0_status() >> 16) & 1); /* main re-enabled: EIE = 1 */
}

/* runs while main is blocked with EIE = 0: retail (VALIDATION.md 2e) shows
 * EIE = 0 here (global EIE; a new thread does not start with EIE = 1); the
 * per-thread model shows 1 */
static void di_carry(void *u)
{
    logf_("c%d ", (ps2k_cop0_status() >> 16) & 1);
    SignalSema(*(int *)u);
}

static void main_di(void *u)
{
    (void)u;
    int probe = make_sema(0, 1);
    di_sema = make_sema(0, 1);
    AddIntcHandler(INTC_VIF1, di_handler, -1);
    EnableIntc(INTC_VIF1);
    CHECK_EQ(CpuIntrDisabled_117070(), 0);

    CHECK_EQ(DisableIntr_120660(), 1); /* was enabled */
    CHECK_EQ(ps2k_cop0_status() & 0x10000u, 0);
    ps2k_raise_intc(PS2K_INTC_VIF1);
    PollSema(probe); /* kernel call with EIE=0: no delivery */
    if (g_control)
        ps2k_debug_force_preempt(); /* deliberately ignores EIE */
    CHECK_EQ(di_hits, 0);
    CHECK_EQ(EnableIntr_1206b0(), 0); /* was disabled; EI delivers */
    CHECK_EQ(di_hits, 1);
    CHECK_EQ(di_status_in_handler, 1); /* handler saw Status.IE == 0 */
    CHECK_EQ(ps2k_cop0_status() & 0x10000u, 0x10000u);
    CHECK_EQ(PollSema(di_sema), di_sema);

    /* block with DI: the kernel/idle context delivers the latched VIF1, and
     * main wakes with EIE = 0 (both EIE models) */
    DIntr();
    ps2k_raise_intc(PS2K_INTC_VIF1);
    spawn(di_other, 20, NULL);
    WaitSema(di_sema); /* blocks; the kernel (EIE=1) delivers VIF1 at once */
    CHECK_EQ(di_hits, 2);
    CHECK_EQ(DIntr(), 0); /* still disabled for this thread after the switch */
    EIntr();
    DelayThread(10); /* di_other runs; EIE = 1 */

    /* DI carries over a blocking call to the next thread (VALIDATION.md 2e) */
    static int carry_sema;
    carry_sema = make_sema(0, 1);
    DIntr();
    spawn(di_carry, 20, &carry_sema);
    WaitSema(carry_sema);
    CHECK_EQ(DIntr(), 0); /* main wakes with EIE = 0 */
    EIntr();

    /* EnableIntc on a pending, masked cause delivers on enable */
    DisableIntc_117080(INTC_VIF1);
    ps2k_raise_intc(PS2K_INTC_VIF1);
    PollSema(probe);
    CHECK_EQ(di_hits, 2);
    CHECK_EQ(EnableIntc_1170e8(INTC_VIF1), 1);
    CHECK_EQ(di_hits, 3);
    PollSema(di_sema);
}

static void t_di_ei(void)
{
    reset(NULL); /* default: retail global EIE */
    di_hits = 0;
    CHECK_EQ(run_main(main_di, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_STR(g_log, "o1 c0 ");
}

/* the non-retail per-thread EIE model behind cfg.eie_per_thread */
static void t_di_ei_per_thread(void)
{
    ps2k_config cfg;
    ps2k_default_config(&cfg);
    cfg.eie_per_thread = 1;
    reset(&cfg);
    di_hits = 0;
    CHECK_EQ(run_main(main_di, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_STR(g_log, "o1 c1 ");
}

/* ======================================================================
 * INTC chain order and stop rule (VALIDATION.md 2a)
 * ==================================================================== */
static int ch_ret;
static int ch_h1(int c) { (void)c; logf_("H1"); return ch_ret; }
static int ch_lib(int c) { (void)c; logf_("L"); return 0; }
static int ch_h2(int c) { (void)c; logf_("H2"); return 0; }
static void main_chain(void *u)
{
    (void)u;
    int probe = make_sema(0, 1);
    CHECK(AddIntcHandler(INTC_VIF1, ch_lib, -1) > 0); /* libgraph's, already there */
    CHECK(AddIntcHandler(INTC_VIF1, ch_h1, 0) > 0);   /* next = 0: head */
    CHECK(AddIntcHandler(INTC_VIF1, ch_h2, -1) > 0);  /* next = -1: tail */
    EnableIntc(INTC_VIF1);
    static const int rets[] = {0, 1, 5, -1, 0};
    for (int i = 0; i < 5; i++) {
        ch_ret = rets[i];
        ps2k_raise_intc(PS2K_INTC_VIF1);
        PollSema(probe); /* delivery point */
        logf_(" ");
    }
}
static void t_intc_chain(void)
{
    reset(NULL);
    CHECK_EQ(run_main(main_chain, 10), PS2K_RUN_MAIN_EXIT);
    /* only a negative return stops the chain; 0 and positive continue.  The
     * control expects the old "stop at the first non-zero" rule. */
    CHECK_STR(g_log, g_control ? "H1LH2 H1 H1 H1 H1LH2 " : "H1LH2 H1LH2 H1LH2 H1 H1LH2 ");
}

/* ======================================================================
 * id numbering (VALIDATION.md 2c)
 * ==================================================================== */
static void id_nop(void *u) { (void)u; }
static int id_dummy(int c) { (void)c; return 0; }
static void main_ids(void *u)
{
    (void)u;
    /* threads: main = 1, created threads from 2, no immediate reuse */
    CHECK_EQ(GetThreadId(), 1);
    int t2 = spawn(id_nop, 5, NULL), t3 = spawn(id_nop, 5, NULL), t4 = spawn(id_nop, 5, NULL);
    CHECK_EQ(t2, 2);
    CHECK_EQ(t3, 3);
    CHECK_EQ(t4, 4);
    CHECK_EQ(DeleteThread(t3), t3); /* ran to completion: dormant */
    CHECK_EQ(DeleteThread(t2), t2);
    CHECK_EQ(spawn(id_nop, 5, NULL), 5);
    CHECK_EQ(spawn(id_nop, 5, NULL), 6);

    /* semaphores: first id 0, last freed = first reused */
    int s[6];
    for (int i = 0; i < 6; i++)
        s[i] = make_sema(0, 1);
    for (int i = 0; i < 6; i++)
        CHECK_EQ(s[i], i);
    DeleteSema(5); /* freed before */
    DeleteSema(3); /* just freed */
    int a = make_sema(0, 1), b = make_sema(0, 1), c = make_sema(0, 1);
    CHECK_EQ(a, 3);
    CHECK_EQ(b, 5);
    CHECK_EQ(c, 6);
    DeleteSema(b);
    CHECK_EQ(make_sema(0, 1), 5);
    struct SemaParam sp;
    CHECK_EQ(ReferSemaStatus(0, &sp), 0); /* id 0 is a valid id */
    CHECK_EQ(SignalSema(0), 0);
    CHECK_EQ(WaitSema(0), 0);

    /* INTC + DMAC handlers: one shared next-fit id range 1..128 (boot sequence
     * observed: INTC 1, DMAC 2, DMAC 3 after 2 was removed, INTC 4, 5; then a
     * per-frame add/remove walks 6..128 and wraps to 2, 6, ...) */
    CHECK_EQ(AddIntcHandler(INTC_VBLANK_E, id_dummy, -1), 1);
    CHECK_EQ(AddDmacHandler(DMAC_VIF1, id_dummy, -1), 2);
    CHECK_EQ(RemoveDmacHandler(DMAC_VIF1, 2), 2);
    CHECK_EQ(AddDmacHandler(DMAC_GIF, id_dummy, -1), 3);
    CHECK_EQ(AddIntcHandler(INTC_VIF1, id_dummy, -1), 4);
    CHECK_EQ(AddIntcHandler(INTC_GS, id_dummy, -1), 5);
    for (int want = 6; want <= 128; want++) {
        int h = AddDmacHandler(DMAC_VIF1, id_dummy, -1);
        CHECK_EQ(h, want);
        RemoveDmacHandler(DMAC_VIF1, h);
    }
    int w1 = AddDmacHandler(DMAC_VIF1, id_dummy, -1);
    CHECK_EQ(w1, 2); /* wrapped; 1, 3, 4, 5 in use */
    RemoveDmacHandler(DMAC_VIF1, w1);
    CHECK_EQ(AddDmacHandler(DMAC_VIF1, id_dummy, -1), 6);
}
static void t_ids(void)
{
    reset(NULL);
    CHECK_EQ(run_main(main_ids, 10), PS2K_RUN_MAIN_EXIT);
}

/* ======================================================================
 * deterministic replay
 * ==================================================================== */
static int dt_s, dt_ping, dt_pong, dt_perturb;
static int dt_vbs(int c) { (void)c; iSignalSema(dt_s); return 0; }
static void dt_alarm(int id, unsigned short t, void *arg)
{
    (void)id;
    (void)t;
    iWakeupThread((int)(intptr_t)arg);
}
static void dt_pinger(void *u)
{
    (void)u;
    for (int i = 0; i < 50; i++) {
        SignalSema(dt_ping);
        WaitSema(dt_pong);
        DelayThread(700 + 13 * i + dt_perturb);
    }
}
static void dt_ponger(void *u)
{
    (void)u;
    for (int i = 0; i < 50; i++) {
        WaitSema(dt_ping);
        (void)ps2k_hw_read32(PS2K_T0_COUNT);
        SignalSema(dt_pong);
    }
}
static void dt_sleeper(void *u)
{
    (void)u;
    for (int i = 0; i < 20; i++) {
        SetAlarm((unsigned short)(37 + i), dt_alarm, (void *)(intptr_t)GetThreadId());
        SleepThread();
        RotateThreadReadyQueue(25);
    }
}
static void dt_main(void *u)
{
    (void)u;
    ps2k_hw_write32(PS2K_T0_MODE, 0x83);
    dt_s = make_sema(0, 1);
    dt_ping = make_sema(0, 1);
    dt_pong = make_sema(0, 1);
    AddIntcHandler(INTC_VBLANK_S, dt_vbs, -1);
    EnableIntc(INTC_VBLANK_S);
    spawn(dt_pinger, 25, NULL);
    spawn(dt_ponger, 24, NULL);
    spawn(dt_sleeper, 25, NULL);
    for (int i = 0; i < 120; i++)
        WaitSema(dt_s);
}

static void dt_run(uint64_t *hash, uint64_t *count, int perturb)
{
    reset(NULL);
    dt_perturb = perturb;
    CHECK_EQ(run_main(dt_main, 10), PS2K_RUN_MAIN_EXIT);
    *hash = ps2k_trace_hash();
    *count = ps2k_trace_count();
}

static void t_determinism(void)
{
    uint64_t h1, n1, h2, n2, h3, n3;
    dt_run(&h1, &n1, 0);
    dt_run(&h2, &n2, g_control ? 1 : 0); /* control: second run perturbed */
    fprintf(stderr, "  trace: %llu records, hash %016llx / %016llx\n", (unsigned long long)n1,
            (unsigned long long)h1, (unsigned long long)h2);
    CHECK(n1 > 1000);
    CHECK_EQ(n1, n2);
    CHECK(h1 == h2);
    if (!g_control) {
        /* sensitivity: a 1 us change in one delay must change the trace */
        dt_run(&h3, &n3, 1);
        CHECK(h3 != h1);
    }
}

/* ======================================================================
 * context violations ("i" only in handlers)
 * ==================================================================== */
static int cv_s, cv_wait_r, cv_sig_r, cv_start_r, cv_tid;
static int cv_handler(int c)
{
    (void)c;
    cv_wait_r = WaitSema(cv_s);            /* violation */
    cv_sig_r = SignalSema(cv_s);           /* violation */
    cv_start_r = StartThread(cv_tid, 0);   /* libkernl: -1, no violation */
    return 0;
}
static void cv_nop(void *u) { (void)u; }
static void main_violation(void *u)
{
    (void)u;
    cv_s = make_sema(0, 1);
    struct ThreadParam tp;
    memset(&tp, 0, sizeof tp);
    tp.entry = (void *)cv_nop;
    tp.initPriority = 20;
    cv_tid = CreateThread(&tp);
    CHECK(iSignalSema(cv_s) < 0); /* violation: i-call in thread context */
    CHECK_EQ(g_violations, 1);
    AddIntcHandler(INTC_VIF1, cv_handler, -1);
    EnableIntc(INTC_VIF1);
    ps2k_raise_intc(PS2K_INTC_VIF1);
    PollSema(cv_s);
    CHECK_EQ(g_violations, 3);
    CHECK(cv_wait_r < 0);
    CHECK(cv_sig_r < 0);
    CHECK_EQ(cv_start_r, -1);
    struct ThreadParam info;
    ReferThreadStatus(cv_tid, &info);
    CHECK_EQ(info.status, THS_DORMANT);
}
static void t_context_violations(void)
{
    reset(NULL);
    CHECK_EQ(run_main(main_violation, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_EQ(ps2k_violation_count(), 3);
    g_violations = 0; /* expected ones */
}

/* ======================================================================
 * timers
 * ==================================================================== */
static uint64_t tm_cmp_time;
static int tm_cmp_hits, tm_ovf_hits;
static int tm_t2(int c)
{
    (void)c;
    tm_cmp_hits++;
    if (!tm_cmp_time)
        tm_cmp_time = ps2k_now();
    ps2k_hw_write32(PS2K_T2_BASE + 0x10, ps2k_hw_read32(PS2K_T2_BASE + 0x10)); /* ack EQUF */
    return 0;
}
static int tm_t1(int c)
{
    (void)c;
    tm_ovf_hits++;
    return 0;
}
static void main_timers(void *u)
{
    (void)u;
    CHECK_EQ(ps2k_now(), 0);
    /* T2: BUSCLK/256, ZRET, CUE, CMPE; comp 1000 -> period 1001 ticks */
    AddIntcHandler(INTC_TIM2, tm_t2, -1);
    EnableIntc(INTC_TIM2);
    ps2k_hw_write32(PS2K_T2_BASE + 0x20, 1000);
    ps2k_hw_write32(PS2K_T2_BASE + 0x00, 0);
    ps2k_hw_write32(PS2K_T2_BASE + 0x10, 0x2 | 0x40 | 0x80 | 0x100);
    /* T1: BUSCLK, CUE, OVFE, start at 0xFF00 -> overflow after 256 cycles */
    AddIntcHandler(INTC_TIM1, tm_t1, -1);
    EnableIntc(INTC_TIM1);
    ps2k_hw_write32(PS2K_T1_BASE + 0x00, 0xFF00);
    ps2k_hw_write32(PS2K_T1_BASE + 0x10, 0x0 | 0x80 | 0x200);
    /* T0 as the game sets it: HBLNK clock, CUE (T0_MODE = 0x83) */
    ps2k_hw_write32(PS2K_T0_MODE, 0x83);
    ps2k_hw_write32(PS2K_T0_COUNT, 0);
    uint64_t h0 = ps2k_hsync_count();

    DelayThread(100000); /* 100 ms */
    uint64_t now = ps2k_now();
    CHECK_EQ(ps2k_hw_read32(PS2K_T0_COUNT), (ps2k_hsync_count() - h0) & 0xFFFF);
    /* ~1573 hsyncs in 100 ms */
    CHECK(ps2k_hw_read32(PS2K_T0_COUNT) >= 1572 && ps2k_hw_read32(PS2K_T0_COUNT) <= 1574);
    CHECK_EQ(tm_cmp_time, 1000ull * 256);
    CHECK_EQ(tm_cmp_hits, (int)(now / 256 + 1) / 1001); /* periodic */
    CHECK_EQ(ps2k_hw_read32(PS2K_T2_BASE), (uint32_t)((now / 256) % 1001));
    CHECK_EQ(tm_ovf_hits, 1 + (int)((now - 256) / 65536));
    CHECK(ps2k_hw_read32(PS2K_T1_BASE + 0x10) & 0x800); /* OVFF set (not acked) */
    /* writing the flag bit back clears it */
    ps2k_hw_write32(PS2K_T1_BASE + 0x10, 0x80 | 0x800);
    CHECK_EQ(ps2k_hw_read32(PS2K_T1_BASE + 0x10) & 0x800, 0);
    /* stopping T0 freezes its count */
    ps2k_hw_write32(PS2K_T0_MODE, 0x03);
    uint32_t frozen = ps2k_hw_read32(PS2K_T0_COUNT);
    DelayThread(20000);
    CHECK_EQ(ps2k_hw_read32(PS2K_T0_COUNT), frozen);
    /* INTC_MASK register reflects EnableIntc */
    CHECK_EQ(ps2k_hw_read32(PS2K_INTC_MASK) & ((1u << INTC_TIM1) | (1u << INTC_TIM2)),
             (1u << INTC_TIM1) | (1u << INTC_TIM2));
}
static void t_timers(void)
{
    ps2k_config cfg;
    ps2k_default_config(&cfg);
    cfg.vblank_enable = 0;
    reset(&cfg);
    tm_cmp_time = 0;
    tm_cmp_hits = tm_ovf_hits = 0;
    CHECK_EQ(run_main(main_timers, 10), PS2K_RUN_MAIN_EXIT);
}

/* ======================================================================
 * alarms
 * ==================================================================== */
static int al_hits, al_released_hits, al_chain;
static uint64_t al_time;
static void al_cb(int id, unsigned short t, void *arg)
{
    (void)id;
    (void)t;
    al_hits++;
    al_time = ps2k_now();
    if (al_chain-- > 0)
        iSetAlarm(5, al_cb, arg); /* re-arm from the handler */
    else
        iWakeupThread((int)(intptr_t)arg);
}
static void al_never(int id, unsigned short t, void *arg)
{
    (void)id;
    (void)t;
    (void)arg;
    al_released_hits++;
}
static void main_alarm(void *u)
{
    (void)u;
    int r = SetAlarm(50, al_never, NULL);
    CHECK(r >= 0);
    CHECK_EQ(ReleaseAlarm(r), r);
    CHECK(ReleaseAlarm(r) < 0);
    uint64_t h0 = ps2k_hsync_count();
    al_chain = 3;
    CHECK(SetAlarm(10, al_cb, (void *)(intptr_t)GetThreadId()) >= 0);
    SleepThread();
    CHECK_EQ(al_hits, 4);
    /* 10 + 3*5 hsyncs later, at the first cycle of that hsync */
    CHECK_EQ(ps2k_hsync_count(), h0 + 25);
    CHECK_EQ(al_time, ps2k_now());
    DelayThread(100000);
    CHECK_EQ(al_released_hits, 0);
}
static void t_alarms(void)
{
    reset(NULL);
    al_hits = al_released_hits = 0;
    CHECK_EQ(run_main(main_alarm, 10), PS2K_RUN_MAIN_EXIT);
}

/* ======================================================================
 * thread lifecycle: rotate, change priority, suspend/resume,
 * terminate/delete, restart, exit-delete
 * ==================================================================== */
static int lc_done, lc_restart_n;
static void lc_rot(void *arg)
{
    for (int i = 0; i < 3; i++) {
        logf_("%s", (const char *)arg);
        RotateThreadReadyQueue(20);
    }
    SignalSema(lc_done);
}
static void lc_marker(void *arg) { logf_("%s ", (const char *)arg); }
static void lc_block(void *u)
{
    (void)u;
    WaitSema(*(int *)u);
}
static void lc_restart(void *u)
{
    (void)u;
    lc_restart_n++;
}
static void lc_exitdel(void *u)
{
    (void)u;
    ExitDeleteThread();
}
static void main_lifecycle(void *u)
{
    (void)u;
    struct ThreadParam info;
    lc_done = make_sema(0, 3);
    spawn(lc_rot, 20, "1");
    spawn(lc_rot, 20, "2");
    spawn(lc_rot, 20, "3");
    for (int i = 0; i < 3; i++)
        WaitSema(lc_done);
    logf_(" ");

    /* raising another thread above us switches immediately */
    int l = spawn(lc_marker, 30, "L");
    logf_("a ");
    CHECK_EQ(ChangeThreadPriority(l, 5), 30);
    logf_("b ");

    /* own priority: returns old, keeps running unless someone is higher */
    CHECK_EQ(ChangeThreadPriority(TH_SELF, 12), 10);
    ReferThreadStatus(TH_SELF, &info);
    CHECK_EQ(info.currentPriority, 12);
    CHECK_EQ(info.initPriority, 10);
    CHECK_EQ(info.status, THS_RUN);

    /* VALIDATION.md 2d: StartThread of an equal-priority thread does not
     * switch, but ChangeThreadPriority to the caller's own unchanged priority
     * YIELDS (the caller goes to the tail of its queue) */
    spawn(lc_marker, 12, "Y");
    logf_("e ");
    CHECK_EQ(ChangeThreadPriority(TH_SELF, 12), 12);
    logf_("f ");

    /* suspend / resume */
    int s = spawn(lc_marker, 20, "S");
    CHECK(SuspendThread(s) >= 0);
    ReferThreadStatus(s, &info);
    CHECK_EQ(info.status, THS_SUSPEND);
    DelayThread(100);
    logf_("c ");
    CHECK(ResumeThread(s) >= 0);
    DelayThread(100);
    logf_("d ");

    /* terminate a waiting thread, then delete it */
    int bs = make_sema(0, 1);
    int t = spawn(lc_block, 20, &bs);
    DelayThread(100);
    ReferThreadStatus(t, &info);
    CHECK_EQ(info.status, THS_WAIT);
    CHECK_EQ(info.waitType, TSW_SEMA);
    CHECK_EQ(info.waitId, bs);
    CHECK(StartThread(t, NULL) < 0); /* not dormant */
    CHECK(DeleteThread(t) < 0);      /* not dormant */
    CHECK(TerminateThread(t) >= 0);
    struct SemaParam sp;
    ReferSemaStatus(bs, &sp);
    CHECK_EQ(sp.numWaitThreads, 0);
    CHECK(DeleteThread(t) >= 0);
    CHECK(ReferThreadStatus(t, &info) < 0);

    /* restart after exit: a fresh host fiber */
    int r = spawn(lc_restart, 5, NULL);
    CHECK_EQ(lc_restart_n, 1);
    CHECK(StartThread(r, NULL) >= 0);
    CHECK_EQ(lc_restart_n, 2);

    /* ExitDeleteThread frees the id */
    int x = spawn(lc_exitdel, 5, NULL);
    DelayThread(10);
    CHECK(ReferThreadStatus(x, &info) < 0);

    /* main may exit with other threads still blocked */
    spawn(lc_block, 20, &bs);
}
static void t_thread_lifecycle(void)
{
    reset(NULL);
    lc_restart_n = 0;
    CHECK_EQ(run_main(main_lifecycle, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_STR(g_log, "123123123 a L b e Y f c S d ");
}

/* ======================================================================
 * deadlock / stall detection, host stack depth
 * ==================================================================== */
static void main_deadlock(void *u)
{
    (void)u;
    WaitSema(make_sema(0, 1));
}
static int deep(int n)
{
    volatile char buf[1024];
    buf[0] = (char)n;
    return n ? deep(n - 1) + buf[0] : 0;
}
static void main_deep(void *u)
{
    (void)u;
    volatile int r = deep(400); /* ~400 KiB of host stack on a guest thread */
    CHECK(r != 0x7fffffff);
}
static void t_run_limits(void)
{
    ps2k_config cfg;
    ps2k_default_config(&cfg);
    cfg.vblank_enable = 0;
    reset(&cfg);
    CHECK_EQ(run_main(main_deadlock, 10), PS2K_RUN_DEADLOCK);

    ps2k_default_config(&cfg);
    cfg.stall_cycles = PS2K_BUSCLK; /* 1 s idle */
    reset(&cfg);
    CHECK_EQ(run_main(main_deadlock, 10), PS2K_RUN_STALL);
    CHECK(ps2k_now() <= PS2K_BUSCLK + PS2K_BUSCLK / 50);

    reset(NULL);
    CHECK_EQ(run_main(main_deep, 10), PS2K_RUN_MAIN_EXIT);
}


/* ======================================================================
 * service threads (docs/NATIVE-THREADS.md slice 1): the same game-shaped
 * thread run as a fiber and as a fiberless service step must give the same
 * kernel trace (hash and count), the same log and the same end state.
 * ==================================================================== */
static int sv_sema, sv_low_sema, sv_hi_sema, sv_steps, sv_limit, sv_tid, sv_extra;
static char sv_log[8192];
static int sv_wait(void *arg)
{
    (void)arg;
    return sv_steps < sv_limit ? sv_sema : -1;
}
static void sv_step(void *arg)
{
    (void)arg;
    size_t n = strlen(sv_log);
    if (n < sizeof sv_log - 32)
        snprintf(sv_log + n, sizeof sv_log - n, "s%d@%llu ", sv_steps, (unsigned long long)ps2k_vblank_count());
    sv_steps++;
    SignalSema(sv_low_sema); /* readies a lower-priority thread: no preemption */
    if (g_control && sv_extra)
        SignalSema(sv_low_sema); /* control: one kernel event more in the service run */
}
static void sv_thread(void *arg) /* the game shape */
{
    int s;
    while ((s = sv_wait(arg)) >= 0) {
        WaitSema(s);
        sv_step(arg);
    }
}
static int sv_vbs(int c)
{
    (void)c;
    iSignalSema(sv_sema);
    if (ps2k_vblank_count() % 3 == 0)
        iSignalSema(sv_hi_sema);
    return 0;
}
static void sv_low(void *u)
{
    (void)u;
    for (;;) {
        WaitSema(sv_low_sema);
        size_t n = strlen(sv_log);
        if (n < sizeof sv_log - 8)
            snprintf(sv_log + n, sizeof sv_log - n, "L ");
    }
}
static void sv_hi(void *u)
{
    (void)u;
    for (;;) {
        WaitSema(sv_hi_sema);
        size_t n = strlen(sv_log);
        if (n < sizeof sv_log - 8)
            snprintf(sv_log + n, sizeof sv_log - n, "H ");
    }
}
static int sv_service_mode;
static void sv_main(void *u)
{
    (void)u;
    sv_sema = make_sema(0, 1);
    sv_low_sema = make_sema(0, 1000);
    sv_hi_sema = make_sema(0, 1);
    AddIntcHandler(INTC_VBLANK_S, sv_vbs, -1);
    EnableIntc(INTC_VBLANK_S);
    spawn(sv_low, 25, NULL);
    spawn(sv_hi, 15, NULL);
    struct ThreadParam tp;
    memset(&tp, 0, sizeof tp);
    tp.entry = (void *)sv_thread;
    tp.initPriority = 18;
    sv_tid = CreateThread(&tp);
    if (sv_service_mode)
        CHECK_EQ(ps2k_thread_set_service(sv_tid, sv_wait, sv_step), 0);
    StartThread(sv_tid, NULL);
    for (int f = 0; f < 60; f++) {
        /* main (prio 20) works through VBlanks: charges cross the edge and the
         * service thread preempts it at the next defined point */
        for (int k = 0; k < 7; k++)
            ps2k_charge(PS2K_BUSCLK / 59 / 5);
        ps2k_wait_vblank();
    }
    struct ThreadParam info;
    ReferThreadStatus(sv_tid, &info);
    CHECK_EQ(info.status, THS_DORMANT); /* the loop ended: thread exited */
}
static void sv_run(int service, uint64_t *h, uint64_t *n, char *log, size_t cap)
{
    reset(NULL);
    sv_steps = 0;
    sv_limit = 40;
    sv_log[0] = 0;
    sv_service_mode = service;
    sv_extra = service;
    uint32_t steps0 = ps2k_svc_step_count(), def0 = ps2k_svc_deferred_count();
    CHECK_EQ(run_main(sv_main, 20), PS2K_RUN_MAIN_EXIT);
    *h = ps2k_trace_hash();
    *n = ps2k_trace_count();
    snprintf(log, cap, "%s", sv_log);
    if (service) {
        CHECK_EQ(ps2k_svc_step_count() - steps0, 40);
        CHECK_EQ(ps2k_svc_deferred_count() - def0, 0);
    }
    ps2k_shutdown();
}
static void t_service_thread(void)
{
    static char l1[8192], l2[8192];
    uint64_t h1, n1, h2, n2;
    sv_run(0, &h1, &n1, l1, sizeof l1);
    sv_run(1, &h2, &n2, l2, sizeof l2);
    fprintf(stderr, "  fiber:   %llu records %016llx\n  service: %llu records %016llx\n",
            (unsigned long long)n1, (unsigned long long)h1, (unsigned long long)n2, (unsigned long long)h2);
    CHECK(strstr(l1, "s39@") != NULL);
    CHECK(strstr(l1, "H ") != NULL);
    CHECK_EQ(n1, n2);
    CHECK(h1 == h2);
    CHECK_STR(l2, l1);
    reset(NULL); /* main() shuts down once more */
}

/* ======================================================================
 * poll wait (frame driver condition waits) + control
 * A worker (prio 25) woken by VBLANK_START sets a flag on its 4th wake;
 * main polls the flag.  10 us DelayThread polling and ps2k_wait_poll must
 * see it within one poll period of each other, the poll wait with a few
 * wakes instead of thousands.  A flag set by a handler alone is seen too.
 * ==================================================================== */
static int pw_sema, pw_wakes, pw_flag, pw_hflag, pw_mode;
static uint64_t pw_seen, pw_hseen;
static int pw_polls, pw_hpolls;
static int pw_vbs(int c)
{
    (void)c;
    iSignalSema(pw_sema);
    if (ps2k_vblank_count() == 7)
        pw_hflag = 1; /* handler-only change */
    return 0;
}
static void pw_worker(void *u)
{
    (void)u;
    for (;;) {
        WaitSema(pw_sema);
        if (++pw_wakes == 4)
            pw_flag = 1;
    }
}
static void pw_wait(void)
{
    uint64_t c10 = ps2k_usec_to_cycles(10);
    if (pw_mode == 0)
        ps2k_delay_thread(10);
    else if (g_control)
        ps2k_wait_until(ps2k_now() + 20 * c10); /* control: a coarser timed poll */
    else
        ps2k_wait_poll(ps2k_now() + c10);
}
static void pw_main(void *u)
{
    (void)u;
    pw_sema = make_sema(0, 1);
    AddIntcHandler(INTC_VBLANK_S, pw_vbs, -1);
    EnableIntc(INTC_VBLANK_S);
    spawn(pw_worker, 25, NULL);
    while (!pw_flag) {
        pw_wait();
        pw_polls++;
    }
    pw_seen = ps2k_now();
    while (!pw_hflag) {
        pw_wait();
        pw_hpolls++;
    }
    pw_hseen = ps2k_now();
}
static void pw_run(int mode, uint64_t *seen, uint64_t *hseen, int *polls, int *hpolls)
{
    reset(NULL);
    pw_wakes = pw_flag = pw_hflag = pw_polls = pw_hpolls = 0;
    pw_mode = mode;
    CHECK_EQ(run_main(pw_main, 20), PS2K_RUN_MAIN_EXIT);
    *seen = pw_seen;
    *hseen = pw_hseen;
    *polls = pw_polls;
    *hpolls = pw_hpolls;
    ps2k_shutdown();
}
static void t_poll_wait(void)
{
    uint64_t s0, h0, s1, h1;
    int p0, q0, p1, q1;
    uint64_t c10 = ps2k_usec_to_cycles(10);
    pw_run(0, &s0, &h0, &p0, &q0);
    pw_run(1, &s1, &h1, &p1, &q1);
    fprintf(stderr, "  delay: flag at %llu after %d polls, handler flag at %llu after %d\n"
                    "  poll:  flag at %llu after %d polls, handler flag at %llu after %d\n",
            (unsigned long long)s0, p0, (unsigned long long)h0, q0, (unsigned long long)s1, p1,
            (unsigned long long)h1, q1);
    CHECK((s1 > s0 ? s1 - s0 : s0 - s1) <= c10); /* within one poll period */
    CHECK((h1 > h0 ? h1 - h0 : h0 - h1) <= c10);
    CHECK(s1 >= vbs_time(3));
    CHECK(h1 >= vbs_time(6));
    CHECK(p0 > 1000);
    CHECK(p1 < 40);
    CHECK(q1 < 20);
    reset(NULL);
}

/* ======================================================================
 * driven threads (frame driver support in the kernel)
 * ==================================================================== */
static int dv_sema, dv_steps, dv_tid, dv_entry_ran, dv_exit_ran, dv_mark;
static void dv_entry(void *u)
{
    (void)u;
    dv_entry_ran = 1; /* runs only once the thread is started unmarked */
}
static void dv_hook(int id, ps2k_entry_fn entry, void *arg)
{
    (void)arg;
    if (entry == dv_entry && dv_mark)
        CHECK_EQ(ps2k_thread_set_driven(id), 0);
}
static int dv_vbs(int c)
{
    (void)c;
    if (iPollSema(dv_sema) < 0)
        iSignalSema(dv_sema);
    return 0;
}
static void dv_main(void *u)
{
    (void)u;
    struct ThreadParam tp, info;
    dv_sema = make_sema(0, 1);
    AddIntcHandler(INTC_VBLANK_S, dv_vbs, -1);
    EnableIntc(INTC_VBLANK_S);
    memset(&tp, 0, sizeof tp);
    tp.entry = (void *)dv_entry;
    tp.initPriority = 15;
    dv_mark = 1;
    dv_tid = CreateThread(&tp);
    CHECK_EQ(StartThread(dv_tid, NULL), dv_tid);
    CHECK_EQ(ps2k_thread_driven_state(dv_tid), 2);
    ReferThreadStatus(dv_tid, &info);
    CHECK_EQ(info.status, THS_WAIT);
    CHECK_EQ(ReleaseWaitThread(dv_tid), -1); /* cannot run a parked thread */
    /* the "driver": one step per signal, at each wait */
    for (int f = 0; f < 20; f++) {
        ps2k_wait_vblank();
        while (PollSema(dv_sema) >= 0)
            dv_steps++;
    }
    CHECK_EQ(dv_entry_ran, 0);
    CHECK_EQ(ps2k_driven_exit(dv_tid, 0), 0);
    dv_exit_ran = 1;
    ReferThreadStatus(dv_tid, &info);
    CHECK_EQ(info.status, THS_DORMANT);
    CHECK_EQ(ps2k_thread_driven_state(dv_tid), 0);
    /* restarted unmarked: an ordinary thread again */
    dv_mark = 0;
    CHECK_EQ(StartThread(dv_tid, NULL), dv_tid);
    ps2k_wait_vblank();
    CHECK_EQ(dv_entry_ran, 1);
    /* a parked thread can be terminated and deleted by the game */
    dv_mark = 1;
    int t2 = CreateThread(&tp);
    StartThread(t2, NULL);
    CHECK_EQ(ps2k_thread_driven_state(t2), 2);
    CHECK_EQ(TerminateThread(t2), t2);
    CHECK_EQ(ps2k_thread_driven_state(t2), 0);
    CHECK_EQ(DeleteThread(t2), t2);
}
static void t_driven_thread(void)
{
    reset(NULL);
    dv_steps = dv_entry_ran = dv_exit_ran = 0;
    ps2k_set_start_hook(dv_hook);
    CHECK_EQ(run_main(dv_main, 20), PS2K_RUN_MAIN_EXIT);
    ps2k_set_start_hook(NULL);
    CHECK_EQ(dv_steps, 20);
    CHECK_EQ(dv_exit_ran, 1);
}

/* ======================================================================
 * frame driver (src/native/threads/rg_frame.c, RG_THREADS=frame: over the HLE)
 * A convertible thread (prio 15 shape) woken by VBLANK_START: parked when
 * started, its body runs at main's driver points once per signal, on main;
 * its loop ends after 12 steps (exit tail runs, thread DORMANT).  A
 * condition set by a worker at VBlank 9 ends a condition wait at that time
 * with a few wakes.
 * ==================================================================== */
static int fd_sema, fd_steps, fd_tail, fd_wrong_thread, fd_flag, fd_wsema;
static int fd_wait(void *a) { (void)a; return fd_steps < 12 ? fd_sema : -1; }
static void fd_step(void *a)
{
    (void)a;
    fd_steps++;
    if (ps2k_get_thread_id() != 1)
        fd_wrong_thread++;
}
static void fd_exit(void *a) { (void)a; fd_tail++; }
static void fd_entry(void *a)
{
    int s;
    while ((s = fd_wait(a)) >= 0) {
        WaitSema(s);
        fd_step(a);
    }
    fd_exit(a);
}
static const rg_thread_conv fd_conv = {(void *)fd_entry, "fd_entry", fd_wait, fd_step, fd_exit, 0, 0, 15};
static int fd_vbs(int c)
{
    (void)c;
    if (iPollSema(fd_sema) < 0)
        iSignalSema(fd_sema);
    iSignalSema(fd_wsema);
    return 0;
}
static void fd_worker(void *u)
{
    (void)u;
    for (;;) {
        WaitSema(fd_wsema);
        if (ps2k_vblank_count() >= 9)
            fd_flag = 1;
    }
}
static int fd_cond(void *a) { (void)a; return fd_flag; }
static void fd_main(void *u)
{
    (void)u;
    struct ThreadParam tp, info;
    fd_sema = make_sema(0, 1);
    fd_wsema = make_sema(0, 1);
    AddIntcHandler(INTC_VBLANK_S, fd_vbs, -1);
    EnableIntc(INTC_VBLANK_S);
    spawn(fd_worker, 25, NULL);
    memset(&tp, 0, sizeof tp);
    tp.entry = (void *)fd_entry;
    tp.initPriority = 15;
    int tid = CreateThread(&tp);
    StartThread(tid, NULL);
    CHECK_EQ(ps2k_thread_driven_state(tid), 2);
    rg_frame_wait_cond(fd_cond, NULL, "test");
    CHECK_EQ(ps2k_vblank_count(), 9);
    for (int f = 0; f < 20; f++)
        rg_frame_delay(20000); /* > 1 field: one signal per field, one step each */
    ReferThreadStatus(tid, &info);
    CHECK_EQ(info.status, THS_DORMANT);
}
static void t_frame_driver(void)
{
    reset(NULL);
    rg_threads_convertible(&fd_conv);
    CHECK_EQ(rg_threads_mode(), RG_THREADS_FRAME);
    rg_threads_stats st0, st1;
    rg_threads_get_stats(&st0);
    CHECK_EQ(run_main(fd_main, 20), PS2K_RUN_MAIN_EXIT);
    rg_threads_get_stats(&st1);
    fprintf(stderr, "  steps %d, cond wakes %llu, points %llu\n", fd_steps,
            (unsigned long long)(st1.cond_wakes - st0.cond_wakes), (unsigned long long)(st1.points - st0.points));
    CHECK_EQ(fd_steps, 12);
    CHECK_EQ(fd_tail, 1);
    CHECK_EQ(fd_wrong_thread, 0);
    CHECK_EQ(st1.driven - st0.driven, 1);
    CHECK(st1.cond_wakes - st0.cond_wakes < 40);
    reset(NULL);
}

/* ======================================================================
 * frame-driven kernel (ps2k cfg.native, RG_THREADS=native, docs/NATIVE-THREADS.md
 * "Slice 5").  Main (prio 20) and a second flow (prio 20, the loading-screen
 * shape) are the only fibers.  A tick-shaped step (prio 18, anywhere) is woken by
 * the VBLANK_START handler and must run in the driver's pass of that VBlank,
 * before main's frame wait returns, as its own thread (step context).  A
 * disk-watch-shaped step (prio 15, anywhere, sync) takes a lock main holds
 * across 4 frames: it waits for it as a real waiter and runs at main's release.
 * No preemption: a raised VIF1 cause and a signal to the other flow change
 * nothing until main waits.  Logic time moves only at waits: T0 does not move
 * across a busy loop; DelayThread / ps2k_charge are exact timed waits.
 * The control runs the same scenario on the HLE (cfg.native = 0): the
 * no-preemption and placement checks must fail.
 * ==================================================================== */
static int fn_vsema, fn_wsema, fn_lock, fn_vsync, fn_vreq, fn_f2sema, fn_vif_flag;
static int fn_tick_tid, fn_dw_tid, fn_tick_steps, fn_tick_bad_ctx, fn_dw_at, fn_dw_steps, fn_f2_runs;
static int fn_tick_vbl[64];
static int fn_main_vbl[64], fn_nmain;
static int fn_dw_release_seen; /* main's frame counter when the locked part ran */
static int fn_frame;
static int fn_tick_wait(void *a) { (void)a; return fn_tick_steps < 40 ? fn_vsema : -1; }
static void fn_tick_step(void *a)
{
    (void)a;
    if (ps2k_get_thread_id() != fn_tick_tid || !ps2k_in_step())
        fn_tick_bad_ctx++;
    if (fn_tick_steps < 64)
        fn_tick_vbl[fn_tick_steps] = (int)ps2k_vblank_count();
    fn_tick_steps++;
}
static void fn_tick_entry(void *a)
{
    int s;
    while ((s = fn_tick_wait(a)) >= 0) {
        WaitSema(s);
        fn_tick_step(a);
    }
}
static int fn_dw_wait(void *a) { (void)a; return fn_dw_at ? fn_lock : fn_wsema; }
static void fn_dw_step(void *a)
{
    (void)a;
    if (fn_dw_at) { /* the lock is ours */
        fn_dw_at = 0;
        fn_dw_steps++;
        fn_dw_release_seen = fn_frame;
        SignalSema(fn_lock);
        return;
    }
    fn_dw_at = 1; /* next: WaitSema(lock) */
}
static void fn_dw_entry(void *a)
{
    int s;
    while ((s = fn_dw_wait(a)) >= 0) {
        WaitSema(s);
        fn_dw_step(a);
    }
}
static const rg_thread_conv fn_tick_conv = {(void *)fn_tick_entry, "fn_tick", fn_tick_wait, fn_tick_step, 0, 0, 0,
                                            18, 0, 0, 0, 0, 1};
static const rg_thread_conv fn_dw_conv = {(void *)fn_dw_entry, "fn_dw", fn_dw_wait, fn_dw_step, 0, 0, 0,
                                          15, 1, 0, 0, 0, 1};
static int fn_vbs(int c)
{
    (void)c;
    if (iPollSema(fn_vsema) < 0)
        iSignalSema(fn_vsema);
    if (ps2k_vblank_count() % 3 == 0 && iPollSema(fn_wsema) < 0)
        iSignalSema(fn_wsema);
    if (fn_vreq) {
        fn_vreq = 0;
        iSignalSema(fn_vsync);
    }
    return 0;
}
static int fn_vif(int c)
{
    (void)c;
    fn_vif_flag = 1;
    return 0;
}
static void fn_f2(void *u)
{
    (void)u;
    for (;;) {
        WaitSema(fn_f2sema);
        fn_f2_runs++;
    }
}
static void fn_frame_wait(void)
{
    fn_vreq = 1;
    WaitSema(fn_vsync);
    if (fn_nmain < 64)
        fn_main_vbl[fn_nmain++] = (int)ps2k_vblank_count();
    fn_frame++;
}
static void fn_main(void *u)
{
    (void)u;
    struct ThreadParam tp;
    fn_vsema = make_sema(0, 1);
    fn_wsema = make_sema(0, 1);
    fn_lock = make_sema(1, 1);
    fn_vsync = make_sema(0, 1);
    fn_f2sema = make_sema(0, 1);
    AddIntcHandler(INTC_VBLANK_S, fn_vbs, -1);
    EnableIntc(INTC_VBLANK_S);
    AddIntcHandler(INTC_VIF1, fn_vif, -1);
    EnableIntc(INTC_VIF1);
    spawn(fn_f2, 20, NULL);
    memset(&tp, 0, sizeof tp);
    tp.entry = (void *)fn_tick_entry;
    tp.initPriority = 18;
    fn_tick_tid = CreateThread(&tp);
    StartThread(fn_tick_tid, NULL);
    tp.entry = (void *)fn_dw_entry;
    tp.initPriority = 15;
    fn_dw_tid = CreateThread(&tp);
    StartThread(fn_dw_tid, NULL);
    CHECK_EQ(ps2k_thread_driven_state(fn_tick_tid), 2);
    /* no preemption: a latched cause, a signal to a ready flow, EI, kernel calls */
    ps2k_raise_intc(INTC_VIF1);
    SignalSema(fn_f2sema);
    EIntr();
    ReferThreadStatus(0, NULL);
    ps2k_poll();
    CHECK_EQ(fn_vif_flag, 0);
    CHECK_EQ(fn_f2_runs, 0);
    /* logic time: a busy loop costs nothing */
    ps2k_hw_write32(PS2K_T0_MODE, 0x83);
    uint64_t t0 = ps2k_now();
    uint32_t c0 = ps2k_hw_read32(PS2K_T0_COUNT);
    volatile uint32_t x = 0;
    for (int i = 0; i < 100000; i++)
        x += (uint32_t)i;
    CHECK_EQ(ps2k_hw_read32(PS2K_T0_COUNT), c0);
    CHECK_EQ(ps2k_now(), t0);
    /* a wait lets the latched cause and the other flow run */
    DelayThread(1000);
    CHECK_EQ(ps2k_now() - t0, 147456);
    CHECK_EQ(fn_vif_flag, 1);
    CHECK_EQ(fn_f2_runs, 1);
    t0 = ps2k_now();
    ps2k_charge(5000); /* a charge from a flow: a timed wait */
    CHECK_EQ(ps2k_now() - t0, 5000);
    /* frames; the lock held across frames 3..6 */
    int held = 0;
    for (int f = 0; f < 12; f++) {
        if (f == 3) {
            WaitSema(fn_lock);
            held = fn_dw_steps;
        }
        if (f == 7) {
            CHECK_EQ(fn_dw_steps, held); /* it waited for the lock (woken at least once meanwhile) */
            CHECK_EQ(fn_dw_at, 1);
            SignalSema(fn_lock); /* sync: the locked part runs here, at the release */
            CHECK_EQ(fn_dw_steps, held + 1);
            CHECK_EQ(fn_dw_release_seen, fn_frame);
        }
        fn_frame_wait();
    }
}
static void t_frame_native(void)
{
    ps2k_config kc;
    ps2k_default_config(&kc);
    kc.native = g_control ? 0 : 1;
    reset(&kc);
    rg_threads_convertible(&fn_tick_conv);
    rg_threads_convertible(&fn_dw_conv);
    CHECK_EQ(rg_threads_mode(), RG_THREADS_NATIVE);
    CHECK_EQ(run_main(fn_main, 20), PS2K_RUN_MAIN_EXIT);
    fprintf(stderr, "  tick steps %d (bad ctx %d), disk-watch steps %d, main frames %d\n", fn_tick_steps,
            fn_tick_bad_ctx, fn_dw_steps, fn_nmain);
    CHECK_EQ(fn_tick_bad_ctx, 0);
    CHECK(fn_dw_steps >= 2);
    /* the tick of VBlank v ran in v's pass, before main's frame wait returned at v */
    int ok = fn_nmain == 12;
    for (int i = 0; i < fn_nmain; i++) {
        int v = fn_main_vbl[i], seen = 0;
        for (int k = 0; k < fn_tick_steps && k < 64; k++)
            if (fn_tick_vbl[k] == v)
                seen = 1;
        ok = ok && seen;
    }
    CHECK(ok);
    ps2k_native_stats ns;
    ps2k_get_native_stats(&ns);
    if (!g_control) {
        CHECK_EQ(ns.flows, 2); /* main + the second flow; the steps have none */
        CHECK_EQ(ns.charge_waits, 1);
    }
    reset(NULL);
}

/* ---------------------------------------------------------------------- */
/* Paced mode (src/native/threads/rg_pace.c, docs/NATIVE-THREADS.md "Paced mode"): the
 * bounded fixed-step accumulator on a fake host clock.  Phases are owed at 59.94 Hz of host
 * time; the host loop below waits until one is owed, "runs" it (work_ns), and presents when
 * the pacer says so (present_ns; with vsync, a present ends at the next 60 Hz refresh). */
typedef struct pace_sim {
    uint64_t ticks, presents, max_batch, batch, first_ns_after_hitch, ticks_after_hitch_burst;
    uint64_t between;
} pace_sim;

static void pace_run(rg_pace *p, uint64_t seconds, uint64_t work_ns, uint64_t present_ns, int vsync,
                     uint64_t hitch_at_ns, uint64_t hitch_ns, int between, pace_sim *r)
{
    uint64_t now = 1000000000ull, end = now + seconds * 1000000000ull, hitch = now + hitch_at_ns;
    int hitched = 0, burst = -1;
    memset(r, 0, sizeof *r);
    while (now < end) {
        uint64_t w = rg_pace_until_tick(p, now);
        if (w) {
            uint32_t alpha = 0;
            if (between && rg_pace_between(p, now, &alpha)) {
                CHECK(alpha < 65536u);
                now += present_ns;
                rg_pace_presented(p, now);
                r->between++;
                continue;
            }
            uint64_t s = rg_pace_sleep_ns(p, w, now, between);
            now += s ? s : 1000;
            continue;
        }
        rg_pace_take_tick(p);
        r->ticks++;
        r->batch++;
        if (burst >= 0)
            burst++;
        now += work_ns;
        if (hitch_ns && !hitched && now >= hitch) {
            now += hitch_ns; /* a debugger / load hitch */
            hitched = 1;
            burst = 0;
        }
        if (rg_pace_present_now(p, now)) {
            if (vsync) /* the present returns at the next 60 Hz refresh */
                now = (now / 16666667ull + 1) * 16666667ull;
            else
                now += present_ns;
            rg_pace_presented(p, now);
            r->presents++;
            if (r->batch > r->max_batch)
                r->max_batch = r->batch;
            r->batch = 0;
            if (burst > 0 && !r->ticks_after_hitch_burst)
                r->ticks_after_hitch_burst = (uint64_t)burst;
        }
    }
}

static void t_pace(void)
{
    rg_pace p;
    rg_pace_config c;
    pace_sim r;

    /* retail (Original, and every run without a host clock): no host time at all */
    rg_pace_default_config(&c);
    rg_pace_init(&p, &c);
    CHECK_EQ(rg_pace_until_tick(&p, 0), 0);
    CHECK_EQ(rg_pace_until_tick(&p, 123456789), 0);
    rg_pace_take_tick(&p);
    CHECK_EQ(rg_pace_present_now(&p, 5), 1);

    /* host, fast host, no cap: 10 s owe 599.4 phases, one present per phase */
    c.mode = RG_PACE_HOST;
    c.max_ticks = g_control ? 60 : 4; /* control: no debt bound (the hitch check below fails) */
    rg_pace_init(&p, &c);
    pace_run(&p, 10, 2000000, 1000000, 0, 0, 0, 0, &r);
    fprintf(stderr, "  host uncapped: ticks %llu presents %llu max batch %llu\n", (unsigned long long)r.ticks,
            (unsigned long long)r.presents, (unsigned long long)r.max_batch);
    CHECK(r.ticks >= 599 && r.ticks <= 601);
    CHECK_EQ(r.presents, r.ticks);
    CHECK_EQ(r.max_batch, 1);

    /* cap 30: two phases per present, logic still 59.94 Hz */
    c.cap_fps = 30;
    rg_pace_init(&p, &c);
    pace_run(&p, 10, 2000000, 1000000, 0, 0, 0, 0, &r);
    fprintf(stderr, "  host cap 30: ticks %llu presents %llu hist[2] %llu\n", (unsigned long long)r.ticks,
            (unsigned long long)r.presents, (unsigned long long)p.hist[2]);
    CHECK(r.ticks >= 599 && r.ticks <= 601);
    CHECK(r.presents >= 298 && r.presents <= 301);
    CHECK(p.hist[2] >= 295);

    /* cap 60 (just above 59.94): never skips a phase's present */
    c.cap_fps = 60;
    rg_pace_init(&p, &c);
    pace_run(&p, 10, 2000000, 1000000, 0, 0, 0, 0, &r);
    CHECK(r.presents >= r.ticks - 1);

    /* vsync at 60 Hz, no cap: the present paces the loop; logic stays at 59.94 Hz */
    c.cap_fps = 0;
    c.vsync = 1;
    rg_pace_init(&p, &c);
    pace_run(&p, 10, 2000000, 0, 1, 0, 0, 0, &r);
    fprintf(stderr, "  vsync 60: ticks %llu presents %llu max batch %llu\n", (unsigned long long)r.ticks,
            (unsigned long long)r.presents, (unsigned long long)r.max_batch);
    CHECK(r.ticks >= 599 && r.ticks <= 601);
    CHECK(r.max_batch <= 2);
    c.vsync = 0;

    /* a slow host (a phase costs 25 ms): logic falls behind real time, never ahead; at most
     * k phases per present; the debt beyond k phases is dropped */
    rg_pace_init(&p, &c);
    pace_run(&p, 10, 25000000, 1000000, 0, 0, 0, 0, &r);
    fprintf(stderr, "  slow host: ticks %llu presents %llu max batch %llu resyncs %llu forced %llu\n",
            (unsigned long long)r.ticks, (unsigned long long)r.presents, (unsigned long long)r.max_batch,
            (unsigned long long)p.resyncs, (unsigned long long)p.forced);
    CHECK(r.ticks <= 600);
    CHECK(r.max_batch <= c.max_ticks);
    CHECK(p.dropped_ticks > 0 || g_control);
    CHECK(p.resyncs == 0 || g_control); /* slower than 59.94 Hz is not a hitch */

    /* a host just over budget (17.5 ms per phase, 5 % slower than 59.94 Hz): with the default
     * catch-up rule every phase is presented (skipping presents cannot win the time back; the
     * game runs at the host's speed, the debt beyond k dropped); the first design
     * (catchup = 1) fell into batches of k phases per present, the rendered frames between
     * never shown (docs/PERF-3D.md "Transition stutter") */
    rg_pace_init(&p, &c);
    pace_run(&p, 10, 17500000, 500000, 0, 0, 0, 0, &r);
    fprintf(stderr, "  over budget: ticks %llu presents %llu max batch %llu slow presents %llu\n",
            (unsigned long long)r.ticks, (unsigned long long)r.presents, (unsigned long long)r.max_batch,
            (unsigned long long)p.skipped_slow);
    CHECK(g_control || r.max_batch <= 2);
    CHECK(g_control || r.presents + 2 >= r.ticks);
    {
        rg_pace_config c1 = c;
        c1.catchup = 1; /* the first design */
        rg_pace_init(&p, &c1);
        pace_run(&p, 10, 17500000, 500000, 0, 0, 0, 0, &r);
        fprintf(stderr, "  over budget, catchup 1: ticks %llu presents %llu max batch %llu\n",
                (unsigned long long)r.ticks, (unsigned long long)r.presents, (unsigned long long)r.max_batch);
        CHECK(r.max_batch == c1.max_ticks);
    }

    /* a 1 s hitch at 5 s: at most k phases back to back after it, ~60 phases dropped */
    rg_pace_init(&p, &c);
    pace_run(&p, 10, 2000000, 1000000, 0, 5000000000ull, 1000000000ull, 0, &r);
    fprintf(stderr, "  hitch: ticks %llu burst %llu resyncs %llu dropped %llu\n", (unsigned long long)r.ticks,
            (unsigned long long)r.ticks_after_hitch_burst, (unsigned long long)p.resyncs,
            (unsigned long long)p.dropped_ticks);
    CHECK(r.ticks_after_hitch_burst >= 1 && r.ticks_after_hitch_burst <= 4);
    CHECK(r.ticks >= 535 && r.ticks <= 546);
    CHECK_EQ(p.resyncs, 1);

    /* between phases: a presenter at a 144 Hz cap shows N frames per phase */
    c.cap_fps = 144;
    rg_pace_init(&p, &c);
    pace_run(&p, 10, 2000000, 500000, 0, 0, 0, 1, &r);
    fprintf(stderr, "  144 between: ticks %llu presents %llu+%llu\n", (unsigned long long)r.ticks,
            (unsigned long long)r.presents, (unsigned long long)r.between);
    CHECK(r.ticks >= 599 && r.ticks <= 601);
    CHECK(r.presents + r.between >= 1400 && r.presents + r.between <= 1442);
}

/* ---------------------------------------------------------------------- */
static const struct {
    const char *name;
    void (*fn)(void);
} tests[] = {
    {"priority_order", t_priority_order},
    {"non_preemption", t_non_preemption},
    {"wakeup_counting", t_wakeup_counting},
    {"semaphores", t_semaphores},
    {"vblank_count", t_vblank_count},
    {"delay_thread", t_delay_thread},
    {"di_ei", t_di_ei},
    {"di_ei_per_thread", t_di_ei_per_thread},
    {"intc_chain", t_intc_chain},
    {"ids", t_ids},
    {"determinism", t_determinism},
    {"context_violations", t_context_violations},
    {"timers", t_timers},
    {"alarms", t_alarms},
    {"thread_lifecycle", t_thread_lifecycle},
    {"run_limits", t_run_limits},
    {"service_thread", t_service_thread},
    {"poll_wait", t_poll_wait},
    {"driven_thread", t_driven_thread},
    {"frame_driver", t_frame_driver},
    {"frame_native", t_frame_native},
    {"pace", t_pace},
};

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    /* the SDK surface follows RG_THREADS (DelayThread through the frame driver in native
     * mode): the HLE tests run the libkernl algorithm, frame_driver the driver over the HLE
     * (RG_THREADS=frame), frame_native the frame-driven kernel (RG_THREADS=native) */
    if (!getenv("RG_THREADS")) {
        const char *mode = argc >= 2 && strncmp(argv[1], "frame_native", 12) == 0 ? "native"
                           : argc >= 2 && strncmp(argv[1], "frame_", 6) == 0     ? "frame"
                                                                                  : "hle";
#ifdef _WIN32
        char kv[32];
        snprintf(kv, sizeof kv, "RG_THREADS=%s", mode);
        _putenv(kv);
#else
        setenv("RG_THREADS", mode, 1);
#endif
    }
    int ran = 0;
    for (size_t i = 0; i < sizeof tests / sizeof tests[0]; i++) {
        char ctl[64];
        snprintf(ctl, sizeof ctl, "%s_control", tests[i].name);
        int want = argc < 2 || strcmp(argv[1], tests[i].name) == 0;
        int want_ctl = argc >= 2 && strcmp(argv[1], ctl) == 0;
        if (!want && !want_ctl)
            continue;
        g_control = want_ctl;
        int before = g_fail;
        tests[i].fn();
        if (g_violations) {
            fprintf(stderr, "%s: %d unexpected context violation(s)\n", tests[i].name, g_violations);
            g_fail++;
        }
        ps2k_shutdown();
        printf("%-28s %s  (backend %s)\n", want_ctl ? ctl : tests[i].name,
               g_fail == before ? "PASS" : "FAIL", ps2k_backend_name());
        ran++;
    }
    if (!ran) {
        fprintf(stderr, "unknown test '%s'\n", argc > 1 ? argv[1] : "");
        return 2;
    }
    return g_fail ? 1 : 0;
}
