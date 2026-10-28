/* SPDX-License-Identifier: CC0-1.0 */
/* VU floating point: no Inf/NaN/denormals, round toward zero, saturation.
 *
 * A VU single is sign/8-bit exponent/23-bit fraction like IEEE, but exponent
 * 255 is an ordinary binade (max magnitude 0x7FFFFFFF ~ 3.4028e38 * 2), an
 * exponent of 0 reads as zero whatever the fraction, results that overflow
 * saturate to +-0x7FFFFFFF (O flag), and results below 2^-126 flush to +-0
 * (U and Z flags).  Arithmetic is done in double (exact for one product of two
 * 24-bit mantissas, and for most sums) and then chopped to 24 bits.
 *
 * The conversions are bit manipulation (vu_float_inl.h; docs/VU.md
 * "Performance"); tests/vu/vu_float_ref.c keeps the original ldexp/frexp
 * formulation and rg-vu-float-diff proves the two agree bit for bit. */
#include <math.h>

#include "vu.h"
#include "vu_decode.h"
#include "vu_float_inl.h"

double vu_f_to_d(uint32_t a) { return vuf_to_d(a); }

uint32_t vu_f_from_d(double v, unsigned *cond)
{
    unsigned c;
    uint32_t r = vuf_from_d(v, &c);
    if (cond) *cond = c;
    return r;
}

uint32_t vu_f_add(uint32_t a, uint32_t b, unsigned *cond)
{
    unsigned c;
    uint32_t r = vuf_add(a, b, &c);
    if (cond) *cond = c;
    return r;
}

uint32_t vu_f_sub(uint32_t a, uint32_t b, unsigned *cond)
{
    unsigned c;
    uint32_t r = vuf_sub(a, b, &c);
    if (cond) *cond = c;
    return r;
}

uint32_t vu_f_mul(uint32_t a, uint32_t b, unsigned *cond)
{
    unsigned c;
    uint32_t r = vuf_mul(a, b, &c);
    if (cond) *cond = c;
    return r;
}

uint32_t vu_ftoi(uint32_t a, int frac_bits) { return vuf_ftoi(a, frac_bits); }

uint32_t vu_itof(uint32_t a, int frac_bits) { return vuf_itof(a, frac_bits); }

int vu_f_cmp(uint32_t a, uint32_t b) { return vuf_cmp(a, b); }

/* EFU result (P) of a lower op on fs (the libm functions are unchanged) */
uint32_t vu_efu(int op, const uint32_t s[4], int fsf)
{
    double x = vuf_to_d(s[0]), y = vuf_to_d(s[1]), z = vuf_to_d(s[2]);
    double w = vuf_to_d(s[3]), f = vuf_to_d(s[fsf]), r;
    unsigned c;
    switch (op) {
    case VU_L_ESADD: r = x * x + y * y + z * z; break;
    case VU_L_ERSADD: r = 1.0 / (x * x + y * y + z * z); break;
    case VU_L_ELENG: r = sqrt(x * x + y * y + z * z); break;
    case VU_L_ERLENG: r = 1.0 / sqrt(x * x + y * y + z * z); break;
    case VU_L_EATANxy: r = atan(y / x); break;
    case VU_L_EATANxz: r = atan(z / x); break;
    case VU_L_ESUM: r = x + y + z + w; break;
    case VU_L_ESQRT: r = sqrt(fabs(f)); break;
    case VU_L_ERSQRT: r = 1.0 / sqrt(fabs(f)); break;
    case VU_L_ERCPR: r = 1.0 / f; break;
    case VU_L_ESIN: r = sin(f); break;
    case VU_L_EATAN: r = atan(f); break;
    case VU_L_EEXP: r = exp(-f); break;
    default: r = 0; break;
    }
    if (r != r) r = 0;                        /* 0/0 style cases */
    if (isinf(r)) r = r > 0 ? 1e300 : -1e300; /* saturates in from_d */
    return vuf_from_d(r, &c);
}

/* FDIV: returns Q, sets *fl to VU_ST_I / VU_ST_D */
uint32_t vu_fdiv(int op, uint32_t a, uint32_t b, uint32_t *fl)
{
    double da = vuf_to_d(a), db = vuf_to_d(b);
    uint32_t sgn = (a ^ b) & 0x80000000u;
    unsigned c;
    *fl = 0;
    if (op == VU_L_SQRT) {
        if (db < 0) *fl = VU_ST_I;
        return vuf_from_d(sqrt(fabs(db)), &c) & 0x7FFFFFFFu;
    }
    if (op == VU_L_RSQRT) {
        if (db < 0) *fl = VU_ST_I;
        if (db == 0) {
            *fl |= da == 0 ? VU_ST_I : VU_ST_D;
            return (a & 0x80000000u) | 0x7FFFFFFFu;
        }
        return vuf_from_d(da / sqrt(fabs(db)), &c);
    }
    if (db == 0) {
        *fl = da == 0 ? VU_ST_I : VU_ST_D;
        return sgn | 0x7FFFFFFFu;
    }
    return vuf_from_d(da / db, &c);
}
