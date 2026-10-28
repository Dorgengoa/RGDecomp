/* SPDX-License-Identifier: CC0-1.0
 * EE FPU float operations as PCSX2 runs them (docs/BRINGUP.md "Retail parity"); linked into
 * every game object by tools/parity/eediv/eediv_cc.py (llvm-link, always inlined) in place
 * of the IR's fadd / fsub / fdiv on floats.  The game's MXCSR is round toward zero + FTZ +
 * DAZ (RG_EE_FPU=chop, src/native/threads/rg_nk_internal.h); fmul and the conversions use
 * it as they are.  Verified against retail: the retail fdlibm sinf / cosf / atan2f written
 * in C and compiled with these operations reproduce 113,903 of 113,903 calls probed on PCSX2.
 *
 *  - ADD / SUB: the operand with the smaller exponent loses the mantissa bits the EE adder
 *    shifts out except one guard bit (mask 0xFFFFFFFF << (diff - 1)); a difference of 25 or
 *    more leaves only its sign; then the add under the MXCSR.
 *  - DIV: rounded to nearest (PCSX2's EE division rounding mode).  Exact without an MXCSR
 *    switch on the common path: under chop q = RTZ(a / b); r = a - q*b is exact in double, so
 *    round to nearest is q or q one ulp away from zero (ties to even).
 * With the MXCSR at round to nearest (RG_EE_FPU unset) the helpers are plain IEEE ops. */
#include <stdint.h>
#include <string.h>
#include <xmmintrin.h>

#define EE_INLINE __attribute__((always_inline)) inline
/* the three entry points: C linkage, emitted in this TU (used) as linkonce_odr / comdat, so
 * every game object can carry its own always-inlined copy */
#define EE_ENTRY extern "C" __attribute__((always_inline, used)) inline

static EE_INLINE uint32_t ee_u(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }
static EE_INLINE float ee_f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }

static EE_INLINE void ee_align(float *a, float *b)
{
    uint32_t ua = ee_u(*a), ub = ee_u(*b);
    int d = (int)((ua >> 23) & 0xFF) - (int)((ub >> 23) & 0xFF);
    if (d < 0) {
        uint32_t t = ua;
        ua = ub;
        ub = t;
        d = -d;
        if (d >= 25)
            ub &= 0x80000000u;
        else if (d > 0)
            ub &= 0xFFFFFFFFu << (d - 1);
        *a = ee_f(ub);
        return;
    }
    if (d >= 25)
        ub &= 0x80000000u;
    else if (d > 0)
        ub &= 0xFFFFFFFFu << (d - 1);
    *b = ee_f(ub);
}

EE_ENTRY float rg_ee_addf(float a, float b)
{
    ee_align(&a, &b);
    return a + b;
}

EE_ENTRY float rg_ee_subf(float a, float b)
{
    ee_align(&a, &b);
    return a - b;
}

__attribute__((noinline)) static float ee_div_slow(float a, float b)
{
    unsigned o = _mm_getcsr();
    _mm_setcsr(o & ~0x6000u);
    __asm__ volatile("" : "+x"(a), "+x"(b));
    float q = a / b;
    __asm__ volatile("" : "+x"(q));
    _mm_setcsr(o);
    return q;
}

EE_ENTRY float rg_ee_divf(float a, float b)
{
    float q = a / b;
    uint32_t uq = ee_u(q), aq = uq & 0x7FFFFFFFu;
    if (aq < 0x00800000u || aq >= 0x7F7FFFFFu || !(_mm_getcsr() & 0x6000u))
        return (_mm_getcsr() & 0x6000u) ? ee_div_slow(a, b) : q;
    double r = (double)a - (double)q * (double)b;            /* exact */
    double ulp = (double)ee_f(aq + 1) - (double)ee_f(aq);    /* exact */
    double half = ulp * 0.5 * (double)ee_f(ee_u(b) & 0x7FFFFFFFu);
    double ar = r < 0 ? -r : r;
    if (ar > half || (ar == half && (uq & 1)))
        uq += 1;                                               /* away from zero */
    return ee_f(uq);
}
