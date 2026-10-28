/* SPDX-License-Identifier: CC0-1.0 */
/* REFERENCE COPY (tests only) of src/ps2/vu/vu_float.c as it was before the
 * bit-manipulation rewrite (docs/VU.md "Performance"); rg-vu-float-diff
 * compares the live helpers against it.  Do not optimise.
 *
 * VU floating point: no Inf/NaN/denormals, round toward zero, saturation.
 *
 * A VU single is sign/8-bit exponent/23-bit fraction like IEEE, but exponent
 * 255 is an ordinary binade (max magnitude 0x7FFFFFFF ~ 3.4028e38 * 2), an
 * exponent of 0 reads as zero whatever the fraction, results that overflow
 * saturate to +-0x7FFFFFFF (O flag), and results below 2^-126 flush to +-0
 * (U and Z flags).  Arithmetic is done in double (exact for one product of two
 * 24-bit mantissas, and for most sums) and then chopped to 24 bits. */
#include <math.h>

#include <stdint.h>
#include "vu_float_ref.h"

enum { C_Z = 1, C_S = 2, C_U = 4, C_O = 8 };

double ref_f_to_d(uint32_t a)
{
    uint32_t e = (a >> 23) & 0xFF;
    double v;
    if (!e) return (a >> 31) ? -0.0 : 0.0;
    v = ldexp(1.0 + (double)(a & 0x7FFFFF) / 8388608.0, (int)e - 127);
    return (a >> 31) ? -v : v;
}

uint32_t ref_f_from_d(double v, unsigned *cond)
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

uint32_t ref_f_add(uint32_t a, uint32_t b, unsigned *cond)
{
    return ref_f_from_d(ref_f_to_d(a) + ref_f_to_d(b), cond);
}

uint32_t ref_f_sub(uint32_t a, uint32_t b, unsigned *cond)
{
    return ref_f_from_d(ref_f_to_d(a) - ref_f_to_d(b), cond);
}

uint32_t ref_f_mul(uint32_t a, uint32_t b, unsigned *cond)
{
    return ref_f_from_d(ref_f_to_d(a) * ref_f_to_d(b), cond);
}

uint32_t ref_ftoi(uint32_t a, int frac_bits)
{
    double v = ldexp(ref_f_to_d(a), frac_bits);
    if (v >= 2147483647.0) return 0x7FFFFFFFu;
    if (v <= -2147483648.0) return 0x80000000u;
    return (uint32_t)(int32_t)v; /* C conversion truncates toward zero */
}

uint32_t ref_itof(uint32_t a, int frac_bits)
{
    return ref_f_from_d(ldexp((double)(int32_t)a, -frac_bits), 0);
}

int ref_f_cmp(uint32_t a, uint32_t b)
{
    /* sign-magnitude order on the raw bits (no NaN on the VU) */
    int64_t ka = (a & 0x80000000u) ? -(int64_t)(a & 0x7FFFFFFFu) : (int64_t)a;
    int64_t kb = (b & 0x80000000u) ? -(int64_t)(b & 0x7FFFFFFFu) : (int64_t)b;
    if ((a & 0x7F800000u) == 0) ka = 0; /* denormals / zeros compare equal */
    if ((b & 0x7F800000u) == 0) kb = 0;
    return ka < kb ? -1 : ka > kb ? 1 : 0;
}

/* ---- reference copies of the float paths of src/ps2/vu/vu.c (CLIP, the
 * EFU, FDIV) as they were before the rewrite, on the ref_ helpers ---- */
#include "vu.h"
#include "vu_decode.h"

uint32_t ref_clip(const uint32_t fs[4], uint32_t ftw)
{
    double w = fabs(ref_f_to_d(ftw));
    uint32_t fl = 0;
    int c;
    for (c = 0; c < 3; c++) {
        double x = ref_f_to_d(fs[c]);
        if (x > w) fl |= 1u << (c * 2);
        if (x < -w) fl |= 2u << (c * 2);
    }
    return fl;
}

uint32_t ref_efu(int op, const uint32_t s[4], int fsf)
{
    double x = ref_f_to_d(s[0]), y = ref_f_to_d(s[1]), z = ref_f_to_d(s[2]);
    double w = ref_f_to_d(s[3]), f = ref_f_to_d(s[fsf]), r;
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
    if (r != r) r = 0;
    if (isinf(r)) r = r > 0 ? 1e300 : -1e300;
    return ref_f_from_d(r, 0);
}

uint32_t ref_fdiv(int op, uint32_t a, uint32_t b, uint32_t *fl)
{
    double da = ref_f_to_d(a), db = ref_f_to_d(b);
    uint32_t sgn = (a ^ b) & 0x80000000u;
    *fl = 0;
    if (op == VU_L_SQRT) {
        if (db < 0) *fl = VU_ST_I;
        return ref_f_from_d(sqrt(fabs(db)), 0) & 0x7FFFFFFFu;
    }
    if (op == VU_L_RSQRT) {
        if (db < 0) *fl = VU_ST_I;
        if (db == 0) {
            *fl |= da == 0 ? VU_ST_I : VU_ST_D;
            return (a & 0x80000000u) | 0x7FFFFFFFu;
        }
        return ref_f_from_d(da / sqrt(fabs(db)), 0);
    }
    if (db == 0) {
        *fl = da == 0 ? VU_ST_I : VU_ST_D;
        return sgn | 0x7FFFFFFFu;
    }
    return ref_f_from_d(da / db, 0);
}
