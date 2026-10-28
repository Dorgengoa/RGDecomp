/* SPDX-License-Identifier: CC0-1.0 */
/* Game memory the walkers read in place; poison mode (nr_mem.h). */
#include "nr_mem.h"

#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

int g_nr_poison_mode;   /* set by nr_poison_mode() (first frame begin); 0 before */
static volatile long g_epoch = 1;
static struct {
    uint64_t rejected, queries, poisoned_qw, hits;
    uint32_t first_a;
    char first_who[24];
} g_ms;

#ifdef _WIN32
/* per thread: the readable regions seen since the last frame (memory freed in between is
 * re-queried; a region freed within one frame is the one case this cannot see) */
#define NR_RGN 24
static _Thread_local struct { long epoch; int n; uintptr_t lo[NR_RGN], hi[NR_RGN]; } t_rg;

static int readable_at(uintptr_t a)
{
    MEMORY_BASIC_INFORMATION mi;
    int i;
    if (t_rg.epoch != g_epoch) { t_rg.epoch = g_epoch; t_rg.n = 0; }
    for (i = 0; i < t_rg.n; i++)
        if (a >= t_rg.lo[i] && a < t_rg.hi[i]) return 1;
    g_ms.queries++;
    if (!VirtualQuery((const void *)a, &mi, sizeof mi)) return 0;
    if (mi.State != MEM_COMMIT || (mi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) ||
        !(mi.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ |
                        PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
        return 0;
    i = t_rg.n < NR_RGN ? t_rg.n++ : (int)(a >> 12) % NR_RGN;
    t_rg.lo[i] = (uintptr_t)mi.BaseAddress;
    t_rg.hi[i] = (uintptr_t)mi.BaseAddress + mi.RegionSize;
    return 1;
}
#endif

const uint8_t *nr_game_ptr(uint32_t a, uint32_t bytes)
{
    if (a < 0x10000u || (a & 0x80000000u)) return NULL;   /* null / scratchpad: not a static packet */
#ifdef _WIN32
    if (!readable_at(a) || (bytes > 1 && !readable_at((uintptr_t)a + bytes - 1))) {
        g_ms.rejected++;
        return NULL;
    }
#else
    (void)bytes;
#endif
    return (const uint8_t *)(uintptr_t)a;
}

void nr_game_mem_frame(void)
{
#ifdef _WIN32
    InterlockedIncrement(&g_epoch);
#endif
}

int nr_poison_mode(void)
{
    static int m = -1;
    if (m < 0) {
        const char *e = getenv("RG_NR_POISON");
        m = e && e[0] ? atoi(e) : 0;
        if (m < 0) m = 0;
        g_nr_poison_mode = m;
        if (m) fprintf(stderr, "native render: RG_NR_POISON=%d: dead frame packet stacks are poisoned (diagnostic run)\n", m);
    }
    return m;
}

void nr_poison_stack(uint32_t base, uint32_t qwords)
{
    static const uint32_t q[4] = { NR_POISON_W0, NR_POISON_W1, NR_POISON_W2, NR_POISON_W3 };
    uint8_t *p;
    uint32_t i;
    if (!nr_poison_mode() || !qwords || !nr_game_ptr(base, qwords * 16u)) return;
    p = (uint8_t *)(uintptr_t)base;
    for (i = 0; i < qwords; i++) memcpy(p + i * 16u, q, 16);
    g_ms.poisoned_qw += qwords;
}

int nr_poisoned(const uint8_t *p, const char *who, uint32_t a)
{
    uint32_t w[4];
    memcpy(w, p, 16);
    if (w[0] != NR_POISON_W0 || w[1] != NR_POISON_W1 || w[2] != NR_POISON_W2 || w[3] != NR_POISON_W3) return 0;
    if (++g_ms.hits <= 16)
        fprintf(stderr, "nr: POISON: %s read a dead packet at %08X (a pointer into a frame packet stack "
                        "the game has reset; docs/NATIVE-RENDER.md \"Remembered packets\")\n", who, a);
    if (g_ms.hits == 1) {
        g_ms.first_a = a;
        strncpy(g_ms.first_who, who, sizeof g_ms.first_who - 1);
    }
    if (g_nr_poison_mode >= 2) {
        fprintf(stderr, "nr: POISON: RG_NR_POISON=2: abort\n");
        fflush(stderr);
        abort();
    }
    return 1;
}

void nr_mem_stats(FILE *f)
{
    if (!f) return;
    if (g_ms.rejected || g_nr_poison_mode)
        fprintf(f, "native render game memory: %llu walker reads refused (not readable memory), %llu region queries; "
                   "poison mode %d: %llu qwords poisoned, %llu poisoned reads%s%s%s\n",
                (unsigned long long)g_ms.rejected, (unsigned long long)g_ms.queries, g_nr_poison_mode,
                (unsigned long long)g_ms.poisoned_qw, (unsigned long long)g_ms.hits,
                g_ms.hits ? " (first: " : "", g_ms.hits ? g_ms.first_who : "", g_ms.hits ? ")" : "");
}
