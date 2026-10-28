/* SPDX-License-Identifier: CC0-1.0 */
/* The line-strand VU1 program (0x441660 + 0x441840) as plain C
 * (nr_vu1ln.h, docs/NATIVE-RENDER.md "Line strands"). */
#include "nr_vu1ln.h"

#include <math.h>
#include <string.h>

/* VU FMAC arithmetic: double, chopped toward zero to a single */
static inline float vchop(double v)
{
    float f = (float)v;
    uint32_t u;
    memcpy(&u, &f, 4);
    if ((double)fabsf(f) > fabs(v)) u -= 1;
    if ((u & 0x7F800000u) == 0) u &= 0x80000000u;
    memcpy(&f, &u, 4);
    return f;
}
static float vmul(float a, float b) { return vchop((double)a * (double)b); }
static float vadd(float a, float b) { return vchop((double)a + (double)b); }
static float vsub(float a, float b) { return vchop((double)a - (double)b); }
static float kf(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }

static int32_t ftoi4(float v)
{
    double d = (double)v * 16.0;
    if (d >= 2147483647.0) return 2147483647;
    if (d <= -2147483648.0) return (int32_t)0x80000000u;
    return (int32_t)d;
}
static int32_t ftoi0(float v)
{
    double d = (double)v;
    if (d >= 2147483647.0) return 2147483647;
    if (d <= -2147483648.0) return (int32_t)0x80000000u;
    return (int32_t)d;
}

/* clip = S * (p, 1) (qw68..71, mulax/madday/maddaz/maddw) */
static void clipv(const nr_qw *c, const float p[3], float o[4])
{
    int k;
    for (k = 0; k < 4; k++) {
        float a = vmul(c[68].f[k], p[0]);
        a = vadd(a, vmul(c[69].f[k], p[1]));
        a = vadd(a, vmul(c[70].f[k], p[2]));
        o[k] = vadd(a, c[71].f[k]);           /* * vf00w (1.0) is exact */
    }
}
/* screen = clip.xyz * Q, Q = DIV 1 / w */
static void proj(const float cl[4], float s[3])
{
    float q = vchop(1.0 / (double)cl[3]);
    s[0] = vmul(cl[0], q); s[1] = vmul(cl[1], q); s[2] = vmul(cl[2], q);
}
/* guard band: (s * g) + (qw110 * g) outside +-1 (CLIP against vf00w) */
static int guard_out(const float s[3], const float g[3], const float o[3])
{
    int k;
    for (k = 0; k < 3; k++) {
        float v = vadd(vmul(s[k], g[k]), vmul(o[k], g[k]));
        if (v > 1.0f || v < -1.0f) return 1;
    }
    return 0;
}
static void cross(float o[3], const float a[3], const float b[3])
{
    float x = vsub(vmul(a[1], b[2]), vmul(b[1], a[2]));
    float y = vsub(vmul(a[2], b[0]), vmul(b[2], a[0]));
    float z = vsub(vmul(a[0], b[1]), vmul(b[0], a[1]));
    o[0] = x; o[1] = y; o[2] = z;
}

int nr_vu1ln_records(const nr_qw *c, const float (*pos)[3], uint32_t n, int four, nr_lnrec *out, int max)
{
    float g[3], go[3];
    const float k111 = kf(0x3F8E38E4u), kfade = kf(0xBB360B61u);
    uint32_t step = four ? 4 : 2, i;
    int nr = 0, k;
    /* qw109 = qw17 with xy * qw16.xy, qw110 = qw18 (the head writes them) */
    g[0] = vmul(c[17].f[0], c[16].f[0]);
    g[1] = vmul(c[17].f[1], c[16].f[1]);
    g[2] = c[17].f[2];
    go[0] = c[18].f[0]; go[1] = c[18].f[1]; go[2] = c[18].f[2];
    for (i = 0; i + step <= n && nr < max; i += step) {
        float cl[4][4], s[4][3], fade, hw;
        int adc, j = four ? 1 : 0;          /* the segment: P1 -> P2 (four) or P0 -> P1 */
        nr_lnrec *r = &out[nr++];
        for (k = 0; k < (int)step; k++) {
            clipv(c, pos[i + k], cl[k]);
            proj(cl[k], s[k]);
        }
        fade = vadd(k111, vmul(kfade, cl[j][3]));
        if (fade < 0.0f) fade = 0.0f;
        if (fade > 1.0f) fade = 1.0f;
        r->alpha = (uint32_t)ftoi0(vmul(fade, 64.0f)) & 0xFF;
        hw = vmul(0.5f, fade);
        adc = guard_out(s[j], g, go) || guard_out(s[j + 1], g, go);
        if (four && !adc) {
            float e1[3], e2[3], e3[3], e4[3], n1[3], n2[3];
            for (k = 0; k < 3; k++) {
                e1[k] = vsub(s[1][k], s[0][k]);
                e2[k] = vsub(s[2][k], s[0][k]);
                e3[k] = vsub(s[2][k], s[1][k]);
                e4[k] = vsub(s[3][k], s[1][k]);
            }
            cross(n1, e1, e2);
            cross(n2, e3, e4);
            if (vmul(n1[2], n2[2]) < 0.0f) adc = 1;   /* CLIP z < -|0| */
        }
        r->adc = adc ? (int)0xFFFF8000u : 0;   /* MFIR.w sign-extends vi01 = 0x8000 */
        {
            /* v0 a+(hw,0) v1 b+(hw,0) v2 a-(hw,0) v3 b-(hw,0) v4 a-(0,hw) v5 b-(0,hw) v6 a+(0,hw) v7 b+(0,hw) */
            static const int sx[8] = { 1, 1, -1, -1, 0, 0, 0, 0 }, sy[8] = { 0, 0, 0, 0, -1, -1, 1, 1 };
            for (k = 0; k < 8; k++) {
                const float *p = s[j + (k & 1)];
                float x = sx[k] ? vadd(p[0], sx[k] > 0 ? hw : -hw) : p[0];
                float y = sy[k] ? vadd(p[1], sy[k] > 0 ? hw : -hw) : p[1];
                r->x[k] = ftoi4(x);
                r->y[k] = ftoi4(y);
                r->z[k] = ftoi4(p[2]);
            }
        }
    }
    return nr;
}

int nr_vu1ln_is_line_sig(const uint32_t sig[10])
{
    return sig[4] == 0x800106BCu && sig[5] == 0x09010800u;
}
