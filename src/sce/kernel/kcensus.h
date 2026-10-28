/* SPDX-License-Identifier: CC0-1.0
 * Kernel census recorder (kcensus.c, docs/NATIVE-THREADS.md "Census"). */
#ifndef RG_KCENSUS_H
#define RG_KCENSUS_H

#include <stdint.h>

#include "rg_threads_oracle.h" /* RG_NATIVE_ONLY: no census recorder (docs/NATIVE-THREADS.md) */

#ifdef __cplusplus
extern "C" {
#endif

#if RG_THREADS_ORACLE
extern int rg_kcensus_on; /* RG_KCENSUS set: one branch per wrapper when off */
int  rg_kcensus_open(const char *path);
void rg_kcensus_ev(const char *kind, const void *ra, int32_t a, int32_t b, int32_t c, const void *fn);
void rg_kcensus_flush(void);

#define RG_KC(kind, a, b, c, fn) \
    do { if (rg_kcensus_on) rg_kcensus_ev((kind), __builtin_return_address(0), (a), (b), (c), (const void *)(fn)); } while (0)
#else
#define rg_kcensus_on 0
static inline void rg_kcensus_ev(const char *kind, const void *ra, int32_t a, int32_t b, int32_t c, const void *fn)
{
    (void)kind; (void)ra; (void)a; (void)b; (void)c; (void)fn;
}
#define RG_KC(kind, a, b, c, fn) do { } while (0)
#endif

#ifdef __cplusplus
}
#endif
#endif
