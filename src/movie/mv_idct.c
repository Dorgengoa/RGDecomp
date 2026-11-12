/* SPDX-License-Identifier: CC0-1.0 */
/* 8x8 inverse DCT (ISO/IEC 13818-2 Annex A):
 *   f(x,y) = 1/4 sum_u sum_v C(u) C(v) F(v,u) cos((2x+1)u pi/16) cos((2y+1)v pi/16)
 * evaluated separably in double precision with an even/odd split of each 1-D transform
 * (x[n] = E[n] + O[n], x[7-n] = E[n] - O[n]), then rounded to nearest. Far more accurate
 * than the IEEE 1180 bounds require; tests/movie checks it against the direct double sum.
 * Rows that are known to be zero are skipped (most coded blocks have 1-3 non-zero rows). */
#include <math.h>
#include <string.h>

#include "mv_internal.h"

/* c[k][n] = C(k)/2 * cos((2n+1) k pi / 16) for n = 0..3 (the other half follows by
 * symmetry). Computed once with cos(); the values are exact enough that table order and
 * libm differences cannot change a rounded result in practice, and the decoder only needs
 * self-consistency for determinism (same binary, same output). */
static double g_c[8][4];
static int g_init;

#if defined(__x86_64__) || defined(_M_X64)
/* x64 (gfxperf5, 2026-11-08): the game builds this table on its first movie frame, inside the
 * kernel step, i.e. under the guest MXCSR (round toward zero + FTZ + DAZ), where the x64 UCRT's
 * cos is wrong (src/crt/crt_math.c HOST_RN): 12 of 32 entries differed from i686 by up to
 * ~2^-40 relative, enough to flip rounded pixels; the title movie then differed from i686 by 1-2
 * levels (boot:save2 fields 678-1,100).  Under that MXCSR x64 takes the table i686 computes
 * there (read from an i686 save state at field 677, out/gfxperf5/runs/s1_i).  Round to nearest
 * (tools, tests, RG_EE_FPU=ieee) computes as before.  RG_MV_IDCT_TAB=0: always compute. */
#include <stdint.h>
#include <stdlib.h>
#include <xmmintrin.h>
static const uint64_t g_c_i686_chop[8][4] = {
    {0x3fd6a09e667f3bcdull, 0x3fd6a09e667f3bcdull, 0x3fd6a09e667f3bcdull, 0x3fd6a09e667f3bcdull},
    {0x3fdf6297cff75cb0ull, 0x3fda9b66290ea1a3ull, 0x3fd1c73b39ae68c9ull, 0x3fb8f8b83c69a60dull},
    {0x3fdd906bcf328d46ull, 0x3fc87de2a6aea964ull, 0xbfc87de2a6aea962ull, 0xbfdd906bcf328d46ull},
    {0x3fda9b66290ea1a3ull, 0xbfb8f8b83c69a608ull, 0xbfdf6297cff75cb0ull, 0xbfd1c73b39ae68cfull},
    {0x3fd6a09e667f3bcdull, 0xbfd6a09e667f3bccull, 0xbfd6a09e667f3bceull, 0x3fd6a09e667f3bcbull},
    {0x3fd1c73b39ae68c9ull, 0xbfdf6297cff75cb0ull, 0x3fb8f8b83c69a5ecull, 0x3fda9b66290ea1a5ull},
    {0x3fc87de2a6aea964ull, 0xbfdd906bcf328d47ull, 0x3fdd906bcf328d44ull, 0xbfc87de2a6aea947ull},
    {0x3fb8f8b83c69a60dull, 0xbfd1c73b39ae68cfull, 0x3fda9b66290ea1a5ull, 0xbfdf6297cff75cb2ull},
};
static int chop_table(void)
{
    const char *e = getenv("RG_MV_IDCT_TAB");
    if (e && e[0] == '0') return 0;
    if ((_mm_getcsr() & 0x6000u) != 0x6000u) return 0;
    memcpy(g_c, g_c_i686_chop, sizeof g_c);
    g_init = 1;
    return 1;
}
#else
static int chop_table(void) { return 0; }
#endif

static void init_tab(void)
{
    const double pi = 3.14159265358979323846;
    if (chop_table()) return;
    for (int k = 0; k < 8; k++) {
        double ck = (k == 0) ? sqrt(0.5) : 1.0;
        for (int n = 0; n < 4; n++) g_c[k][n] = 0.5 * ck * cos((2 * n + 1) * k * pi / 16.0);
    }
    g_init = 1;
}

/* 1-D: in[0..7] (stride is) -> out[0..7] (stride os) */
static inline void idct1(const double *in, int is, double *out, int os)
{
    double x0 = in[0], x1 = in[is], x2 = in[2 * is], x3 = in[3 * is];
    double x4 = in[4 * is], x5 = in[5 * is], x6 = in[6 * is], x7 = in[7 * is];
    for (int n = 0; n < 4; n++) {
        double e = g_c[0][n] * x0 + g_c[2][n] * x2 + g_c[4][n] * x4 + g_c[6][n] * x6;
        double o = g_c[1][n] * x1 + g_c[3][n] * x3 + g_c[5][n] * x5 + g_c[7][n] * x7;
        out[n * os] = e + o;
        out[(7 - n) * os] = e - o;
    }
}

static void idct_core(const int32_t *blk, unsigned rowmask, double *res)
{
    double tmp[64];
    if (!g_init) init_tab();
    /* horizontal pass on each non-zero row (row v holds F(v, u=0..7)) */
    for (int v = 0; v < 8; v++) {
        double *t = tmp + v * 8;
        if (!(rowmask & (1u << v))) {
            memset(t, 0, 8 * sizeof(double));
            continue;
        }
        const int32_t *r = blk + v * 8;
        if (!(r[1] | r[2] | r[3] | r[4] | r[5] | r[6] | r[7])) {
            double d = g_c[0][0] * (double)r[0];
            for (int x = 0; x < 8; x++) t[x] = d;
            continue;
        }
        double in[8];
        for (int u = 0; u < 8; u++) in[u] = (double)r[u];
        idct1(in, 1, t, 1);
    }
    /* vertical pass on each column */
    for (int x = 0; x < 8; x++) idct1(tmp + x, 8, res + x, 8);
}

static inline int round_nearest(double v)
{
    /* floor(v + 0.5) without libm: v is within +-2^13 */
    return (int)(v + 0.5 + 16384.0) - 16384;
}

void mv_idct_int(const int32_t *blk, unsigned rowmask, int32_t *out)
{
    double res[64];
    idct_core(blk, rowmask, res);
    for (int i = 0; i < 64; i++) out[i] = round_nearest(res[i]);
}

void mv_idct_put(const int32_t *blk, unsigned rowmask, uint8_t *dst, int stride)
{
    double res[64];
    idct_core(blk, rowmask, res);
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int v = round_nearest(res[y * 8 + x]);
            dst[x] = (uint8_t)(v < 0 ? 0 : v > 255 ? 255 : v);
        }
        dst += stride;
    }
}

void mv_idct_add(const int32_t *blk, unsigned rowmask, uint8_t *dst, int stride)
{
    double res[64];
    idct_core(blk, rowmask, res);
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int v = round_nearest(res[y * 8 + x]);
            if (v < -256) v = -256; /* 7.5: saturate the IDCT output, then add, then clip */
            if (v > 255) v = 255;
            v += dst[x];
            dst[x] = (uint8_t)(v < 0 ? 0 : v > 255 ? 255 : v);
        }
        dst += stride;
    }
}

void mv_idct_ref(const int32_t *blk, double *out)
{
    const double pi = 3.14159265358979323846;
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++) {
            double s = 0;
            for (int v = 0; v < 8; v++)
                for (int u = 0; u < 8; u++) {
                    double cu = u ? 1.0 : sqrt(0.5), cv = v ? 1.0 : sqrt(0.5);
                    s += cu * cv * (double)blk[v * 8 + u] * cos((2 * x + 1) * u * pi / 16.0) *
                         cos((2 * y + 1) * v * pi / 16.0);
                }
            out[y * 8 + x] = s / 4.0;
        }
}
