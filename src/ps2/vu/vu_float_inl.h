/* SPDX-License-Identifier: CC0-1.0 */
/* VU float helpers as inline bit manipulation (docs/VU.md "Performance").
 * Private to src/ps2/vu: vu_float.c wraps them as the public vu_f_* entry
 * points, vu.c calls them directly.
 *
 * Every function here returns exactly the bits of the original
 * ldexp/frexp formulation (kept as tests/vu/vu_float_ref.c and compared by
 * rg-vu-float-diff):
 *   - vu_f_to_d: a VU single with exponent e != 0 is (1 + f/2^23) * 2^(e-127),
 *     i.e. the double with exponent field e - 127 + 1023 and the 23 fraction
 *     bits at the top of the 52-bit mantissa; e == 0 reads as a signed zero.
 *   - vu_f_from_d: frexp's m * 2^ex has ex = E64 - 1022 for a normal double,
 *     so the VU exponent ex + 126 is E64 - 896, and (m*2 - 1) * 2^23 chopped is
 *     the top 23 mantissa bits.  A subnormal double (E64 == 0, nonzero
 *     mantissa) has frexp exponent <= -1022, an underflow either way.
 *   - ldexp(x, +-n) for |n| <= 15 on these magnitudes is a multiplication by
 *     the exact power of two 2^+-n (no overflow, no underflow, no rounding).
 * The arithmetic itself (double add / sub / mul, round to nearest, SSE2) is
 * unchanged. */
#ifndef RG_PS2_VU_FLOAT_INL_H
#define RG_PS2_VU_FLOAT_INL_H

#include <stdint.h>
#include <string.h>

#if defined(__GNUC__) || defined(__clang__)
#define VUF_INLINE static inline __attribute__((always_inline))
#else
#define VUF_INLINE static __inline
#endif

enum { VUF_Z = 1, VUF_S = 2, VUF_U = 4, VUF_O = 8 };

/* vu_float.c: EFU result (P) for lower op `op` (vu_decode.h) on fs = s[4]
 * with field fsf; FDIV/SQRT/RSQRT result (Q) with *fl = VU_ST_I / VU_ST_D */
uint32_t vu_efu(int op, const uint32_t s[4], int fsf);
uint32_t vu_fdiv(int op, uint32_t a, uint32_t b, uint32_t *fl);

VUF_INLINE double vuf_bits_d(uint64_t b)
{
    double d;
    memcpy(&d, &b, 8);
    return d;
}

VUF_INLINE uint64_t vuf_d_bits(double d)
{
    uint64_t b;
    memcpy(&b, &d, 8);
    return b;
}

/* the double is built from two 32-bit halves (the port is i686): high word
 * = sign | (exponent and fraction >> 3) + (1023 - 127) << 20, low word = the
 * fraction's 3 low bits at the top; exponent 0 is a signed zero */
VUF_INLINE double vuf_to_d(uint32_t a)
{
    uint32_t hi = a & 0x80000000u, lo = 0;
    if (a & 0x7F800000u) {
        hi |= ((a & 0x7FFFFFFFu) >> 3) + ((uint32_t)(1023 - 127) << 20);
        lo = a << 29;
    }
    return vuf_bits_d(((uint64_t)hi << 32) | lo);
}

/* cond receives the MAC-style bits (Z, S, U, O); never NULL here */
VUF_INLINE uint32_t vuf_from_d(double v, unsigned *cond)
{
    uint64_t b = vuf_d_bits(v);
    uint32_t hi = (uint32_t)(b >> 32);
    uint32_t s = hi & 0x80000000u;
    unsigned c = s ? VUF_S : 0;
    int E;
    /* fast path, the common case: VU exponent 1..255 (neither zero, nor
     * overflow, nor underflow; the same result as the last line) */
    if ((uint32_t)(((hi >> 20) & 0x7FF) - 897) < 255u) {
        *cond = c;
        return s | ((((hi >> 20) & 0x7FF) - 896) << 23) | ((hi << 3) & 0x7FFFF8u) | ((uint32_t)b >> 29);
    }
    if (!(b << 1)) {                 /* +-0 */
        *cond = c | VUF_Z;
        return s;
    }
    E = (int)((hi >> 20) & 0x7FF) - 896;
    if (E >= 256) {                  /* also +-Inf, never produced by the callers */
        *cond = c | VUF_O;
        return s | 0x7FFFFFFFu;
    }
    if (E <= 0) {                    /* incl. subnormal doubles */
        *cond = c | VUF_U | VUF_Z;
        return s;
    }
    *cond = c;
    return s | ((uint32_t)E << 23) | ((hi << 3) & 0x7FFFF8u) | (uint32_t)((uint32_t)b >> 29);
}

VUF_INLINE uint32_t vuf_add(uint32_t a, uint32_t b, unsigned *cond)
{
    return vuf_from_d(vuf_to_d(a) + vuf_to_d(b), cond);
}

VUF_INLINE uint32_t vuf_sub(uint32_t a, uint32_t b, unsigned *cond)
{
    return vuf_from_d(vuf_to_d(a) - vuf_to_d(b), cond);
}

VUF_INLINE uint32_t vuf_mul(uint32_t a, uint32_t b, unsigned *cond)
{
    return vuf_from_d(vuf_to_d(a) * vuf_to_d(b), cond);
}

/* 2^n and 2^-n for the four FTOI/ITOF fraction widths (0, 4, 12, 15) and
 * anything else up to 31 */
VUF_INLINE double vuf_pow2(int n)
{
    return vuf_bits_d((uint64_t)(1023 + n) << 52);
}

VUF_INLINE uint32_t vuf_ftoi(uint32_t a, int frac_bits)
{
    double v = vuf_to_d(a) * vuf_pow2(frac_bits);
    if (v >= 2147483647.0) return 0x7FFFFFFFu;
    if (v <= -2147483648.0) return 0x80000000u;
    return (uint32_t)(int32_t)v;     /* truncates toward zero */
}

VUF_INLINE uint32_t vuf_itof(uint32_t a, int frac_bits)
{
    unsigned c;
    return vuf_from_d((double)(int32_t)a * vuf_pow2(-frac_bits), &c);
}

VUF_INLINE int vuf_cmp(uint32_t a, uint32_t b)
{
    int32_t ka = (a & 0x7F800000u) ? (int32_t)(a & 0x7FFFFFFFu) : 0;
    int32_t kb = (b & 0x7F800000u) ? (int32_t)(b & 0x7FFFFFFFu) : 0;
    if (a & 0x80000000u) ka = -ka;
    if (b & 0x80000000u) kb = -kb;
    return ka < kb ? -1 : ka > kb ? 1 : 0;
}

/* CLIP judgement of fs.xyz against |ft.w| (6 bits: +x -x +y -y +z -z).
 * The original's double compares are compares of the VU values, done here
 * on the magnitudes (exponent 0 reads as zero, as in to_d). */
VUF_INLINE uint32_t vuf_clip(const uint32_t fs[4], uint32_t ftw)
{
    int32_t w = (ftw & 0x7F800000u) ? (int32_t)(ftw & 0x7FFFFFFFu) : 0;
    uint32_t fl = 0;
    int c;
    for (c = 0; c < 3; c++) {
        uint32_t x = fs[c];
        int32_t m = (x & 0x7F800000u) ? (int32_t)(x & 0x7FFFFFFFu) : 0;
        if (m > w) fl |= (x & 0x80000000u) ? 2u << (c * 2) : 1u << (c * 2);
    }
    return fl;
}

#endif
