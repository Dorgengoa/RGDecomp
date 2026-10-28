/* SPDX-License-Identifier: CC0-1.0
 * Native threads and timing: mode switch + slice 1 service-step registry
 * (docs/NATIVE-THREADS.md).  The frame driver is rg_frame.c. */
#include "rg_threads.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ps2k.h"

/* Model state (saved in port save states with the rest of the statics): a
 * state carries the mode it was made in, like the kernel's service flags. */
static int g_mode = -1;
static int g_services;
static int g_refused;

int rg_threads_mode(void)
{
    if (g_mode < 0) {
        const char *e = getenv("RG_THREADS");
        g_mode = RG_THREADS_NATIVE;
#if !RG_THREADS_ORACLE
        /* native-only build: the EE kernel HLE is not linked (docs/NATIVE-THREADS.md) */
        if (e && *e && strcmp(e, "native"))
            fprintf(stderr, "rg_threads: RG_THREADS=%s: this build has the native kernel only; using native\n", e);
        return g_mode;
#endif
        if (e && !strcmp(e, "hle"))
            g_mode = RG_THREADS_HLE;
        else if (e && !strcmp(e, "service"))
            g_mode = RG_THREADS_SERVICE;
        else if (e && !strcmp(e, "frame"))
            g_mode = RG_THREADS_FRAME;
        else if (e && *e && strcmp(e, "native"))
            fprintf(stderr, "rg_threads: RG_THREADS=%s unknown (native|frame|service|hle); using native\n", e);
    }
    return g_mode;
}

const char *rg_threads_mode_name(int m)
{
    return m == RG_THREADS_NATIVE    ? "native"
           : m == RG_THREADS_FRAME   ? "frame"
           : m == RG_THREADS_SERVICE ? "service"
                                     : "hle";
}
#define mode_name rg_threads_mode_name

void rg_threads_force_mode(int mode, const char *why)
{
    int old = rg_threads_mode();
    if (old == mode)
        return;
#if !RG_THREADS_ORACLE
    fprintf(stderr, "rg_threads: RG_THREADS=%s needed (%s), but this build has the native kernel only\n",
            mode_name(mode), why ? why : "");
    abort();
#endif
    fprintf(stderr, "rg_threads: RG_THREADS=%s -> %s (%s)\n", mode_name(old), mode_name(mode), why ? why : "");
    g_mode = mode;
}

int rg_threads_kernel_native(void) { return rg_threads_mode() == RG_THREADS_NATIVE; }

void rg_frame_report(FILE *f);              /* rg_frame.c */
void rg_frame_stats(rg_threads_stats *out); /* rg_frame.c */
void rg_frame_kernel_stats(ps2k_native_stats *out); /* rg_frame.c */

static void report_at_exit(void)
{
    rg_threads_stats st;
    rg_threads_get_stats(&st);
    fprintf(stderr, "rg_threads: mode=%s services=%d refused=%d steps=%u deferred=%u\n", mode_name(st.mode),
            st.services, st.refused, (unsigned)st.steps, (unsigned)st.deferred);
    if (st.mode == RG_THREADS_NATIVE) {
        ps2k_native_stats ns;
        rg_frame_kernel_stats(&ns); /* copied at the last field end */
        fprintf(stderr,
                "rg_threads: kernel frame-driven: flows=%u flow_switches=%llu passes=%llu delays=%llu "
                "charge_waits=%llu charges_dropped=%llu\n",
                (unsigned)ns.flows, (unsigned long long)ns.flow_switches, (unsigned long long)ns.passes,
                (unsigned long long)ns.delays, (unsigned long long)ns.charge_waits,
                (unsigned long long)ns.charges_dropped);
    }
    rg_frame_report(stderr);
}

/* RG_THREADS_LOG=1: one summary at exit (called from every entry point) */
void rg_threads_log_at_exit(void)
{
    static int reg;
    if (!reg && getenv("RG_THREADS_LOG")) {
        reg = 1;
        atexit(report_at_exit);
    }
}

int rg_threads_service(int tid, int (*wait)(void *arg), void (*step)(void *arg), int allowed,
                       const char *name)
{
    rg_threads_log_at_exit();
#if !RG_THREADS_ORACLE
    (void)tid; (void)wait; (void)step; (void)allowed; (void)name;
    return 0; /* service threads are the HLE's (RG_THREADS=service) */
#else
    if (rg_threads_mode() != RG_THREADS_SERVICE)
        return 0;
    if (!allowed) {
        g_refused++;
        if (getenv("RG_THREADS_LOG"))
            fprintf(stderr, "rg_threads: %s (thread %d) stays an HLE thread (its step could block here)\n",
                    name ? name : "?", tid);
        return 0;
    }
    if (ps2k_thread_set_service(tid, (ps2k_svc_wait_fn)wait, (ps2k_entry_fn)step) != 0) {
        fprintf(stderr, "rg_threads: %s (thread %d) cannot become a service step\n", name ? name : "?", tid);
        g_refused++;
        return 0;
    }
    g_services++;
    if (getenv("RG_THREADS_LOG"))
        fprintf(stderr, "rg_threads: %s (thread %d) runs as a native service step\n", name ? name : "?", tid);
    return 1;
#endif
}

void rg_threads_get_stats(rg_threads_stats *out)
{
    if (!out)
        return;
    memset(out, 0, sizeof *out);
    rg_frame_stats(out);
    out->mode = rg_threads_mode();
    out->services = g_services;
    out->refused += g_refused;
    out->steps = ps2k_svc_step_count();
    out->deferred = ps2k_svc_deferred_count();
}
