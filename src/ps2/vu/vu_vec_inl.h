/* SPDX-License-Identifier: CC0-1.0 */
/* Four-lane SSE2 forms of the VU float helpers (docs/VU.md "Block
 * translator"), for the block translator's handlers.  Private to
 * src/ps2/vu and the float differential test.
 *
 * Every lane gives exactly the bits of the scalar helper in
 * vu_float_inl.h (which rg-vu-float-diff proves against the original
 * ldexp/frexp code):
 *   - vuv_to_d is vuf_to_d on each lane, with the same 32-bit halves;
 *   - vuv_from_d computes vuf_from_d's last line (VU exponent 1..255, the
 *     common case) and its +-0 case on all lanes at once and reports the
 *     other lanes in a mask; the caller redoes those with the scalar
 *     vuf_from_d (overflow and underflow results, and their condition bits);
 *   - vuv_key is vuf_cmp's sign-magnitude key, so comparing keys as signed
 *     integers is vuf_cmp;
 *   - vuv_ftoi is vuf_ftoi: SSE2 truncation, saturating like the scalar
 *     compares (the conversion's own out-of-range answer 0x80000000 is
 *     already right for the negative side).
 * Lane c of a __m128i is component c (x = 0); dest masks have x in bit 3,
 * so vuv_lanes() reverses them. */
#ifndef RG_PS2_VU_VEC_INL_H
#define RG_PS2_VU_VEC_INL_H

#include <emmintrin.h>
#include <stdint.h>

#include "vu_float_inl.h"

typedef struct vuv_d4 {
    __m128d lo;   /* lanes 0, 1 */
    __m128d hi;   /* lanes 2, 3 */
} vuv_d4;

/* dest field (x = bit 3) -> lane bits (x = bit 0), and back */
static const uint8_t vuv_rev4[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
VUF_INLINE unsigned vuv_lanes(unsigned dest) { return vuv_rev4[dest & 15]; }

VUF_INLINE __m128i vuv_load(const uint32_t *p) { return _mm_loadu_si128((const __m128i *)p); }
VUF_INLINE void vuv_store(uint32_t *p, __m128i v) { _mm_storeu_si128((__m128i *)p, v); }

/* all-ones in lane c when bit c of lanes is set */
VUF_INLINE __m128i vuv_lane_mask(unsigned lanes)
{
    return _mm_set_epi32((lanes & 8) ? -1 : 0, (lanes & 4) ? -1 : 0, (lanes & 2) ? -1 : 0, (lanes & 1) ? -1 : 0);
}

VUF_INLINE vuv_d4 vuv_to_d(__m128i a)
{
    const __m128i sgn = _mm_set1_epi32((int)0x80000000u);
    __m128i s = _mm_and_si128(a, sgn);
    __m128i ez = _mm_cmpeq_epi32(_mm_and_si128(a, _mm_set1_epi32(0x7F800000)), _mm_setzero_si128());
    __m128i hi = _mm_add_epi32(_mm_srli_epi32(_mm_and_si128(a, _mm_set1_epi32(0x7FFFFFFF)), 3),
                               _mm_set1_epi32((1023 - 127) << 20));
    __m128i lo = _mm_slli_epi32(a, 29);
    vuv_d4 d;
    hi = _mm_or_si128(s, _mm_andnot_si128(ez, hi));
    lo = _mm_andnot_si128(ez, lo);
    d.lo = _mm_castsi128_pd(_mm_unpacklo_epi32(lo, hi));
    d.hi = _mm_castsi128_pd(_mm_unpackhi_epi32(lo, hi));
    return d;
}

VUF_INLINE vuv_d4 vuv_bcast(double v)
{
    vuv_d4 d;
    d.lo = d.hi = _mm_set1_pd(v);
    return d;
}

/* *slow = lanes (bit c = lane c) whose result needs the scalar vuf_from_d,
 * *zero = lanes whose result is +-0 (vuf_from_d's first case: the result
 * is the sign, the condition Z, plus S when negative) */
VUF_INLINE __m128i vuv_from_d_z(vuv_d4 d, unsigned *slow, unsigned *zero)
{
    __m128 f01 = _mm_castpd_ps(d.lo), f23 = _mm_castpd_ps(d.hi);
    __m128i hi = _mm_castps_si128(_mm_shuffle_ps(f01, f23, _MM_SHUFFLE(3, 1, 3, 1)));
    __m128i lo = _mm_castps_si128(_mm_shuffle_ps(f01, f23, _MM_SHUFFLE(2, 0, 2, 0)));
    __m128i ex = _mm_and_si128(_mm_srli_epi32(hi, 20), _mm_set1_epi32(0x7FF));
    __m128i t = _mm_sub_epi32(ex, _mm_set1_epi32(897));
    __m128i fast = _mm_and_si128(_mm_cmpgt_epi32(t, _mm_set1_epi32(-1)), _mm_cmplt_epi32(t, _mm_set1_epi32(255)));
    __m128i sgn = _mm_and_si128(hi, _mm_set1_epi32((int)0x80000000u));
    __m128i z = _mm_cmpeq_epi32(_mm_or_si128(_mm_and_si128(hi, _mm_set1_epi32(0x7FFFFFFF)), lo), _mm_setzero_si128());
    __m128i r;
    unsigned fm = (unsigned)_mm_movemask_ps(_mm_castsi128_ps(fast));
    *zero = (unsigned)_mm_movemask_ps(_mm_castsi128_ps(z));
    *slow = ~(fm | *zero) & 15u;
    r = _mm_or_si128(sgn, _mm_slli_epi32(_mm_add_epi32(t, _mm_set1_epi32(1)), 23));
    r = _mm_or_si128(r, _mm_and_si128(_mm_slli_epi32(hi, 3), _mm_set1_epi32(0x7FFFF8)));
    r = _mm_or_si128(r, _mm_srli_epi32(lo, 29));
    /* +-0: the sign alone */
    return _mm_or_si128(_mm_andnot_si128(z, r), _mm_and_si128(z, sgn));
}

VUF_INLINE __m128i vuv_from_d(vuv_d4 d, unsigned *slow)
{
    unsigned zero;
    return vuv_from_d_z(d, slow, &zero);
}

VUF_INLINE double vuv_lane_d(vuv_d4 d, int c)
{
    double t[4];
    _mm_storeu_pd(t, d.lo);
    _mm_storeu_pd(t + 2, d.hi);
    return t[c];
}

/* vuv_from_d plus the scalar redo of the slow lanes among `lanes`; the
 * returned MAC bits are those of `lanes` (S from the sign for fast lanes,
 * the scalar condition for the others), spread like mac_spread >> c */
VUF_INLINE __m128i vuv_from_d_mac(vuv_d4 d, unsigned lanes, uint32_t *mac)
{
    unsigned slow, sb, zero;
    __m128i r = vuv_from_d_z(d, &slow, &zero);
    slow &= lanes;
    *mac |= vuv_rev4[zero & lanes];          /* Z of the +-0 lanes */
    if (slow) {
        uint32_t rr[4];
        double t[4];
        int c;
        _mm_storeu_pd(t, d.lo);
        _mm_storeu_pd(t + 2, d.hi);
        vuv_store(rr, r);
        for (c = 0; c < 4; c++)
            if (slow & (1u << c)) {
                unsigned cond;
                rr[c] = vuf_from_d(t[c], &cond);
                *mac |= (((cond & VUF_Z) ? 0x0008u : 0) | ((cond & VUF_S) ? 0x0080u : 0) |
                         ((cond & VUF_U) ? 0x0800u : 0) | ((cond & VUF_O) ? 0x8000u : 0)) >> c;
            }
        r = vuv_load(rr);
    }
    sb = (unsigned)_mm_movemask_ps(_mm_castsi128_ps(r)) & lanes & ~slow;
    *mac |= (uint32_t)vuv_rev4[sb] << 4;
    return r;
}

/* vuv_from_d with the slow lanes redone, no condition bits */
VUF_INLINE __m128i vuv_from_d_fix(vuv_d4 d, unsigned lanes)
{
    uint32_t mac = 0;
    return vuv_from_d_mac(d, lanes, &mac);
}

/* the product step of MADD/MSUB: chopped product, and the O bits of its
 * lanes (as MAC bits) */
VUF_INLINE __m128i vuv_from_d_ovf(vuv_d4 d, unsigned lanes, uint32_t *obits)
{
    unsigned slow;
    __m128i r = vuv_from_d(d, &slow);
    slow &= lanes;
    if (slow) {
        uint32_t rr[4];
        double t[4];
        int c;
        _mm_storeu_pd(t, d.lo);
        _mm_storeu_pd(t + 2, d.hi);
        vuv_store(rr, r);
        for (c = 0; c < 4; c++)
            if (slow & (1u << c)) {
                unsigned cond;
                rr[c] = vuf_from_d(t[c], &cond);
                if (cond & VUF_O) *obits |= 0x8000u >> c;
            }
        r = vuv_load(rr);
    }
    return r;
}

VUF_INLINE vuv_d4 vuv_add(vuv_d4 a, vuv_d4 b) { a.lo = _mm_add_pd(a.lo, b.lo); a.hi = _mm_add_pd(a.hi, b.hi); return a; }
VUF_INLINE vuv_d4 vuv_sub(vuv_d4 a, vuv_d4 b) { a.lo = _mm_sub_pd(a.lo, b.lo); a.hi = _mm_sub_pd(a.hi, b.hi); return a; }
VUF_INLINE vuv_d4 vuv_mul(vuv_d4 a, vuv_d4 b) { a.lo = _mm_mul_pd(a.lo, b.lo); a.hi = _mm_mul_pd(a.hi, b.hi); return a; }

/* vuf_cmp key: exponent 0 reads as 0, then sign-magnitude as signed int */
VUF_INLINE __m128i vuv_key(__m128i a)
{
    __m128i k = _mm_and_si128(a, _mm_set1_epi32(0x7FFFFFFF));
    __m128i ez = _mm_cmpeq_epi32(_mm_and_si128(a, _mm_set1_epi32(0x7F800000)), _mm_setzero_si128());
    __m128i s = _mm_srai_epi32(a, 31);
    k = _mm_andnot_si128(ez, k);
    return _mm_sub_epi32(_mm_xor_si128(k, s), s);
}

/* MAX (is_max) / MINI of a and t, lane by lane, as the interpreter's
 * cmp >= 0 ? a : t / cmp <= 0 ? a : t */
VUF_INLINE __m128i vuv_minmax(__m128i a, __m128i t, int is_max)
{
    __m128i ka = vuv_key(a), kt = vuv_key(t);
    __m128i take_t = is_max ? _mm_cmpgt_epi32(kt, ka) : _mm_cmpgt_epi32(ka, kt);
    return _mm_or_si128(_mm_and_si128(take_t, t), _mm_andnot_si128(take_t, a));
}

VUF_INLINE __m128i vuv_ftoi(__m128i a, int frac_bits)
{
    vuv_d4 v = vuv_to_d(a);
    __m128d p = _mm_set1_pd(vuf_pow2(frac_bits)), lim = _mm_set1_pd(2147483647.0);
    __m128i r, sat;
    v.lo = _mm_mul_pd(v.lo, p);
    v.hi = _mm_mul_pd(v.hi, p);
    r = _mm_unpacklo_epi64(_mm_cvttpd_epi32(v.lo), _mm_cvttpd_epi32(v.hi));
    sat = _mm_castps_si128(_mm_shuffle_ps(_mm_castpd_ps(_mm_cmpge_pd(v.lo, lim)),
                                          _mm_castpd_ps(_mm_cmpge_pd(v.hi, lim)), _MM_SHUFFLE(2, 0, 2, 0)));
    return _mm_or_si128(_mm_andnot_si128(sat, r), _mm_and_si128(sat, _mm_set1_epi32(0x7FFFFFFF)));
}

/* lanes: the lanes whose result is used (the others may be left wrong) */
VUF_INLINE __m128i vuv_itof(__m128i a, int frac_bits, unsigned lanes)
{
    vuv_d4 v;
    __m128d p = _mm_set1_pd(vuf_pow2(-frac_bits));
    v.lo = _mm_mul_pd(_mm_cvtepi32_pd(a), p);
    v.hi = _mm_mul_pd(_mm_cvtepi32_pd(_mm_shuffle_epi32(a, _MM_SHUFFLE(3, 2, 3, 2))), p);
    return vuv_from_d_fix(v, lanes);
}

#endif
