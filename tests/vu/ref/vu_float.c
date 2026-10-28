/* SPDX-License-Identifier: CC0-1.0 */
/* VU floating point: no Inf/NaN/denormals, round toward zero, saturation.
 *
 * A VU single is sign/8-bit exponent/23-bit fraction like IEEE, but exponent
 * 255 is an ordinary binade (max magnitude 0x7FFFFFFF ~ 3.4028e38 * 2), an
 * exponent of 0 reads as zero whatever the fraction, results that overflow
 * saturate to +-0x7FFFFFFF (O flag), and results below 2^-126 flush to +-0
 * (U and Z flags).  Arithmetic is done in double (exact for one product of two
 * 24-bit mantissas, and for most sums) and then chopped to 24 bits. */
#include <math.h>

#include "vu.h"

enum { C_Z = 1, C_S = 2, C_U = 4, C_O = 8 };

double vu_f_to_d(uint32_t a)
{
    uint32_t e = (a >> 23) & 0xFF;
    double v;
    if (!e) return (a >> 31) ? -0.0 : 0.0;
    v = ldexp(1.0 + (double)(a & 0x7FFFFF) / 8388608.0, (int)e - 127);
    return (a >> 31) ? -v : v;
}

uint32_t vu_f_from_d(double v, unsigned *cond)
{
    uint32_t s = signbit(v) ? 0x80000000u : 0;
    double a = fabs(v), m;
    unsigned c = s ? C_S : 0;
    int ex, E;
    uint32_t frac;
    if (a == 0.0) {
        if (cond) *cond = c | C_Z;
        return s;
    }
    m = frexp(a, &ex); /* a = m * 2^ex, m in [0.5, 1) */
    E = ex + 126;
    if (E >= 256) {
        if (cond) *cond = c | C_O;
        return s | 0x7FFFFFFFu;
    }
    if (E <= 0) {
        if (cond) *cond = c | C_U | C_Z;
        return s;
    }
    frac = (uint32_t)((m * 2.0 - 1.0) * 8388608.0); /* chop */
    if (cond) *cond = c;
    return s | ((uint32_t)E << 23) | frac;
}

uint32_t vu_f_add(uint32_t a, uint32_t b, unsigned *cond)
{
    return vu_f_from_d(vu_f_to_d(a) + vu_f_to_d(b), cond);
}

uint32_t vu_f_sub(uint32_t a, uint32_t b, unsigned *cond)
{
    return vu_f_from_d(vu_f_to_d(a) - vu_f_to_d(b), cond);
}

uint32_t vu_f_mul(uint32_t a, uint32_t b, unsigned *cond)
{
    return vu_f_from_d(vu_f_to_d(a) * vu_f_to_d(b), cond);
}

uint32_t vu_ftoi(uint32_t a, int frac_bits)
{
    double v = ldexp(vu_f_to_d(a), frac_bits);
    if (v >= 2147483647.0) return 0x7FFFFFFFu;
    if (v <= -2147483648.0) return 0x80000000u;
    return (uint32_t)(int32_t)v; /* C conversion truncates toward zero */
}

uint32_t vu_itof(uint32_t a, int frac_bits)
{
    return vu_f_from_d(ldexp((double)(int32_t)a, -frac_bits), 0);
}

int vu_f_cmp(uint32_t a, uint32_t b)
{
    /* sign-magnitude order on the raw bits (no NaN on the VU) */
    int64_t ka = (a & 0x80000000u) ? -(int64_t)(a & 0x7FFFFFFFu) : (int64_t)a;
    int64_t kb = (b & 0x80000000u) ? -(int64_t)(b & 0x7FFFFFFFu) : (int64_t)b;
    if ((a & 0x7F800000u) == 0) ka = 0; /* denormals / zeros compare equal */
    if ((b & 0x7F800000u) == 0) kb = 0;
    return ka < kb ? -1 : ka > kb ? 1 : 0;
}
