/* SPDX-License-Identifier: CC0-1.0 */
/* The shadow-volume VU1 program (0x4425F0 + 0x4427E0) as plain C
 * (nr_vu1sh.h, docs/NATIVE-RENDER.md "Shadow volumes"). */
#include "nr_vu1sh.h"

#include <math.h>
#include <string.h>

/* VU FMAC arithmetic (nr_const.c): double, chopped toward zero to a single */
static inline float vchop(double v)
{
    float f = (float)v;
    uint32_t u;
    memcpy(&u, &f, 4);
    if ((double)fabsf(f) > fabs(v)) u -= 1;          /* one ulp toward zero (f is not 0 here) */
    if ((u & 0x7F800000u) == 0) u &= 0x80000000u;    /* below 2^-126: flush to (signed) zero */
    memcpy(&f, &u, 4);
    return f;
}
static float vmul(float a, float b) { return vchop((double)a * (double)b); }
static float vadd(float a, float b) { return vchop((double)a + (double)b); }
static float vsub(float a, float b) { return vchop((double)a - (double)b); }

/* acc = c0 * x.x; acc += c1 * x.y; acc += c2 * x.z; out = acc + c3 * x.w */
static void mat4(float o[4], const float c0[4], const float c1[4], const float c2[4], const float c3[4],
                 const float x[4])
{
    int k;
    for (k = 0; k < 4; k++) {
        float a = vmul(c0[k], x[0]);
        a = vadd(a, vmul(c1[k], x[1]));
        a = vadd(a, vmul(c2[k], x[2]));
        o[k] = vadd(a, vmul(c3[k], x[3]));
    }
}

/* OPMULA / OPMSUB: a x b */
static void cross(float o[3], const float a[3], const float b[3])
{
    float x = vsub(vmul(a[1], b[2]), vmul(b[1], a[2]));
    float y = vsub(vmul(a[2], b[0]), vmul(b[2], a[0]));
    float z = vsub(vmul(a[0], b[1]), vmul(b[0], a[1]));
    o[0] = x; o[1] = y; o[2] = z;
}

/* CLIP: any of x, y, z outside +-|w| */
static int clipped(const float v[4])
{
    float w = fabsf(v[3]);
    return v[0] > w || v[0] < -w || v[1] > w || v[1] < -w || v[2] > w || v[2] < -w;
}

/* FTOI4: x * 16 truncated toward zero, saturated */
static int32_t ftoi4(float v)
{
    double d = (double)v * 16.0;
    if (d >= 2147483647.0) return 2147483647;
    if (d <= -2147483648.0) return (int32_t)0x80000000u;
    return (int32_t)d;
}

/* project: xyz *= Q (Q = 1 / w, DIV chopped), w kept */
static void proj(float v[4])
{
    float q = vchop(1.0 / (double)v[3]);
    v[0] = vmul(v[0], q);
    v[1] = vmul(v[1], q);
    v[2] = vmul(v[2], q);
}

static void face(nr_shface *f, const float a[3], const float b[3], const float c[3], const float *const v4[4],
                 const int32_t (*fx)[4])
{
    float e1[3], e2[3], n[3];
    int k;
    (void)v4;
    e1[0] = vsub(b[0], a[0]); e1[1] = vsub(b[1], a[1]); e1[2] = vsub(b[2], a[2]);
    e2[0] = vsub(c[0], a[0]); e2[1] = vsub(c[1], a[1]); e2[2] = vsub(c[2], a[2]);
    cross(n, e1, e2);
    /* mulz by vf20.z (1.0) then CLIP against w = 0: bit +z = n.z > 0 */
    f->regq = n[2] > 0.0f ? 38u : 35u;
    for (k = 0; k < 4; k++) {
        f->x[k] = fx[k][0]; f->y[k] = fx[k][1]; f->z[k] = fx[k][2]; f->w[k] = fx[k][3];
    }
}

int nr_vu1sh_faces(const nr_qw *c, const float (*pos)[3], uint32_t n, nr_shface *out, int max)
{
    float S[4][4], M[4][4], C[4][4], L[3];
    float s16z, s16w;
    uint32_t t;
    int nf = 0, i, k;
    /* S: qw12..15 with x of qw12 scaled by qw16.z and y of qw13 by qw16.w (qw106) */
    s16z = c[16].f[2];
    s16w = c[16].f[3];
    for (i = 0; i < 4; i++) memcpy(S[i], c[12 + i].f, 16);
    S[0][0] = vmul(S[0][0], s16z);
    S[1][1] = vmul(S[1][1], s16w);
    /* M = plane projection (columns qw30..33) x object rows qw60..63 */
    for (i = 0; i < 4; i++) mat4(M[i], c[30].f, c[31].f, c[32].f, c[33].f, c[60 + i].f);
    /* C = clip (columns qw8..11) x view (qw24..27), xy scaled by qw16.xy (qw105) */
    for (i = 0; i < 4; i++) {
        mat4(C[i], c[8].f, c[9].f, c[10].f, c[11].f, c[24 + i].f);
        C[i][0] = vmul(C[i][0], c[16].f[0]);
        C[i][1] = vmul(C[i][1], c[16].f[1]);
    }
    L[0] = c[34].f[0]; L[1] = c[34].f[1]; L[2] = c[34].f[2];
    for (t = 0; t + 2 < n; t += 3) {
        float w[3][4], p[3][4], e1[3], e2[3], nn[3], d;
        float A[3][4], B[3][4];
        int32_t fa[3][4], fb[3][4];
        int clipout = 0;
        for (k = 0; k < 3; k++) {
            float x[4] = { pos[t + k][0], pos[t + k][1], pos[t + k][2], 1.0f };
            mat4(w[k], c[60].f, c[61].f, c[62].f, c[63].f, x);   /* world = R * p (w = 1) */
            mat4(p[k], M[0], M[1], M[2], M[3], x);               /* projected on the plane */
        }
        for (k = 0; k < 3; k++) { e1[k] = vsub(w[1][k], w[0][k]); e2[k] = vsub(w[2][k], w[0][k]); }
        cross(nn, e1, e2);
        d = vmul(L[0], nn[0]);
        d = vadd(d, vmul(L[1], nn[1]));
        d = vadd(d, vmul(L[2], nn[2]));
        if (!(d > 0.0001f)) continue;
        for (k = 0; k < 3; k++) {
            mat4(A[k], C[0], C[1], C[2], C[3], w[k]);
            if (clipped(A[k])) clipout = 1;
        }
        if (clipout) continue;
        for (k = 0; k < 3; k++) {
            mat4(B[k], C[0], C[1], C[2], C[3], p[k]);
            if (clipped(B[k])) clipout = 1;
        }
        if (clipout) continue;
        for (k = 0; k < 3; k++) {
            float s[4];
            mat4(s, S[0], S[1], S[2], S[3], A[k]);
            proj(s);
            memcpy(A[k], s, 16);
            mat4(s, S[0], S[1], S[2], S[3], B[k]);
            proj(s);
            memcpy(B[k], s, 16);
        }
        for (k = 0; k < 3; k++) {
            int j;
            for (j = 0; j < 4; j++) { fa[k][j] = ftoi4(A[k][j]); fb[k][j] = ftoi4(B[k][j]); }
        }
        if (nf + 5 > max) break;
        {
            const int32_t (*f1[4])[4], (*f2[4])[4], (*f3[4])[4], (*f4[4])[4], (*f5[4])[4];
            int32_t q[4][4];
            int j;
            (void)f1; (void)f2; (void)f3; (void)f4; (void)f5;
            /* sides: A0 B0 B1 A1 (normal (B0-A0) x (B1-A0)), A1 B1 B2 A2, A2 B2 B0 A0 */
#define SETQ(a, b, c2, d2) do { for (j = 0; j < 4; j++) { q[0][j] = a[j]; q[1][j] = b[j]; q[2][j] = c2[j]; q[3][j] = d2[j]; } } while (0)
            SETQ(fa[0], fb[0], fb[1], fa[1]);
            face(&out[nf++], A[0], B[0], B[1], NULL, (const int32_t (*)[4])q);
            SETQ(fa[1], fb[1], fb[2], fa[2]);
            face(&out[nf++], A[1], B[1], B[2], NULL, (const int32_t (*)[4])q);
            SETQ(fa[2], fb[2], fb[0], fa[0]);
            face(&out[nf++], A[2], B[2], B[0], NULL, (const int32_t (*)[4])q);
            /* caps: A0 A1 A2 A2 ((A1-A0) x (A2-A0)), B2 B1 B0 B0 ((B1-B2) x (B0-B2)) */
            SETQ(fa[0], fa[1], fa[2], fa[2]);
            face(&out[nf++], A[0], A[1], A[2], NULL, (const int32_t (*)[4])q);
            SETQ(fb[2], fb[1], fb[0], fb[0]);
            face(&out[nf++], B[2], B[1], B[0], NULL, (const int32_t (*)[4])q);
#undef SETQ
        }
    }
    return nf;
}

/* skinning as the decode piece 0x43A020 does it (paths for 1, 2 and 4 bones):
 * v_k = p * w_k (xyz, and w = w_k), acc = sum over bones of r0 v.x + r1 v.y +
 * r2 v.z + r3 v.w in that order, every step chopped */
void nr_vu1sh_skin(const float p[3], const float *const rows[4][4], const float w[4], int nb, float out[3])
{
    int b, k;
    float acc[3] = { 0, 0, 0 };
    for (b = 0; b < nb; b++) {
        float v[4];
        v[0] = vmul(p[0], w[b]); v[1] = vmul(p[1], w[b]); v[2] = vmul(p[2], w[b]); v[3] = w[b];
        for (k = 0; k < 3; k++) {
            float a = b == 0 ? vmul(rows[b][0][k], v[0]) : vadd(acc[k], vmul(rows[b][0][k], v[0]));
            a = vadd(a, vmul(rows[b][1][k], v[1]));
            a = vadd(a, vmul(rows[b][2][k], v[2]));
            acc[k] = vadd(a, vmul(rows[b][3][k], v[3]));
        }
    }
    out[0] = acc[0]; out[1] = acc[1]; out[2] = acc[2];
}

float nr_vu1sh_weight(uint32_t byte)
{
    /* LOI 0x3B808081 (the decode pieces' 1/255; 0.00392157f would be 0x3B808083) */
    static const union { uint32_t u; float f; } k = { 0x3B808081u };
    return vmul((float)byte, k.f);
}
float nr_vu1sh_pos(int32_t raw, float scale) { return vmul((float)raw * (1.0f / 32768.0f), scale); }

int nr_vu1_decode_positions(const nr_qw *mem, uint32_t top, int skinned, float (*out)[3], int max)
{
    const nr_qw *h0 = &mem[top & 1023], *h1 = &mem[(top + 1) & 1023];
    uint32_t n = h0->u[1] & 0x7FFF, i, data = top + 2, a_skin = data + h1->u[2];
    const float *ps = mem[77].f;
    int nb = 0;
    if (n > (uint32_t)max) n = (uint32_t)max;
    if (skinned) {
        uint32_t j = mem[76].u[2] ? h1->u[3] : 0;
        nb = j == 0 ? 1 : j == 2 ? 2 : (j == 4 || j == 6) ? 4 : 0;
    }
    for (i = 0; i < n; i++) {
        const nr_qw *pq = &mem[(data + i) & 1023];
        float p[3];
        int k;
        for (k = 0; k < 3; k++) p[k] = nr_vu1sh_pos(pq->i[k], ps[k]);
        if (nb) {
            const nr_qw *si = &mem[(a_skin + 2 * i) & 1023], *sw = &mem[(a_skin + 2 * i + 1) & 1023];
            const float *rows[4][4];
            float w[4];
            int b;
            for (b = 0; b < nb; b++) {
                uint32_t idx = 900 + 2 * (si->u[b] & 0xFFFF);
                for (k = 0; k < 4; k++) rows[b][k] = mem[(idx + k) & 1023].f;
                w[b] = nr_vu1sh_weight(sw->u[b]);
            }
            nr_vu1sh_skin(p, (const float *const (*)[4])rows, w, nb, p);
        }
        out[i][0] = p[0]; out[i][1] = p[1]; out[i][2] = p[2];
    }
    return (int)n;
}

int nr_vu1sh_is_shadow_sig(const uint32_t sig[10])
{
    return sig[4] == 0x01E1000Cu && sig[5] == 0x0185006Au;
}
