/* SPDX-License-Identifier: CC0-1.0 */
/* The offscreen-composite VU1 program 0x445C60 (nr_comp.h).  The arithmetic
 * follows the VU interpreter's (src/ps2/vu/vu_float_inl.h) bit for bit:
 * operands with exponent 0 read as signed zeros, results are the double
 * result with the mantissa truncated (toward zero), exponent underflow gives
 * a signed zero, MAX / MINI compare signed magnitudes (fs wins ties), the MAC
 * sign flag is the result's sign bit. */
#include "nr_comp.h"

#include <string.h>

static uint32_t fb(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }
static double to_d(uint32_t a)
{
    uint32_t hi = a & 0x80000000u, lo = 0;
    uint64_t b;
    double d;
    if (a & 0x7F800000u) {
        hi |= ((a & 0x7FFFFFFFu) >> 3) + ((uint32_t)(1023 - 127) << 20);
        lo = a << 29;
    }
    b = ((uint64_t)hi << 32) | lo;
    memcpy(&d, &b, 8);
    return d;
}
static uint32_t from_d(double v)
{
    uint64_t b;
    uint32_t hi, s;
    int e;
    memcpy(&b, &v, 8);
    hi = (uint32_t)(b >> 32);
    s = hi & 0x80000000u;
    if (!(b << 1)) return s;
    e = (int)((hi >> 20) & 0x7FF) - 896;
    if (e >= 256) return s | 0x7FFFFFFFu;
    if (e <= 0) return s;
    return s | ((uint32_t)e << 23) | ((hi << 3) & 0x7FFFF8u) | (uint32_t)((uint32_t)b >> 29);
}
static uint32_t vadd(uint32_t a, uint32_t b) { return from_d(to_d(a) + to_d(b)); }
static uint32_t vsub(uint32_t a, uint32_t b) { return from_d(to_d(a) - to_d(b)); }
static int vcmp(uint32_t a, uint32_t b)
{
    int32_t ka = (a & 0x7F800000u) ? (int32_t)(a & 0x7FFFFFFFu) : 0;
    int32_t kb = (b & 0x7F800000u) ? (int32_t)(b & 0x7FFFFFFFu) : 0;
    if (a & 0x80000000u) ka = -ka;
    if (b & 0x80000000u) kb = -kb;
    return ka < kb ? -1 : ka > kb ? 1 : 0;
}
static uint32_t vmax(uint32_t fs, uint32_t ft) { return vcmp(fs, ft) >= 0 ? fs : ft; }
static uint32_t vmin(uint32_t fs, uint32_t ft) { return vcmp(fs, ft) <= 0 ? fs : ft; }
static int32_t ftoi4(uint32_t a)
{
    double v = to_d(a) * 16.0;
    if (v >= 2147483647.0) return 0x7FFFFFFF;
    if (v <= -2147483648.0) return (int32_t)0x80000000u;
    return (int32_t)v;
}

int nr_comp_strips(const nr_comp_in *in, nr_comp_strip *out, int cap)
{
    const uint32_t one = 0x3F800000u, i32 = 0x42000000u;   /* 1.0, 32.0 (LOI) */
    uint32_t a[4], b[4], v5[4], v6[4], dy[4], of[4], v7x, ireg = fb(in->i_reg);
    int n = 0, k;
    for (k = 0; k < 4; k++) dy[k] = fb(in->dy[k]);
    of[0] = fb(in->ofs[0]); of[1] = fb(in->ofs[1]); of[2] = 0; of[3] = 0;   /* mulx.zw: +0 */
    /* subw.xy vf05 = qw98 - 1; addw.xy vf04 = qw99 + 1; max.xyz vf03 = max(qw140, vf05);
     * mini.xyz vf04 = min(qw141, vf04) */
    a[0] = vmax(fb(in->rmin[0]), vsub(fb(in->lo[0]), one));
    a[1] = vmax(fb(in->rmin[1]), vsub(fb(in->lo[1]), one));
    a[2] = vmax(fb(in->rmin[2]), fb(in->lo[2]));
    b[0] = vmin(fb(in->rmax[0]), vadd(fb(in->hi[0]), one));
    b[1] = vmin(fb(in->rmax[1]), vadd(fb(in->hi[1]), one));
    b[2] = vmin(fb(in->rmax[2]), fb(in->hi[2]));
    /* sub.x / sub.y vf00, vf04, vf03: the sign flag ends the program */
    if (vsub(b[0], a[0]) & 0x80000000u) return 0;
    if (vsub(b[1], a[1]) & 0x80000000u) return 0;
    a[3] = 0; b[3] = 0;                            /* mulx.w vf03 / vf04 = 1 * 0 */
    v6[0] = vsub(b[0], a[0]);
    for (k = 0; k < 4; k++) v5[k] = a[k];          /* max.xyzw vf05, vf03, vf03 */
    v6[1] = vmax(b[1], ireg);                      /* max.yzw vf06, vf04, I (old I) */
    v6[2] = vmax(b[2], ireg);
    v6[3] = vmax(b[3], ireg);
    v7x = vsub(v6[0], one);                        /* subw.x vf07, vf06, vf00w */
    for (;;) {
        if (n == cap) return -1;
        v6[0] = vmin(vadd(v5[0], i32), b[0]);      /* addi.x; mini.x */
        for (k = 0; k < 4; k++) {
            out[n].q[0][k] = ftoi4(vadd(v5[k], dy[k]));
            out[n].q[1][k] = ftoi4(vadd(v5[k], of[k]));
            out[n].q[2][k] = ftoi4(vadd(v6[k], dy[k]));
            out[n].q[3][k] = ftoi4(vadd(v6[k], of[k]));
        }
        n++;
        v7x = vsub(v7x, i32);                      /* subi.x vf07 */
        v5[0] = vadd(v5[0], i32);                  /* addi.x vf05 */
        if (v7x & 0x80000000u) break;              /* fmand (sign x) -> ibeq */
    }
    return n;
}
