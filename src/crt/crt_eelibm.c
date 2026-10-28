/* SPDX-License-Identifier: CC0-1.0
 * The retail float libm (newlib's fdlibm float routines as built for the R5900), written in C
 * from the retail listings (tools/parity/eediv/listing.py): IeeeSqrtf_125988, Scalbnf_128f08,
 * KernelSinf_1279d8, KernelCosf_127020, KernelTanf_127ae0, RemPio2f_1255d8,
 * KernelRemPio2f_127170, Sinf_128fd0, Cosf_128d30, Tanf_1290b8, Atanf_128a60,
 * IeeeAtan2f_124c18, IeeeAsinf_124878, IeeeAcosf_124450, IeeePowf_124df8.
 *
 * The R5900 build: exponent 255 is an ordinary number and there are no denormals
 * (_FLT_LARGEST_EXPONENT_IS_NORMAL, _FLT_NO_DENORMALS), so no Inf / NaN branches; |x| below
 * 2^-126 counts as zero.  Constants are the retail bit patterns (the compiler parsed them
 * rounding toward zero).  The operation order is the listings' (gcc does not reassociate).
 *
 * Runs under the game's MXCSR (RG_EE_FPU=chop, the default since 2026-10-24: round toward
 * zero + FTZ + DAZ, src/native/threads/rg_nk_internal.h); crt_math.c calls it only in that mode.
 * Plain chop is close to retail but not bit-exact: the EE adder drops the bits it shifts out
 * and PCSX2 divides rounding to nearest.  Compiled through tools/parity/eediv/eediv_cc.py (the
 * opt-in exact model) this file reproduces retail exactly: docs/TEST-FIXTURES.md "Retail
 * parity", tools/parity/eelibm_check.py.
 *
 * Division by zero: PCSX2's DIV.S returns sign | 0x7F7FFFFF for a zero divisor (ee_divz), so
 * (x-x)/(x-x) is +FLT_MAX (EE_ZERO_DIV), never a host Inf / NaN. */
#include "crt.h"

#include <math.h>
#include <stdint.h>
#include <string.h>

static inline float F(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
static inline uint32_t U(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }

#define EE_ZERO_DIV F(0x7F7FFFFF)
#define ONE F(0x3F800000)
#define HALF F(0x3F000000)
#define HUGE_ F(0x7149F2C9)  /* 1e30 */
#define TINY_ F(0x0DA2425F)  /* 1e-30 */

/* a / b where b can be +-0: EE DIV.S (PCSX2) gives sign | 0x7F7FFFFF for a zero divisor */
static inline float ee_divz(float a, float b)
{
    if ((U(b) & 0x7F800000u) == 0)
        return F(((U(a) ^ U(b)) & 0x80000000u) | 0x7F7FFFFFu);
    return a / b;
}

/* Fabsf_128e08 / Copysignf_128cf0: bit operations */
static inline float ee_fabsf(float x) { return F(U(x) & 0x7FFFFFFFu); }
static inline float ee_copysignf(float x, float y) { return F((U(x) & 0x7FFFFFFFu) | (U(y) & 0x80000000u)); }

/* IeeeSqrtf_125988: bit-by-bit integer square root, rounded (q += q & 1 when inexact) */
static float ee_sqrtf(float x)
{
    int32_t ix = (int32_t)U(x);
    if (((uint32_t)ix & 0x7FFFFFFFu) <= 0x007FFFFFu)
        return x;                                   /* +-0 */
    if (ix < 0)
        return EE_ZERO_DIV;                         /* (x-x)/(x-x) */
    int32_t m = (ix >> 23) - 127;
    ix = (ix & 0x007FFFFF) | 0x00800000;
    ix <<= m & 1;
    m >>= 1;
    ix += ix;
    int32_t q = 0, s = 0;
    for (int32_t r = 0x01000000; r != 0; r = (int32_t)((uint32_t)r >> 1)) {
        int32_t t = s + r;
        if (t <= ix) {
            s = t + r;
            ix -= t;
            q += r;
        }
        ix += ix;
    }
    if (ix != 0)
        q += q & 1;
    return F((uint32_t)((q >> 1) + 0x3F000000 + (m << 23)));
}

/* Scalbnf_128f08.  Retail lets the exponent reach 255 (an ordinary EE number); on the host
 * that is Inf/NaN, so 255 takes the overflow path (+-FLT_MAX under chop) here. */
static float ee_scalbnf(float x, int n)
{
    uint32_t hx = U(x), ix = hx & 0x7FFFFFFFu;
    if (ix <= 0x007FFFFFu)
        return x;
    int k = (int)(ix >> 23) + n;
    if (k > 254)
        return HUGE_ * ee_copysignf(HUGE_, x);
    if (k > 0)
        return F((hx & 0x807FFFFFu) | ((uint32_t)k << 23));
    if (n > 50000)
        return HUGE_ * ee_copysignf(HUGE_, x);
    return TINY_ * ee_copysignf(TINY_, x);
}

/* ---- kernels (|x| <= pi/4, y = tail of the reduced argument) ---- */
static float ksinf(float x, float y, int iy)
{
    uint32_t ix = U(x) & 0x7FFFFFFF;
    if (ix < 0x32000000 && (int)x == 0)
        return x;
    float z = x * x, v = z * x;
    float r = F(0x3C088889) + z * (F(0xB9500D01) + z * (F(0x3638EF1A) + z * (F(0xB2D72F34) + z * F(0x2F2EC9D2))));
    if (iy == 0)
        return x + v * (F(0xBE2AAAAA) + z * r);
    return x - ((z * (HALF * y - v * r) - y) - v * F(0xBE2AAAAA));
}

static float kcosf(float x, float y)
{
    uint32_t ix = U(x) & 0x7FFFFFFF;
    if (ix < 0x32000000 && (int)x == 0)
        return ONE;
    float z = x * x;
    float r = z * (F(0x3D2AAAAA) + z * (F(0xBAB60B60) + z * (F(0x37D00D00) + z * (F(0xB493F27B) +
              z * (F(0x310F74F5) + z * F(0xAD47D74E))))));
    if (ix < 0x3E99999A)
        return ONE - (HALF * z - (z * r - x * y));
    float qx = ix > 0x3F480000 ? F(0x3E900000) : F(ix - 0x01000000);
    float hz = HALF * z - qx;
    float a = ONE - qx;
    return a - (hz - (z * r - x * y));
}

/* KernelTanf_127ae0 (iy = 1: tan, -1: -1/tan) */
static const uint32_t tanT[13] = {0x3EAAAAAB, 0x3E088889, 0x3D5D0DD1, 0x3CB327A3, 0x3C11371E, 0x3B6B6916, 0x3ABEDE47,
                                  0x3A1A26C7, 0x398137B8, 0x38A3F445, 0x3895C07A, 0xB79BAE5E, 0x37D95384};

static float ktanf(float x, float y, int iy)
{
    int32_t hx = (int32_t)U(x);
    uint32_t ix = (uint32_t)hx & 0x7FFFFFFF;
    if (ix < 0x31800000) {
        if ((int)x == 0) {
            if ((ix | (uint32_t)(iy + 1)) == 0)
                return ee_divz(ONE, ee_fabsf(x));
            return iy == 1 ? x : ee_divz(F(0xBF800000), x);
        }
    }
    if (ix >= 0x3F2CA140) {
        if (hx < 0) {
            x = -x;
            y = -y;
        }
        float z = F(0x3F490FDA) - x;
        float w = F(0x33222167) - y;
        x = z + w;
        y = 0.0f;
    }
    float z = x * x;
    float w = z * z;
    float r = F(tanT[1]) + w * (F(tanT[3]) + w * (F(tanT[5]) + w * (F(tanT[7]) + w * (F(tanT[9]) + w * F(tanT[11])))));
    float v = z * (F(tanT[2]) + w * (F(tanT[4]) + w * (F(tanT[6]) + w * (F(tanT[8]) + w * (F(tanT[10]) + w * F(tanT[12]))))));
    float s = z * x;
    r = y + z * (s * (r + v) + y);
    r = r + F(tanT[0]) * s;
    w = x + r;
    if (ix >= 0x3F2CA140) {
        v = (float)iy;
        return (float)(1 - ((hx >> 30) & 2)) * (v - (x - (w * w / (w + v) - r)) * 2.0f);
    }
    if (iy == 1)
        return w;
    {
        float a, t;
        z = F(U(w) & 0xFFFFF000u);
        v = r - (z - x);
        t = a = F(0xBF800000) / w;
        t = F(U(t) & 0xFFFFF000u);
        s = t * z + ONE;
        return t + a * (s + t * v);
    }
}

/* ---- argument reduction ---- */
/* KernelRemPio2f_127170 (newlib kf_rem_pio2.c; note ih = iq[jz-1] >> 8 for q0 == 0, as linked) */
static const int32_t two_over_pi[198] = {
    0xA2, 0xF9, 0x83, 0x6E, 0x4E, 0x44, 0x15, 0x29, 0xFC, 0x27, 0x57, 0xD1, 0xF5, 0x34, 0xDD, 0xC0, 0xDB, 0x62,
    0x95, 0x99, 0x3C, 0x43, 0x90, 0x41, 0xFE, 0x51, 0x63, 0xAB, 0xDE, 0xBB, 0xC5, 0x61, 0xB7, 0x24, 0x6E, 0x3A,
    0x42, 0x4D, 0xD2, 0xE0, 0x06, 0x49, 0x2E, 0xEA, 0x09, 0xD1, 0x92, 0x1C, 0xFE, 0x1D, 0xEB, 0x1C, 0xB1, 0x29,
    0xA7, 0x3E, 0xE8, 0x82, 0x35, 0xF5, 0x2E, 0xBB, 0x44, 0x84, 0xE9, 0x9C, 0x70, 0x26, 0xB4, 0x5F, 0x7E, 0x41,
    0x39, 0x91, 0xD6, 0x39, 0x83, 0x53, 0x39, 0xF4, 0x9C, 0x84, 0x5F, 0x8B, 0xBD, 0xF9, 0x28, 0x3B, 0x1F, 0xF8,
    0x97, 0xFF, 0xDE, 0x05, 0x98, 0x0F, 0xEF, 0x2F, 0x11, 0x8B, 0x5A, 0x0A, 0x6D, 0x1F, 0x6D, 0x36, 0x7E, 0xCF,
    0x27, 0xCB, 0x09, 0xB7, 0x4F, 0x46, 0x3F, 0x66, 0x9E, 0x5F, 0xEA, 0x2D, 0x75, 0x27, 0xBA, 0xC7, 0xEB, 0xE5,
    0xF1, 0x7B, 0x3D, 0x07, 0x39, 0xF7, 0x8A, 0x52, 0x92, 0xEA, 0x6B, 0xFB, 0x5F, 0xB1, 0x1F, 0x8D, 0x5D, 0x08,
    0x56, 0x03, 0x30, 0x46, 0xFC, 0x7B, 0x6B, 0xAB, 0xF0, 0xCF, 0xBC, 0x20, 0x9A, 0xF4, 0x36, 0x1D, 0xA9, 0xE3,
    0x91, 0x61, 0x5E, 0xE6, 0x1B, 0x08, 0x65, 0x99, 0x85, 0x5F, 0x14, 0xA0, 0x68, 0x40, 0x8D, 0xFF, 0xD8, 0x80,
    0x4D, 0x73, 0x27, 0x31, 0x06, 0x06, 0x15, 0x56, 0xCA, 0x73, 0xA8, 0xC9, 0x60, 0xE2, 0x7B, 0xC0, 0x8C, 0x6B};
static const uint32_t PIo2[11] = {0x3FC90000, 0x39F00000, 0x37D9FFFF, 0x33A20000, 0x2E83FFFF, 0x2B4FFFFF,
                                  0x27C1FFFF, 0x22CFFFFF, 0x1FC40000, 0x1BC5FFFF, 0x17440000};

static int kernel_rem_pio2f(const float *x, float *y, int e0, int nx)
{
    const float zero = 0.0f, two8 = F(0x43800000), twon8 = F(0x3B800000);
    int32_t jz, jx, jv, jp, jk, carry, n, iq[20], i, j, k, m, q0, ih;
    float z, fw, f[20], fq[20], q[20];

    jk = 9;                     /* init_jk[prec = 2] */
    jp = jk;
    jx = nx - 1;
    jv = (e0 - 3) / 8;
    if (jv < 0)
        jv = 0;
    q0 = e0 - 8 * (jv + 1);
    j = jv - jx;
    m = jx + jk;
    for (i = 0; i <= m; i++, j++)
        f[i] = j < 0 ? zero : (float)two_over_pi[j];
    for (i = 0; i <= jk; i++) {
        for (j = 0, fw = 0.0f; j <= jx; j++)
            fw = fw + x[j] * f[jx + i - j];
        q[i] = fw;
    }
    jz = jk;
recompute:
    for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
        fw = (float)(int32_t)(twon8 * z);
        iq[i] = (int32_t)(z - fw * two8);
        z = q[j - 1] + fw;
    }
    z = ee_scalbnf(z, q0);
    z = z - floorf(z * F(0x3E000000)) * F(0x41000000);
    n = (int32_t)z;
    z = z - (float)n;
    ih = 0;
    if (q0 > 0) {
        i = iq[jz - 1] >> (8 - q0);
        n += i;
        iq[jz - 1] -= i << (8 - q0);
        ih = iq[jz - 1] >> (7 - q0);
    } else if (q0 == 0)
        ih = iq[jz - 1] >> 8;
    else if (z >= HALF)
        ih = 2;
    if (ih > 0) {
        n += 1;
        carry = 0;
        for (i = 0; i < jz; i++) {
            j = iq[i];
            if (carry == 0) {
                if (j != 0) {
                    carry = 1;
                    iq[i] = 0x100 - j;
                }
            } else
                iq[i] = 0xFF - j;
        }
        if (q0 > 0) {
            switch (q0) {
            case 1: iq[jz - 1] &= 0x7F; break;
            case 2: iq[jz - 1] &= 0x3F; break;
            }
        }
        if (ih == 2) {
            z = ONE - z;
            if (carry != 0)
                z = z - ee_scalbnf(ONE, q0);
        }
    }
    if (z == zero) {
        j = 0;
        for (i = jz - 1; i >= jk; i--)
            j |= iq[i];
        if (j == 0) {
            for (k = 1; iq[jk - k] == 0; k++)
                ;
            for (i = jz + 1; i <= jz + k; i++) {
                f[jx + i] = (float)two_over_pi[jv + i];
                for (j = 0, fw = 0.0f; j <= jx; j++)
                    fw = fw + x[j] * f[jx + i - j];
                q[i] = fw;
            }
            jz += k;
            goto recompute;
        }
    }
    if (z == zero) {
        jz -= 1;
        q0 -= 8;
        while (iq[jz] == 0) {
            jz--;
            q0 -= 8;
        }
    } else {
        z = ee_scalbnf(z, -q0);
        if (z >= two8) {
            fw = (float)(int32_t)(twon8 * z);
            iq[jz] = (int32_t)(z - fw * two8);
            jz += 1;
            q0 += 8;
            iq[jz] = (int32_t)fw;
        } else
            iq[jz] = (int32_t)z;
    }
    fw = ee_scalbnf(ONE, q0);
    for (i = jz; i >= 0; i--) {
        q[i] = fw * (float)iq[i];
        fw = fw * twon8;
    }
    for (i = jz; i >= 0; i--) {
        for (fw = 0.0f, k = 0; k <= jp && k <= jz - i; k++)
            fw = fw + F(PIo2[k]) * q[i + k];
        fq[jz - i] = fw;
    }
    fw = 0.0f;
    for (i = jz; i >= 0; i--)
        fw = fw + fq[i];
    y[0] = ih == 0 ? fw : -fw;
    fw = fq[0] - fw;
    for (i = 1; i <= jz; i++)
        fw = fw + fq[i];
    y[1] = ih == 0 ? fw : -fw;
    return n & 7;
}

static const uint32_t npio2_hw[32] = {
    0x3FC90F00, 0x40490F00, 0x4096CB00, 0x40C90F00, 0x40FB5300, 0x4116CB00, 0x412FED00, 0x41490F00,
    0x41623100, 0x417B5300, 0x418A3A00, 0x4196CB00, 0x41A35C00, 0x41AFED00, 0x41BC7E00, 0x41C90F00,
    0x41D5A000, 0x41E23100, 0x41EEC200, 0x41FB5300, 0x4203F200, 0x420A3A00, 0x42108300, 0x4216CB00,
    0x421D1400, 0x42235C00, 0x4229A500, 0x422FED00, 0x42363600, 0x423C7E00, 0x4242C700, 0x42490F00};

static int rem_pio2f(float x, float *y)
{
    const float pio2_1 = F(0x3FC90F80), pio2_1t = F(0x37354442), pio2_2 = F(0x373543FF),
                pio2_2t = F(0x2E85A308), pio2_3 = F(0x2E85A300), pio2_3t = F(0x248D3131),
                invpio2 = F(0x3F22F984);
    int32_t hx = (int32_t)U(x);
    uint32_t ix = (uint32_t)hx & 0x7FFFFFFF;
    if (ix <= 0x3F490FD8) {
        y[0] = x;
        y[1] = 0;
        return 0;
    }
    if (ix < 0x4016CBE4) {      /* |x| < 3pi/4: one step */
        float z;
        if (hx > 0) {
            z = x - pio2_1;
            if ((ix & 0xFFFFFFF0) != 0x3FC90FD0) {
                y[0] = z - pio2_1t;
                y[1] = (z - y[0]) - pio2_1t;
            } else {
                z = z - pio2_2;
                y[0] = z - pio2_2t;
                y[1] = (z - y[0]) - pio2_2t;
            }
            return 1;
        }
        z = x + pio2_1;
        if ((ix & 0xFFFFFFF0) != 0x3FC90FD0) {
            y[0] = z + pio2_1t;
            y[1] = (z - y[0]) + pio2_1t;
        } else {
            z = z + pio2_2;
            y[0] = z + pio2_2t;
            y[1] = (z - y[0]) + pio2_2t;
        }
        return -1;
    }
    if (ix <= 0x43490F80) {     /* |x| ~<= 2^7 pi/2: medium */
        float t = ee_fabsf(x);
        int n = (int)(t * invpio2 + HALF);
        float fn = (float)n;
        float r = t - fn * pio2_1;
        float w = fn * pio2_1t;
        if (n < 32 && (ix & 0xFFFFFF00) != npio2_hw[n - 1]) {
            y[0] = r - w;
        } else {
            int j = (int)(ix >> 23);
            y[0] = r - w;
            int i = j - (int)((U(y[0]) >> 23) & 0xFF);
            if (i > 8) {
                t = r;
                w = fn * pio2_2;
                r = t - w;
                w = fn * pio2_2t - ((t - r) - w);
                y[0] = r - w;
                i = j - (int)((U(y[0]) >> 23) & 0xFF);
                if (i > 25) {
                    t = r;
                    w = fn * pio2_3;
                    r = t - w;
                    w = fn * pio2_3t - ((t - r) - w);
                    y[0] = r - w;
                }
            }
        }
        y[1] = (r - y[0]) - w;
        if (hx < 0) {
            y[0] = -y[0];
            y[1] = -y[1];
            return -n;
        }
        return n;
    }
    {                           /* large: scalbn(|x|, ilogb(x) - 7) in three 8-bit chunks */
        float tx[3], z;
        int e0 = (int)(ix >> 23) - 134, nx = 3, i;
        z = F(ix - ((uint32_t)e0 << 23));
        for (i = 0; i < 2; i++) {
            tx[i] = (float)(int32_t)z;
            z = (z - tx[i]) * F(0x43800000);
        }
        tx[2] = z;
        while (tx[nx - 1] == 0.0f)
            nx--;
        int n = kernel_rem_pio2f(tx, y, e0, nx);
        if (hx < 0) {
            y[0] = -y[0];
            y[1] = -y[1];
            return -n;
        }
        return n;
    }
}

float rg_ee_sinf(float x)
{
    float y[2];
    uint32_t ix = U(x) & 0x7FFFFFFF;
    if (ix <= 0x3F490FD8)
        return ksinf(x, 0.0f, 0);
    int n = rem_pio2f(x, y);
    switch (n & 3) {
    case 0: return ksinf(y[0], y[1], 1);
    case 1: return kcosf(y[0], y[1]);
    case 2: return -ksinf(y[0], y[1], 1);
    default: return -kcosf(y[0], y[1]);
    }
}

float rg_ee_cosf(float x)
{
    float y[2];
    uint32_t ix = U(x) & 0x7FFFFFFF;
    if (ix <= 0x3F490FD8)
        return kcosf(x, 0.0f);
    int n = rem_pio2f(x, y);
    switch (n & 3) {
    case 0: return kcosf(y[0], y[1]);
    case 1: return -ksinf(y[0], y[1], 1);
    case 2: return -kcosf(y[0], y[1]);
    default: return ksinf(y[0], y[1], 1);
    }
}

float rg_ee_tanf(float x)
{
    float y[2];
    uint32_t ix = U(x) & 0x7FFFFFFF;
    if (ix <= 0x3F490FDA)
        return ktanf(x, 0.0f, 1);
    int n = rem_pio2f(x, y);
    return ktanf(y[0], y[1], 1 - ((n & 1) << 1));
}

/* ---- atan / atan2 ---- */
static const uint32_t atanhi[4] = {0x3EED6338, 0x3F490FDA, 0x3F7B985D, 0x3FC90FDA};
static const uint32_t atanlo[4] = {0x31AC3769, 0x33222167, 0x33140FB4, 0x33A22168};
static const uint32_t aT[11] = {0x3EAAAAAB, 0xBE4CCCCC, 0x3E124924, 0xBDE38E38, 0x3DBA2E6E, 0xBD9D8795,
                                0x3D886B34, 0xBD6EF16A, 0x3D4BDA59, 0xBD15A221, 0x3C8569D7};

static float ee_atanf(float x)
{
    int32_t hx = (int32_t)U(x);
    uint32_t ix = (uint32_t)hx & 0x7FFFFFFF;
    int id;
    if (ix >= 0x50800000)
        return hx > 0 ? F(atanhi[3]) + F(atanlo[3]) : -F(atanhi[3]) - F(atanlo[3]);
    if (ix < 0x3EE00000) {
        if (ix < 0x31000000 && HUGE_ + x > ONE)
            return x;
        id = -1;
    } else {
        x = ee_fabsf(x);
        if (ix < 0x3F980000) {
            if (ix < 0x3F300000) {
                id = 0;
                x = (F(0x40000000) * x - ONE) / (F(0x40000000) + x);
            } else {
                id = 1;
                x = (x - ONE) / (x + ONE);
            }
        } else if (ix < 0x401C0000) {
            id = 2;
            x = (x - F(0x3FC00000)) / (ONE + F(0x3FC00000) * x);
        } else {
            id = 3;
            x = F(0xBF800000) / x;
        }
    }
    float z = x * x, w = z * z;
    float s1 = z * (F(aT[0]) + w * (F(aT[2]) + w * (F(aT[4]) + w * (F(aT[6]) + w * (F(aT[8]) + w * F(aT[10]))))));
    float s2 = w * (F(aT[1]) + w * (F(aT[3]) + w * (F(aT[5]) + w * (F(aT[7]) + w * F(aT[9])))));
    if (id < 0)
        return x - x * (s1 + s2);
    z = F(atanhi[id]) - ((x * (s1 + s2) - F(atanlo[id])) - x);
    return hx < 0 ? -z : z;
}

float rg_ee_atan2f(float y, float x)
{
    const float pi = F(0x40490FDA), pi_o_2 = F(0x3FC90FDA), pi_lo = F(0x34222168);
    int32_t hx = (int32_t)U(x), hy = (int32_t)U(y);
    uint32_t ix = (uint32_t)hx & 0x7FFFFFFF, iy = (uint32_t)hy & 0x7FFFFFFF;
    if ((uint32_t)hx == 0x3F800000)
        return ee_atanf(y);
    int m = ((hy >> 31) & 1) | ((hx >> 30) & 2);
    if (iy <= 0x7FFFFF) {
        switch (m) {
        case 0:
        case 1: return y;
        case 2: return pi;
        default: return -pi;
        }
    }
    if (ix <= 0x7FFFFF)
        return hy < 0 ? -pi_o_2 : pi_o_2;
    int k = (int)(iy - ix) >> 23;
    float z;
    if (k > 60)
        z = pi_o_2;
    else if (hx < 0 && k < -60)
        z = 0.0f;
    else
        z = ee_atanf(ee_fabsf(y / x));
    switch (m) {
    case 0: return z;
    case 1: return F(U(z) ^ 0x80000000u);
    case 2: return pi - (z - pi_lo);
    default: return (z - pi_lo) - pi;
    }
}

/* ---- asin / acos (shared rational approximation) ---- */
#define PIO2_HI F(0x3FC90FDA)
#define PIO2_LO F(0x33A22168)
#define PIO4_HI F(0x3F490FDA)

static inline float asin_p(float t)
{
    return t * (F(0x3E2AAAAA) + t * (F(0xBEA6B08F) + t * (F(0x3E4E0AA8) + t * (F(0xBD241146) +
           t * (F(0x3A4F7F04) + t * F(0x3811EF08))))));
}

static inline float asin_q(float t)
{
    return ONE + t * (F(0xC019D138) + t * (F(0x4001572C) + t * (F(0xBF303360) + t * F(0x3D9DC62D))));
}

float rg_ee_asinf(float x)
{
    int32_t hx = (int32_t)U(x);
    uint32_t ix = (uint32_t)hx & 0x7FFFFFFF;
    float t, w, p, q, c, r, s;
    if (ix == 0x3F800000)
        return x * PIO2_HI + x * PIO2_LO;
    if (ix > 0x3F800000)
        return EE_ZERO_DIV;                 /* (x-x)/(x-x) */
    if (ix < 0x3F000000) {
        if (ix < 0x32000000) {
            if (HUGE_ + x > ONE)
                return x;
        } else {
            t = x * x;
            p = asin_p(t);
            q = asin_q(t);
            w = p / q;
            return x + x * w;
        }
    }
    w = ONE - ee_fabsf(x);
    t = w * HALF;
    p = asin_p(t);
    q = asin_q(t);
    s = ee_sqrtf(t);
    if (ix >= 0x3F79999A) {
        w = p / q;
        t = PIO2_HI - ((s + s * w) * 2.0f - PIO2_LO);
    } else {
        w = F(U(s) & 0xFFFFF000u);
        c = (t - w * w) / (s + w);
        r = p / q;
        p = (s * 2.0f) * r - (PIO2_LO - c * 2.0f);
        q = PIO4_HI - w * 2.0f;
        t = PIO4_HI - (p - q);
    }
    return hx > 0 ? t : -t;
}

float rg_ee_acosf(float x)
{
    int32_t hx = (int32_t)U(x);
    uint32_t ix = (uint32_t)hx & 0x7FFFFFFF;
    float z, p, q, r, w, s, c, df;
    if (ix == 0x3F800000)
        return hx > 0 ? 0.0f : F(0x40490FDA);
    if (ix > 0x3F800000)
        return EE_ZERO_DIV;                 /* (x-x)/(x-x) */
    if (ix < 0x3F000000) {
        if (ix <= 0x23000000)
            return F(0x3FC90FDA);           /* pio2_hi + pio2_lo, folded */
        z = x * x;
        p = asin_p(z);
        q = asin_q(z);
        r = p / q;
        return PIO2_HI - (x - (PIO2_LO - x * r));
    }
    if (hx < 0) {
        z = (x + ONE) * HALF;
        p = asin_p(z);
        q = asin_q(z);
        s = ee_sqrtf(z);
        r = p / q;
        w = r * s - PIO2_LO;
        return F(0x40490FDA) - (s + w) * 2.0f;
    }
    z = (ONE - x) * HALF;
    s = ee_sqrtf(z);
    df = F(U(s) & 0xFFFFF000u);
    c = (z - df * df) / (s + df);
    p = asin_p(z);
    q = asin_q(z);
    r = p / q;
    w = r * s + c;
    return (df + w) * 2.0f;
}

/* ---- pow (IeeePowf_124df8; note t = x - 1, not |x| - 1, in the |y| > 2^27 branch) ---- */
static const uint32_t pow_bp[2] = {0x3F800000, 0x3FC00000};
static const uint32_t pow_dp_h[2] = {0x00000000, 0x3F15C000};
static const uint32_t pow_dp_l[2] = {0x00000000, 0x35D1CFDC};

float rg_ee_powf(float x, float y)
{
    float z, ax, z_h, z_l, p_h, p_l, y1, t1, t2, r, s, t, u, v, w;
    int32_t i, j, k, yisint, n, hx, hy, ix, iy, is;
    hx = (int32_t)U(x);
    hy = (int32_t)U(y);
    ix = hx & 0x7FFFFFFF;
    iy = hy & 0x7FFFFFFF;
    if (iy <= 0x007FFFFF)
        return ONE;
    yisint = 0;
    if (hx < 0) {
        if (iy >= 0x4B800000)
            yisint = 2;
        else if (iy >= 0x3F800000) {
            k = (iy >> 23) - 0x7F;
            j = iy >> (23 - k);
            if ((j << (23 - k)) == iy)
                yisint = 2 - (j & 1);
        }
    }
    if (iy == 0x3F800000)
        return hy < 0 ? ee_divz(ONE, x) : x;
    if (hy == 0x40000000)
        return x * x;
    if (hy == 0x3F000000 && hx >= 0)
        return ee_sqrtf(x);
    ax = ee_fabsf(x);
    if (ix <= 0x007FFFFF || ix == 0x3F800000) {
        z = ax;
        if (hy < 0)
            z = ee_divz(ONE, z);
        if (hx < 0) {
            if (((ix - 0x3F800000) | yisint) == 0)
                z = EE_ZERO_DIV;            /* (z-z)/(z-z) */
            else if (yisint == 1)
                z = -z;
        }
        return z;
    }
    if (((((uint32_t)hx >> 31) - 1) | (uint32_t)yisint) == 0)
        return EE_ZERO_DIV;                 /* (x-x)/(x-x) */
    if (iy > 0x4D000000) {
        if (ix < 0x3F7FFFF8)
            return hy < 0 ? F(0x7F7FFFFF) : 0.0f;   /* huge*huge / tiny*tiny, folded */
        if (ix > 0x3F800007)
            return hy > 0 ? F(0x7F7FFFFF) : 0.0f;
        t = x - ONE;
        w = (t * t) * (HALF - t * (F(0x3EAAAAAA) - t * F(0x3E800000)));
        u = F(0x3FB8AA00) * t;
        v = t * F(0x36ECA56F) - w * F(0x3FB8AA3A);
        t1 = u + v;
        t1 = F(U(t1) & 0xFFFFF000u);
        t2 = v - (t1 - u);
    } else {
        float s2, s_h, s_l, t_h, t_l;
        n = (ix >> 23) - 0x7F;
        j = ix & 0x007FFFFF;
        ix = j | 0x3F800000;
        if (j <= 0x1CC471)
            k = 0;
        else if (j < 0x5DB3D7)
            k = 1;
        else {
            k = 0;
            n += 1;
            ix -= 0x00800000;
        }
        ax = F((uint32_t)ix);
        u = ax - F(pow_bp[k]);
        v = ONE / (ax + F(pow_bp[k]));
        s = u * v;
        s_h = F(U(s) & 0xFFFFF000u);
        t_h = F((uint32_t)((((ix >> 1) | 0x20000000) + 0x0040000) + (k << 21)));
        t_l = ax - (t_h - F(pow_bp[k]));
        s_l = v * ((u - s_h * t_h) - s_h * t_l);
        s2 = s * s;
        r = (s2 * s2) * (F(0x3F199999) + s2 * (F(0x3EDB6DB7) + s2 * (F(0x3EAAAAAB) + s2 * (F(0x3E8BA304) +
            s2 * (F(0x3E6C3254) + s2 * F(0x3E53F142))))));
        r = r + s_l * (s_h + s);
        s2 = s_h * s_h;
        t_h = (s2 + F(0x40400000)) + r;
        t_h = F(U(t_h) & 0xFFFFF000u);
        t_l = r - ((t_h - F(0x40400000)) - s2);
        u = s_h * t_h;
        v = s_l * t_h + t_l * s;
        p_h = u + v;
        p_h = F(U(p_h) & 0xFFFFF000u);
        p_l = v - (p_h - u);
        z_h = F(0x3F763800) * p_h;
        z_l = (F(0x369DC39F) * p_h + p_l * F(0x3F76384E)) + F(pow_dp_l[k]);
        t = (float)n;
        t1 = ((z_h + z_l) + F(pow_dp_h[k])) + t;
        t1 = F(U(t1) & 0xFFFFF000u);
        t2 = z_l - (((t1 - t) - F(pow_dp_h[k])) - z_h);
    }
    s = ONE;
    if (((((uint32_t)hx >> 31) - 1) | (uint32_t)(yisint - 1)) == 0)
        s = F(0xBF800000);
    y1 = F(U(y) & 0xFFFFF000u);
    p_l = (y - y1) * t1 + y * t2;
    p_h = y1 * t1;
    z = p_l + p_h;
    j = (int32_t)U(z);
    i = j & 0x7FFFFFFF;
    if (j > 0) {
        if (i > 0x43010000)
            return s * HUGE_ * HUGE_;
        if (i == 0x43010000 && p_l + F(0x3338AA3B) > z - p_h)
            return s * HUGE_ * HUGE_;
    } else {
        if (i > 0x42FC0000)
            return s * TINY_ * TINY_;
        if (i == 0x42FC0000 && p_l <= z - p_h)
            return s * TINY_ * TINY_;
    }
    k = (i >> 23) - 0x7F;
    n = 0;
    if (i > 0x3F000000) {
        n = j + (0x00800000 >> (k + 1));
        k = ((n & 0x7FFFFFFF) >> 23) - 0x7F;
        t = F((uint32_t)n & ~(0x007FFFFFu >> k));
        n = ((n & 0x007FFFFF) | 0x00800000) >> (23 - k);
        if (j < 0)
            n = -n;
        p_h = p_h - t;
    }
    t = p_l + p_h;
    t = F(U(t) & 0xFFFFF000u);
    u = t * F(0x3F317200);
    v = (p_l - (t - p_h)) * F(0x3F317217) + t * F(0x35BFBE8C);
    z = u + v;
    w = v - (z - u);
    t = z * z;
    t1 = z - t * (F(0x3E2AAAAA) + t * (F(0xBB360B60) + t * (F(0x388AB354) + t * (F(0xB5DDEA0E) + t * F(0x3331BB4B)))));
    r = (z * t1) / (t1 - F(0x40000000)) - (w + z * w);
    z = ONE - (r - z);
    j = (int32_t)U(z);
    j += (int32_t)((uint32_t)n << 23);
    if ((j >> 23) <= 0)
        z = ee_scalbnf(z, n);
    else
        z = F((uint32_t)j);
    return s * z;
}
