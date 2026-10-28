/* SPDX-License-Identifier: CC0-1.0
 * rg_spin tests (docs/SPIN.md): the loop shapes stage `spin` produces, run
 * on the EE kernel HLE.  One executable, one test per argv[1]; names ending
 * in "_control" are deliberately wrong (WILL_FAIL) and prove a check is armed.
 *
 *   handler_flag  main spins on a flag a VBLANK_START handler sets; with the
 *                 hint it leaves at the first VBLANK_START, exactly
 *   thread_flag   main spins on a flag a higher-priority thread sets after
 *                 DelayThread(1000): the hint's charge fires the alarm and the
 *                 woken thread preempts the spinner
 *   rotate_flag   the movie-player shape: spin + RotateThreadReadyQueue while a
 *                 handler must fire -- without the hint no time ever passes
 *   determinism   two identical runs end at the same cycle, same counts
 *   di_report     a spin under DI is reported (it can never end)
 *   halt          rg_spin_halt reports and parks only its own thread
 *   long_wait     a wait longer than report_cycles is reported once
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eekernel.h"
#include "ps2k.h"
#include "spin.h"

static int g_fail;
static int g_control;
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

static int g_reports[5];
static uint32_t g_report_site;
static void on_report(int what, uint32_t site, uint64_t iters, void *user)
{
    (void)iters;
    (void)user;
    g_reports[what]++;
    g_report_site = site;
}

static void reset(void)
{
    ps2k_config cfg;
    ps2k_default_config(&cfg);
    cfg.stop_at_cycles = 4ull * PS2K_BUSCLK; /* a hang ends as TIME_LIMIT, not a host hang */
    ps2k_init(&cfg);
    rg_spin_config sc;
    rg_spin_default_config(&sc);
    rg_spin_configure(&sc);
    rg_spin_reset();
    rg_spin_set_report_hook(on_report, NULL);
    memset(g_reports, 0, sizeof g_reports);
}

static char g_stack[4][0x800];
static int spawn(void (*fn)(void *), int prio, int k)
{
    struct ThreadParam tp;
    memset(&tp, 0, sizeof tp);
    tp.entry = (void *)fn;
    tp.stack = g_stack[k];
    tp.stackSize = sizeof g_stack[0];
    tp.initPriority = prio;
    int id = CreateThread(&tp);
    if (id >= 0)
        StartThread(id, NULL);
    return id;
}

/* The exact shape stage `spin` emits for `while (!flag) {}`; the control
 * variant is the uninstrumented loop, bounded so the host does not hang. */
#define SPIN_WHILE(cond, site)                                \
    do {                                                      \
        if (g_control) {                                      \
            for (long n_ = 0; (cond) && n_ < 2000000; n_++) { \
            }                                                 \
        } else {                                              \
            while ((cond) && (rg_spin_hint(site), 1)) {       \
            }                                                 \
        }                                                     \
    } while (0)

static uint64_t vbs_time(uint64_t k)
{
    return (k * PS2K_FIELD_SUB + 240ull * PS2K_HSYNC_SUB) / PS2K_SUB;
}

/* ---------------------------------------------------------- handler_flag */
static volatile int hf_flag;
static uint64_t hf_seen_at;
static int hf_handler(int cause)
{
    (void)cause;
    hf_flag = 1;
    return 0;
}
static void main_handler_flag(void *u)
{
    (void)u;
    hf_flag = 0;
    AddIntcHandler(PS2K_INTC_VBLANK_START, hf_handler, 0);
    EnableIntc(PS2K_INTC_VBLANK_START);
    SPIN_WHILE(!hf_flag, 0x00100001u);
    hf_seen_at = ps2k_now();
}
static void t_handler_flag(void)
{
    reset();
    hf_seen_at = 0;
    CHECK_EQ(ps2k_run(main_handler_flag, NULL, 10), PS2K_RUN_MAIN_EXIT);
    CHECK(hf_flag == 1);
    /* left at the first VBLANK_START, within one charge */
    CHECK(hf_seen_at >= vbs_time(0) && hf_seen_at < vbs_time(0) + 64);
    CHECK_EQ(rg_spin_iterations(0x00100001u), (vbs_time(0) + 31) / 32);
}

/* ---------------------------------------------------------- thread_flag */
static volatile int tf_flag;
static uint64_t tf_set_at;
static void tf_worker(void *u)
{
    (void)u;
    DelayThread(1000);
    tf_set_at = ps2k_now();
    tf_flag = 1;
}
static void main_thread_flag(void *u)
{
    (void)u;
    tf_flag = 0;
    spawn(tf_worker, 5, 0); /* higher priority than main: runs, then sleeps */
    SPIN_WHILE(!tf_flag, 0x00100002u);
}
static void t_thread_flag(void)
{
    reset();
    tf_set_at = 0;
    CHECK_EQ(ps2k_run(main_thread_flag, NULL, 10), PS2K_RUN_MAIN_EXIT);
    CHECK(tf_flag == 1);
    CHECK(tf_set_at >= 147456 && tf_set_at < 147456 + 64);
}

/* ---------------------------------------------------------- rotate_flag
 * MoviePlayerShutdown_1d56c0 / VideoDecMain_1d5240: spin + ThreadYield
 * (RotateThreadReadyQueue) at a priority two threads share, waiting for a
 * VBlank.  RotateThreadReadyQueue is a kernel call (delivery point) but no
 * time passes while a thread is ready, so only the hint ends the wait. */
static volatile int rf_flag;
static volatile int rf_peer_iters;
static void rf_peer(void *u)
{
    (void)u;
    while (!rf_flag) {
        rf_peer_iters++;
        RotateThreadReadyQueue(10);
        if (rf_peer_iters > 4000000)
            break;
    }
}
static int rf_handler(int cause)
{
    (void)cause;
    rf_flag = 1;
    return 0;
}
static void main_rotate_flag(void *u)
{
    (void)u;
    rf_flag = 0;
    rf_peer_iters = 0;
    AddIntcHandler(PS2K_INTC_VBLANK_START, rf_handler, 0);
    EnableIntc(PS2K_INTC_VBLANK_START);
    spawn(rf_peer, 10, 1);
    long n = 0;
    if (g_control) {
        while (!rf_flag && n++ < 2000000)
            RotateThreadReadyQueue(10);
    } else {
        while (!rf_flag && (rg_spin_hint(0x00100003u), 1))
            RotateThreadReadyQueue(10);
    }
}
static void t_rotate_flag(void)
{
    reset();
    CHECK_EQ(ps2k_run(main_rotate_flag, NULL, 10), PS2K_RUN_MAIN_EXIT);
    CHECK(rf_flag == 1);
}

/* ---------------------------------------------------------- determinism */
static void t_determinism(void)
{
    uint64_t end[2], iters[2];
    int perturb = g_control;
    g_control = 0; /* both runs use the instrumented loop */
    for (int k = 0; k < 2; k++) {
        reset();
        tf_set_at = 0;
        ps2k_run(main_thread_flag, NULL, 10);
        end[k] = ps2k_now();
        iters[k] = rg_spin_total();
        ps2k_shutdown();
        if (perturb && k == 0) {
            rg_spin_config sc;
            rg_spin_default_config(&sc);
            sc.cycles_per_iter = 33; /* perturb the second run */
            reset();
            rg_spin_configure(&sc);
            tf_set_at = 0;
            ps2k_run(main_thread_flag, NULL, 10);
            end[1] = ps2k_now();
            iters[1] = rg_spin_total();
            ps2k_shutdown();
            break;
        }
    }
    CHECK_EQ(end[0], end[1]);
    CHECK_EQ(iters[0], iters[1]);
    reset(); /* main() shuts down after each test */
}

/* ---------------------------------------------------------- di_report */
static void main_di(void *u)
{
    (void)u;
    hf_flag = 0;
    AddIntcHandler(PS2K_INTC_VBLANK_START, hf_handler, 0);
    EnableIntc(PS2K_INTC_VBLANK_START);
    DIntr();
    for (int n = 0; !hf_flag && n < 100000 && (rg_spin_hint(0x00100004u), 1); n++) {
    }
    EIntr();
}
static void t_di_report(void)
{
    reset();
    ps2k_run(main_di, NULL, 10);
    CHECK_EQ(g_reports[RG_SPIN_DI], 1);
    CHECK_EQ(g_report_site, 0x00100004u);
}

/* ---------------------------------------------------------- halt */
static volatile int halt_after;
static void halt_worker(void *u)
{
    (void)u;
    while ((1) && (rg_spin_halt(0x00100005u), 1)) {
    }
    halt_after = 1; /* never reached */
}
static void main_halt(void *u)
{
    (void)u;
    halt_after = 0;
    spawn(halt_worker, 5, 2);
    DelayThread(100); /* main keeps running after the worker parks */
}
static void t_halt(void)
{
    reset();
    CHECK_EQ(ps2k_run(main_halt, NULL, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_EQ(g_reports[RG_SPIN_HALT], 1);
    CHECK_EQ(halt_after, 0);
}

/* ---------------------------------------------------------- long_wait */
static void t_long_wait(void)
{
    reset();
    rg_spin_config sc;
    rg_spin_default_config(&sc);
    sc.report_cycles = 147456; /* 1 ms; the wait is ~15 ms */
    rg_spin_configure(&sc);
    CHECK_EQ(ps2k_run(main_handler_flag, NULL, 10), PS2K_RUN_MAIN_EXIT);
    CHECK_EQ(g_reports[RG_SPIN_LONG_WAIT], 1);
}

static const struct {
    const char *name;
    void (*fn)(void);
} tests[] = {
    {"handler_flag", t_handler_flag}, {"thread_flag", t_thread_flag},
    {"rotate_flag", t_rotate_flag},   {"determinism", t_determinism},
    {"di_report", t_di_report},       {"halt", t_halt},
    {"long_wait", t_long_wait},
};

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
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
        ps2k_shutdown();
        printf("%-24s %s\n", want_ctl ? ctl : tests[i].name, g_fail == before ? "PASS" : "FAIL");
        ran++;
    }
    if (!ran) {
        fprintf(stderr, "unknown test '%s'\n", argc > 1 ? argv[1] : "");
        return 2;
    }
    return g_fail ? 1 : 0;
}
