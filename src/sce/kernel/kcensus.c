/* SPDX-License-Identifier: CC0-1.0
 * Kernel census recorder (docs/NATIVE-THREADS.md "Census").
 *
 * RG_KCENSUS=<path> writes one TSV row per EE-kernel event the game causes:
 * every SDK kernel call made through src/sce/kernel/eekernel.c (with the
 * caller's return address) plus the kernel-side events of the census tap
 * (thread switches, handler and alarm calls, kernel-private waits, timer
 * reads, VBlank edges).  tools/native/thread_census.py names the addresses
 * with rg-game.map and summarises per thread / semaphore / handler.
 *
 * Measurement only: it never makes a kernel call (it peeks), so a run with
 * the census on is the same run.  Host state for save states
 * (src/savestate/ss_map.c): a loaded run records from the load on.
 *
 * Row: vbl tid prio isr kind a b c fn_rva ra_rva   (rva = address - image base, hex)
 * Do not include eekernel.h here (it clashes with <windows.h> names). */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ps2k.h"
#include "kcensus.h"

#if RG_THREADS_ORACLE /* the whole recorder (RG_NATIVE_ONLY: compiled out) */

int rg_kcensus_on;
static FILE *g_f;
static char g_buf[1 << 16];

#if defined(_WIN32)
extern char __ImageBase; /* COFF: the image base */
#define IMG_BASE ((uintptr_t)&__ImageBase)
#else
#define IMG_BASE ((uintptr_t)0)
#endif

static unsigned long rva(const void *p) { return p ? (unsigned long)((uintptr_t)p - IMG_BASE) : 0ul; }

static void tap(int kind, int32_t a, int32_t b, const void *fn)
{
    static const char *const names[] = {"?", "SW", "HC", "AC", "KW", "T0", "VB", "RH"};
    rg_kcensus_ev(kind >= 1 && kind <= 7 ? names[kind] : "?", NULL, a, b, 0, fn);
}

static void close_census(void)
{
    if (g_f) {
        fflush(g_f);
        fclose(g_f);
        g_f = NULL;
    }
    rg_kcensus_on = 0;
}

int rg_kcensus_open(const char *path)
{
    if (g_f || !path || !*path)
        return g_f ? 0 : -1;
    g_f = fopen(path, "w");
    if (!g_f) {
        fprintf(stderr, "kcensus: cannot write %s\n", path);
        return -1;
    }
    setvbuf(g_f, g_buf, _IOFBF, sizeof g_buf);
    fprintf(g_f, "#kcensus 1\tbase=%lx\n#vbl\ttid\tprio\tisr\tkind\ta\tb\tc\tfn\tra\n",
            (unsigned long)IMG_BASE);
    rg_kcensus_on = 1;
    ps2k_set_census_tap(tap);
    atexit(close_census);
    return 0;
}

/* RG_KCENSUS from the environment, before main (no wiring in the exe). */
__attribute__((constructor)) static void kcensus_env(void)
{
    const char *p = getenv("RG_KCENSUS");
    if (p && *p)
        rg_kcensus_open(p);
}

void rg_kcensus_ev(const char *kind, const void *ra, int32_t a, int32_t b, int32_t c, const void *fn)
{
    if (!g_f)
        return;
    fprintf(g_f, "%llu\t%d\t%d\t%d\t%s\t%ld\t%ld\t%ld\t%lx\t%lx\n",
            (unsigned long long)ps2k_vblank_count(), ps2k_get_thread_id(), ps2k_peek_priority(),
            ps2k_in_handler(), kind, (long)a, (long)b, (long)c, rva(fn), rva(ra));
}

void rg_kcensus_flush(void)
{
    if (g_f)
        fflush(g_f);
}
#endif /* RG_THREADS_ORACLE */
