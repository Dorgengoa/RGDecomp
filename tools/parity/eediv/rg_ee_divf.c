/* SPDX-License-Identifier: CC0-1.0
 * PROTOTYPE (not built; docs/BRINGUP.md 2026-10-19 (c) open item (a)).
 * Float division as retail PCSX2 does it: EE FPU add/sub/mul round toward zero (the game's
 * MXCSR under RG_EE_FPU=chop), but DIV.S rounds to nearest (PCSX2's default EE division
 * rounding mode).  eediv_cc.py rewrites every `fdiv float` of a game object into a call
 * here.  Exact without touching MXCSR on the common path: under chop q = RTZ(a / b); the
 * remainder r = a - q*b is exact in double (q*b has 48 significant bits), the exact quotient
 * is q + r/b with |r/b| < ulp(q), so round to nearest = q, or q one ulp away from zero when
 * |r| > |b| * ulp(q) / 2 (ties: to even).  Zero / denormal / overflow results and the IEEE
 * mode take the MXCSR switch. */
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <string.h>
#include <xmmintrin.h>

static float slow(float a, float b)
{
    unsigned o = _mm_getcsr();
    _mm_setcsr(o & ~0x6000u);
    __asm__ volatile("" : "+x"(a), "+x"(b));
    float q = a / b;
    __asm__ volatile("" : "+x"(q));
    _mm_setcsr(o);
    return q;
}

float rg_ee_divf(float a, float b)
{
    float q = a / b;
    float aq = fabsf(q);
    if (!(_mm_getcsr() & 0x6000u))
        return q;                          /* IEEE mode: already round to nearest */
    if (!(aq >= FLT_MIN && aq < FLT_MAX))
        return slow(a, b);
    double r = (double)a - (double)q * (double)b;          /* exact */
    float up = nextafterf(aq, INFINITY);
    double half = ((double)up - (double)aq) * 0.5 * fabs((double)b);   /* exact */
    double ar = fabs(r);
    uint32_t bits;
    memcpy(&bits, &q, 4);
    if (ar > half || (ar == half && (bits & 1)))
        bits += 1;                         /* one ulp away from zero (sign-magnitude) */
    memcpy(&q, &bits, 4);
    return q;
}

/* EE FPU ADD / SUB as PCSX2 runs them (iFPU FPU_ADD_SUB): the operand with the smaller
 * exponent loses the mantissa bits the EE adder shifts out (all but one guard bit:
 * mask 0xFFFFFFFF << (diff - 1)); a difference of 25 or more leaves only its sign; then
 * an SSE add under the round-toward-zero MXCSR. */
static inline float ee_align(float a, float *b)
{
    uint32_t ua, ub;
    memcpy(&ua, &a, 4);
    memcpy(&ub, b, 4);
    int d = (int)((ua >> 23) & 0xFF) - (int)((ub >> 23) & 0xFF);
    if (d >= 25)
        ub &= 0x80000000u;
    else if (d > 0)
        ub &= 0xFFFFFFFFu << (d - 1);
    memcpy(b, &ub, 4);
    return a;
}
float rg_ee_addf(float a, float b)
{
    uint32_t ua, ub;
    memcpy(&ua, &a, 4);
    memcpy(&ub, &b, 4);
    if (((ua >> 23) & 0xFF) >= ((ub >> 23) & 0xFF))
        ee_align(a, &b);
    else
        ee_align(b, &a);
    return a + b;
}
float rg_ee_subf(float a, float b)
{
    uint32_t ua, ub;
    memcpy(&ua, &a, 4);
    memcpy(&ub, &b, 4);
    if (((ua >> 23) & 0xFF) >= ((ub >> 23) & 0xFF))
        ee_align(a, &b);
    else
        ee_align(b, &a);
    return a - b;
}
