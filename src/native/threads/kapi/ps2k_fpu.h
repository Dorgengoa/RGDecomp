/* SPDX-License-Identifier: CC0-1.0
 * Host float scope inside a kernel step (docs/BRINGUP.md "Retail parity", EE FPU mode).
 *
 * In the EE mode (default since 2026-10-24; RG_EE_FPU=ieee turns it off) the kernel step (game flows, handler chains, alarms, the frame
 * driver's driven steps) runs with MXCSR = round toward zero + FTZ + DAZ, the retail EE
 * rounding (src/native/threads/rg_nk_internal.h).  Host services that game code calls
 * synchronously inside the step (the native renderer's kick, the audio commands, the
 * layout transform, ...) put PS2K_FPU_HOST_SCOPE first in their entry function: it
 * switches to the host's round to nearest (no FTZ/DAZ) only when the caller is in the EE
 * mode and restores the caller's MXCSR at every exit of the scope.  Header only, no link
 * dependency; a no-op off x86 and when the EE mode is off (RG_EE_FPU=ieee).
 *
 * Census of the boundaries: tools/parity/fpboundary.py EXE.
 */
#ifndef PS2K_FPU_H
#define PS2K_FPU_H

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#include <xmmintrin.h>
static inline unsigned ps2k_fpu_host_enter(void)
{
    unsigned o = _mm_getcsr();
    if (o & 0x6000u) {           /* rounding control != nearest: the EE mode */
        _mm_setcsr(o & ~0xE040u);
        __asm__ volatile("" ::: "memory");
    }
    return o;
}
static inline void ps2k_fpu_host_leave(const unsigned *o)
{
    if (*o & 0x6000u) {
        __asm__ volatile("" ::: "memory");
        _mm_setcsr(*o);
    }
}
#define PS2K_FPU_HOST_SCOPE \
    unsigned ps2k_fpu_saved_ __attribute__((cleanup(ps2k_fpu_host_leave), unused)) = ps2k_fpu_host_enter()
#else
#define PS2K_FPU_HOST_SCOPE ((void)0)
#endif

#endif
