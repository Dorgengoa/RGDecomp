/* SPDX-License-Identifier: CC0-1.0
 *
 * rg_sqrtf_rn: single-precision square root ROUNDED TO NEAREST whatever the
 * MXCSR rounding mode (x64 build only; docs/X64-PLAN.md section 0.7).
 *
 * Why: game code runs under the guest MXCSR (round toward zero, FTZ, DAZ:
 * rg_nk_internal.h nk_guest_csr).  On i686 every float sqrt of game code is a
 * call to the CRT's sqrtf (libcpmt xfprec: x87 fsqrt + fstps under the x87
 * control word, which stays round-to-nearest), so i686 gets the correctly
 * rounded NEAREST result, and denormal inputs are not flushed (x87 has no DAZ).
 * On x64 clang inlines `sqrtss`, which rounds toward zero under the guest
 * MXCSR: 1 ulp lower in about half the cases (the x64 audio hash divergence at
 * field 24,824: the emitter-sound pan of GameSceneEmitterSoundsUpdate_1cfde0
 * changed by 1 ulp through VecDistance_13d3d0 -> rg_vu_sqrtf).
 *
 * How: sqrt in double (any rounding mode: sqrt of a float is never within
 * 2^-53 relative of a float rounding midpoint unless exact, so truncation to
 * 53 bits cannot cross one), then round the double to 24 bits by integer
 * arithmetic (half up at bit 29), which is exact and mode-independent.
 * Freestanding (force-included into game TUs with their own declarations).
 */
#ifndef RG_PORT_SQRTF_RN_H
#define RG_PORT_SQRTF_RN_H

static inline float rg_sqrtf_rn(float x)
{
    unsigned int b;
    unsigned long long u;
    double d;
    __builtin_memcpy(&b, &x, 4);
    if ((b & 0x7F800000u) == 0 && (b & 0x007FFFFFu) != 0) {
        /* denormal: build the exact double by hand (cvtss2sd under DAZ gives 0) */
        d = (double)(int)(b & 0x007FFFFFu) * 0x1p-149;
        if (b & 0x80000000u)
            d = -d;
    } else {
        d = (double)x;
    }
    d = __builtin_sqrt(d);
    __builtin_memcpy(&u, &d, 8);
    if (d == 0.0 || (u & 0x7FF0000000000000ull) == 0x7FF0000000000000ull)
        return (float)d; /* +-0, inf, NaN: exact */
    u = (u + 0x10000000ull) & ~0x1FFFFFFFull;
    __builtin_memcpy(&d, &u, 8);
    return (float)d; /* exact: 24 significant bits, in the normal float range */
}

#endif
