/* SPDX-License-Identifier: CC0-1.0
 * PROTOTYPE, SUPERSEDED 2026-10-24 by src/crt/crt_eelibm.c (the complete libm, the default
 * under RG_EE_FPU=chop; checked by tools/parity/eelibm_check.py).  Kept for history.
 * The retail float libm, written from the retail listings (Sinf_128fd0, Cosf_128d30,
 * KernelSinf_1279d8, KernelCosf_127020, RemPio2f_1255d8, Atanf_128a60, IeeeAtan2f_124c18;
 * newlib's fdlibm float routines built for the R5900: exponent 255 is an ordinary number,
 * so no Inf / NaN branches).  Meant to run under the game's EE MXCSR (round toward zero, FTZ,
 * DAZ: RG_EE_FPU=chop); divisions go through ee_div (round to nearest, as PCSX2's DIV.S).
 * Constants are the retail bit patterns. */
#include <stdint.h>
#include <string.h>
#include <math.h>

float rg_ee_divf(float a, float b);      /* tools/parity/eediv/rg_ee_divf.c */
#define ee_div(a, b) rg_ee_divf((a), (b))

static inline float F(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
static inline uint32_t U(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }

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
    return x - ((z * (F(0x3F000000) * y - v * r) - y) - v * F(0xBE2AAAAA));
}

static float kcosf(float x, float y)
{
    uint32_t ix = U(x) & 0x7FFFFFFF;
    if (ix < 0x32000000 && (int)x == 0)
        return F(0x3F800000);
    float z = x * x;
    float r = z * (F(0x3D2AAAAA) + z * (F(0xBAB60B60) + z * (F(0x37D00D00) + z * (F(0xB493F27B) +
              z * (F(0x310F74F5) + z * F(0xAD47D74E))))));
    if (ix < 0x3E99999A)
        return F(0x3F800000) - (F(0x3F000000) * z - (z * r - x * y));
    float qx = ix > 0x3F480000 ? F(0x3E900000) : F(ix - 0x01000000);
    float hz = F(0x3F000000) * z - qx;
    float a = F(0x3F800000) - qx;
    return a - (hz - (z * r - x * y));
}

/* ---- argument reduction ---- */
static const uint32_t npio2_hw[32] = {
    0x3FC90F00, 0x40490F00, 0x4096CB00, 0x40C90F00, 0x40FB5300, 0x4116CB00, 0x412FED00, 0x41490F00,
    0x41623100, 0x417B5300, 0x418A3A00, 0x4196CB00, 0x41A35C00, 0x41AFED00, 0x41BC7E00, 0x41C90F00,
    0x41D5A000, 0x41E23100, 0x41EEC200, 0x41FB5300, 0x4203F200, 0x420A3A00, 0x42108300, 0x4216CB00,
    0x421D1400, 0x42235C00, 0x4229A500, 0x422FED00, 0x42363600, 0x423C7E00, 0x4242C700, 0x42490F00};

static int rem_pio2f(float x, float *y)
{
    const float pio2_1 = F(0x3FC90F80), pio2_1t = F(0x37354442), pio2_2 = F(0x373543FF),
                pio2_2t = F(0x2E85A308), pio2_3 = F(0x2E85A300), pio2_3t = F(0x248D3131),
                invpio2 = F(0x3F22F984), half = F(0x3F000000);
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
                z -= pio2_2;
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
            z += pio2_2;
            y[0] = z + pio2_2t;
            y[1] = (z - y[0]) + pio2_2t;
        }
        return -1;
    }
    if (ix <= 0x43490F80) {     /* |x| ~<= 2^7 pi/2: medium */
        float t = fabsf(x);
        int n = (int)(t * invpio2 + half);
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
    /* large arguments: retail's KernelRemPio2f_127170 (not written yet): long double fallback */
    {
        long double q = nearbyintl((long double)x / 1.57079632679489661923132169163975144L);
        long double rr = (long double)x - q * 1.57079632679489661923132169163975144L;
        y[0] = (float)rr;
        y[1] = (float)(rr - y[0]);
        return (int)((long long)q & 0x7FFFFFFF);
    }
}

float ee_sinf(float x)
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

float ee_cosf(float x)
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

/* ---- atan / atan2 ---- */
static const uint32_t atanhi[4] = {0x3EED6338, 0x3F490FDA, 0x3F7B985D, 0x3FC90FDA};
static const uint32_t atanlo[4] = {0x31AC3769, 0x33222167, 0x33140FB4, 0x33A22168};
static const uint32_t aT[11] = {0x3EAAAAAB, 0xBE4CCCCC, 0x3E124924, 0xBDE38E38, 0x3DBA2E6E, 0xBD9D8795,
                                0x3D886B34, 0xBD6EF16A, 0x3D4BDA59, 0xBD15A221, 0x3C8569D7};

float ee_atanf(float x)
{
    int32_t hx = (int32_t)U(x);
    uint32_t ix = (uint32_t)hx & 0x7FFFFFFF;
    int id;
    if (ix >= 0x50800000)
        return hx > 0 ? F(atanhi[3]) + F(atanlo[3]) : -F(atanhi[3]) - F(atanlo[3]);
    if (ix < 0x3EE00000) {
        if (ix < 0x31000000 && F(0x7149F2C9) + x > F(0x3F800000))
            return x;
        id = -1;
    } else {
        x = fabsf(x);
        if (ix < 0x3F980000) {
            if (ix < 0x3F300000) {
                id = 0;
                x = ee_div(F(0x40000000) * x - F(0x3F800000), F(0x40000000) + x);
            } else {
                id = 1;
                x = ee_div(x - F(0x3F800000), x + F(0x3F800000));
            }
        } else if (ix < 0x401C0000) {
            id = 2;
            x = ee_div(x - F(0x3FC00000), F(0x3F800000) + F(0x3FC00000) * x);
        } else {
            id = 3;
            x = ee_div(F(0xBF800000), x);
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

float ee_atan2f(float y, float x)
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
        z = ee_atanf(fabsf(ee_div(y, x)));
    switch (m) {
    case 0: return z;
    case 1: return F(U(z) ^ 0x80000000u);
    case 2: return pi - (z - pi_lo);
    default: return (z - pi_lo) - pi;
    }
}
