/* SPDX-License-Identifier: CC0-1.0
 * The caller's x87 control word and MXCSR controls kept around a driver call (gfxperf7 / gfxperf8,
 * docs/NATIVE-RENDER.md "GPU throughput 6" / "GPU throughput 7").
 *
 * The 32-bit NVIDIA Vulkan driver's pipeline compiler leaves the calling thread's x87 control word
 * at round toward zero (0x027F -> 0x0E7F); the i686 UCRT's double libm behind the game's Sin / Cos /
 * Tan / Atan wrappers (src/crt/crt_math.c) runs on the x87, so a driver call on the EE thread
 * changed the game's camera matrices by ulps.  NR_FPU_KEEP("what") at the top of a scope saves the
 * x87 control word and MXCSR and restores them at every exit of the scope (MXCSR status flags are
 * left as the callee left them).  Header only, C and C++; a no-op off i686.
 *
 *   RG_VK_FPU_KEEP=0   do not restore (measurement: the behaviour before)
 *   RG_FPU_KEEP_LOG=1  print one stderr line per guarded call that changed the control word or the
 *                      MXCSR controls: "fpukeep: WHAT tid T cw A -> B mxcsr C -> D" (measurement)
 */
#ifndef NR_FPUKEEP_H
#define NR_FPUKEEP_H

#if defined(__i386__) || defined(_M_IX86)
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>

typedef struct nr_fpukeep {
    const char *what;
    unsigned csr;
    unsigned short cw;
    unsigned char on, log;
} nr_fpukeep;

static inline unsigned long nr_fpukeep_tid(void)
{
#ifdef _WIN32
    unsigned long t;
    __asm__ volatile("movl %%fs:0x24, %0" : "=r"(t));   /* the TEB's thread id */
    return t;
#else
    return 0;
#endif
}

static inline nr_fpukeep nr_fpukeep_enter(const char *what)
{
    static int en = -1, lg = -1;
    nr_fpukeep k;
    if (en < 0) { const char *e = getenv("RG_VK_FPU_KEEP"); en = !(e && e[0] == '0'); }
    if (lg < 0) { const char *e = getenv("RG_FPU_KEEP_LOG"); lg = e ? atoi(e) : 0; }
    k.what = what;
    k.on = (unsigned char)en;
    k.log = (unsigned char)lg;
    k.cw = 0;
    k.csr = 0;
    if (!k.on && !k.log) return k;
    __asm__ volatile("fnstcw %0" : "=m"(k.cw));
    k.csr = _mm_getcsr();
    return k;
}

static inline void nr_fpukeep_leave(const nr_fpukeep *k)
{
    unsigned short c;
    unsigned m;
    if (!k->on && !k->log) return;
    __asm__ volatile("fnstcw %0" : "=m"(c));
    m = _mm_getcsr();
    if (k->log && (k->log >= 2 || c != k->cw || ((m ^ k->csr) & ~0x3Fu)))
        fprintf(stderr, "fpukeep: %s tid %lu cw %04x -> %04x mxcsr %08x -> %08x\n", k->what, nr_fpukeep_tid(),
                (unsigned)k->cw, (unsigned)c, k->csr, m);
    if (!k->on) return;
    if (c != k->cw) __asm__ volatile("fldcw %0" : : "m"(k->cw));
    if ((m ^ k->csr) & ~0x3Fu) _mm_setcsr((m & 0x3Fu) | (k->csr & ~0x3Fu));
}

#define NR_FPU_KEEP_CAT2(a, b) a##b
#define NR_FPU_KEEP_CAT(a, b) NR_FPU_KEEP_CAT2(a, b)
#define NR_FPU_KEEP(what) \
    nr_fpukeep NR_FPU_KEEP_CAT(nr_fpukeep_, __LINE__) __attribute__((cleanup(nr_fpukeep_leave), unused)) = nr_fpukeep_enter(what)
#else
#define NR_FPU_KEEP(what) ((void)0)
#endif

#endif
