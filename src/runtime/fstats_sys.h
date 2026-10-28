/* SPDX-License-Identifier: CC0-1.0
 * Host samples for $RG_FIELD_STATS (fstats_sys.c, docs/PERF-3D.md "Transition stutter"). */
#ifndef RG_FSTATS_SYS_H
#define RG_FSTATS_SYS_H

#include <stdint.h>

#define RG_FSTATS_MAX_THREADS 64

typedef struct rg_fstats_sys {
    double proc_cpu_ms;   /* process user + kernel CPU time, cumulative */
    double main_cpu_ms;   /* the calling thread's */
    uint32_t main_tid;
    uint32_t image_base;  /* the exe's load address (start addresses -> map symbols) */
    uint64_t page_faults; /* cumulative (soft + hard) */
    uint64_t private_kb;  /* committed private bytes now */
    int nthr;             /* threads below (Windows; 0 elsewhere) */
    uint32_t tid[RG_FSTATS_MAX_THREADS];
    uint32_t start[RG_FSTATS_MAX_THREADS]; /* start address (map to a symbol offline) */
    double thr_cpu_ms[RG_FSTATS_MAX_THREADS];
} rg_fstats_sys;

void rg_fstats_sys_refresh(void); /* pick up threads started since the last refresh */
void rg_fstats_sys_sample(rg_fstats_sys *s);

#endif
