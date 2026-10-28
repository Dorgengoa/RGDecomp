/* SPDX-License-Identifier: CC0-1.0 */
/* The dominant VU1 model program as plain C: reference semantics
 * (nr_vu1.h, docs/NATIVE-RENDER.md "The model program"). */
#include "nr_vu1.h"

#include <math.h>
#include <string.h>

/* piece signatures (lower words of the first two pairs) */
typedef struct sig2 { uint32_t a, b; int feat; } sig2;
static const sig2 k_sig320[] = { { 0x8000033C, 0x8000033C, 0 } };          /* 0x436CB0 */
static const sig2 k_sig960[] = { { 0x09010067, 0x08820067, 0 },            /* 0x4392C0 rigid */
                                 { 0x400000A1, 0x8000033C, NRV_SKIN } };   /* 0x4393B0 skinned */
static const sig2 k_sig10E0[] = { { 0x08410068, 0x09020068, 0 },           /* 0x43A620 constant */
                                  { 0x09030068, 0x08420068, NRV_VCOL },    /* 0x43AEC0 vertex colour */
                                  { 0x08810067, 0x01C20021, NRV_LIGHT },   /* 0x43A700 directional lights */
                                  { 0x09040068, 0x08430068, NRV_LIGHT | NRV_VCOL } }; /* 0x43B120 lights x vertex colour */
static const sig2 k_sig1900[] = { { 0x08430068, 0x09010067, 0 },                               /* 0x43BC90 */
                                  { 0x09020067, 0x08440068, NRV_GUARD },                       /* 0x43BF60 / 0x43CD40 */
                                  { 0x09050068, 0x08860057, NRV_GUARD | NRV_CULL },            /* 0x43C2B0 */
                                  { 0x09010067, 0x01E40044, NRV_ZSCALE },                      /* 0x43CA90 */
                                  { 0x08440068, 0x09050068, NRV_ZSCALE | NRV_GUARD | NRV_CULL } }; /* 0x43D110 */
static const sig2 k_sig39D0[] = { { 0x01810058, 0x08410067, NRV_UVSCROLL },  /* 0x43E980 */
                                  { 0x01C10040, 0x01840018, NRV_ENVMAP },    /* 0x43EA30 */
                                  { 0x09010067, 0x01C4003C, NRV_REFLECT } }; /* 0x43F100 */

/* kind 0x43F100 (NRV_REFLECT): the reflection map (listing out/nrender/dis/vu1_43F100_*):
 * world = qw60..63 x p, V = normalise(world - qw28), N = qw64..66 x n, d = V.N,
 * u = (V.x - 2 d N.x + 1) / 2, v = (V.z - 2 d N.z + 1) / 2 */
static void reflect_uv(const nr_qw *c, const float p[3], const float n[3], float uv[2])
{
    float w[3], nn[3], l, d;
    int k;
    for (k = 0; k < 3; k++) {
        w[k] = c[60].f[k] * p[0] + c[61].f[k] * p[1] + c[62].f[k] * p[2] + c[63].f[k] - c[NRQ_CAMPOS].f[k];
        nn[k] = c[NRQ_NRMMTX].f[k] * n[0] + c[NRQ_NRMMTX + 1].f[k] * n[1] + c[NRQ_NRMMTX + 2].f[k] * n[2];
    }
    l = sqrtf(w[0] * w[0] + w[1] * w[1] + w[2] * w[2]);
    l = l > 0.0f ? 1.0f / l : 0.0f;
    for (k = 0; k < 3; k++) w[k] *= l;
    d = w[0] * nn[0] + w[1] * nn[1] + w[2] * nn[2];
    d += d;
    uv[0] = (w[0] - d * nn[0] + 1.0f) * 0.5f;
    uv[1] = (w[2] - d * nn[2] + 1.0f) * 0.5f;
}

static int find_sig(const sig2 *t, int n, uint32_t a, uint32_t b)
{
    int i;
    for (i = 0; i < n; i++)
        if (t[i].a == a && t[i].b == b) return t[i].feat;
    return -1;
}

int nr_vu1_variant_from_sig(const uint32_t sig[10])
{
    int f0 = find_sig(k_sig320, 1, sig[0], sig[1]);
    int f1 = find_sig(k_sig960, 2, sig[2], sig[3]);
    int f2 = find_sig(k_sig10E0, 4, sig[4], sig[5]);
    int f3 = find_sig(k_sig1900, 5, sig[6], sig[7]);
    int f4 = find_sig(k_sig39D0, 2, sig[8], sig[9]);
    if (f0 < 0 || f1 < 0 || f2 < 0 || f3 < 0 || f4 < 0) return -1;
    /* 0x43BF60 and 0x43CD40 share their first pairs: CD40 loads 87.z
     * later; the corpus header does not tell them apart, so GUARD alone
     * means "either" and the checker tries both Z rules */
    return f0 | f1 | f2 | f3 | f4;
}

/* the decode pieces' skin weight scale: LOI 0x3B808081 (0.00392157f would be 0x3B808083) */
#define NR_W255 (nr_w255.f)
static const union { uint32_t u; float f; } nr_w255 = { 0x3B808081u };

/* VU ITOF15 / ITOF0 */
static float itof15(int32_t v) { return (float)v * (1.0f / 32768.0f); }

int nr_vu1_batch(const nr_qw *mem, uint32_t top, int variant, nr_vout *out, int max)
{
    const nr_qw *h0 = &mem[top & 1023], *h1 = &mem[(top + 1) & 1023];
    uint32_t n = h0->u[1] & 0x7FFF, i, k;
    uint32_t data = top + 2;
    uint32_t a_nrm = data + h0->u[3], a_uv = data + h1->u[0], a_col = data + h1->u[1], a_skin = data + h1->u[2];
    uint32_t flags87 = mem[NRQ_MAT].u[1];
    const float *ps = mem[NRQ_POSSCALE].f, *us = mem[NRQ_UVSCALE].f;
    const float *ns = mem[NRQ_NRMSCALE].f;
    float mat[4], add[4];
    float env[3][2];          /* 0x43EA30: view(24..26).xy x object rotation (64..66) */
    float lcol[5][4];         /* 0x43A700: light colours x material (33..37) */
    int nb = 0;
    if (n > (uint32_t)max) n = (uint32_t)max;
    if ((variant & NRV_VCOL) && !(variant & NRV_LIGHT)) {
        if (flags87 & 0x100) return -1;    /* the 0x100 path of 0x43AEC0 (not reached in the captures) */
    }
    /* colour stage constants (0x43A620 / 0x43AEC0) */
    {
        float m82[4];
        memcpy(m82, mem[NRQ_COLMUL].f, 16);
        m82[3] *= mem[NRQ_FLAGS].f[3];
        add[0] = mem[NRQ_COLADD].f[0]; add[1] = mem[NRQ_COLADD].f[1]; add[2] = mem[NRQ_COLADD].f[2]; add[3] = 0.0f;
        for (k = 0; k < 4; k++) {
            if (flags87 & 0x200) mat[k] = m82[k] * mem[NRQ_MATCOL2].f[k];
            else mat[k] = m82[k] * mem[NRQ_MATCOL].f[k] + add[k] * 128.0f;
        }
    }
    if (variant & NRV_ENVMAP) {
        for (k = 0; k < 3; k++) {
            const float *rr = mem[NRQ_NRMMTX + k].f;
            env[k][0] = mem[NRQ_VIEW].f[0] * rr[0] + mem[NRQ_VIEW + 1].f[0] * rr[1] + mem[NRQ_VIEW + 2].f[0] * rr[2];
            env[k][1] = mem[NRQ_VIEW].f[1] * rr[0] + mem[NRQ_VIEW + 1].f[1] * rr[1] + mem[NRQ_VIEW + 2].f[1] * rr[2];
        }
    }
    if (variant & NRV_LIGHT) {
        uint32_t c;
        for (k = 0; k < 5; k++)
            for (c = 0; c < 4; c++) lcol[k][c] = mem[NRQ_LIGHTCOL + k].f[c] * mem[NRQ_COLMUL].f[c];
        lcol[4][3] *= mem[NRQ_FLAGS].f[3];
    }
    /* skin: weights per vertex (0x4393B0 jump table by header 1.w) */
    if (variant & NRV_SKIN) {
        uint32_t j = mem[NRQ_BATCH].u[2] ? h1->u[3] : 0;
        /* jump table at 0x960 + 8 * j: j 0 one bone, 2 two, 4 and 6 four (3 bones
         * use the four-weight code), 8 returns at once */
        nb = j == 0 ? 1 : j == 2 ? 2 : (j == 4 || j == 6) ? 4 : 0;
    }
    for (i = 0; i < n; i++) {
        const nr_qw *pq = &mem[(data + i) & 1023];
        float p[4], nrm[3], uv[2], c[4], clip[4], q;
        const nr_qw *nq = &mem[(a_nrm + i) & 1023];
        nr_vout *o = &out[i];
        p[0] = itof15(pq->i[0]) * ps[0];
        p[1] = itof15(pq->i[1]) * ps[1];
        p[2] = itof15(pq->i[2]) * ps[2];
        p[3] = 1.0f;
        nrm[0] = itof15(nq->i[0]) * ns[0];
        nrm[1] = itof15(nq->i[1]) * ns[1];
        nrm[2] = itof15(nq->i[2]) * ns[2];
        if (nb) {
            const nr_qw *si = &mem[(a_skin + 2 * i) & 1023], *sw = &mem[(a_skin + 2 * i + 1) & 1023];
            float acc[3] = { 0, 0, 0 }, nacc[3] = { 0, 0, 0 };
            int b;
            for (b = 0; b < nb; b++) {
                float w = (float)sw->i[b] * NR_W255;
                uint32_t idx = 900 + 2 * (si->u[b] & 0xFFFF);
                const float *r0 = mem[idx & 1023].f, *r1 = mem[(idx + 1) & 1023].f, *r2 = mem[(idx + 2) & 1023].f,
                            *r3 = mem[(idx + 3) & 1023].f;
                float x = p[0] * w, y = p[1] * w, z = p[2] * w;
                acc[0] += r0[0] * x + r1[0] * y + r2[0] * z + r3[0] * w;
                acc[1] += r0[1] * x + r1[1] * y + r2[1] * z + r3[1] * w;
                acc[2] += r0[2] * x + r1[2] * y + r2[2] * z + r3[2] * w;
                x = nrm[0] * w; y = nrm[1] * w; z = nrm[2] * w;
                nacc[0] += r0[0] * x + r1[0] * y + r2[0] * z;
                nacc[1] += r0[1] * x + r1[1] * y + r2[1] * z;
                nacc[2] += r0[2] * x + r1[2] * y + r2[2] * z;
            }
            p[0] = acc[0]; p[1] = acc[1]; p[2] = acc[2];
            nrm[0] = nacc[0]; nrm[1] = nacc[1]; nrm[2] = nacc[2];
        }
        {
            const nr_qw *uq = &mem[(a_uv + i) & 1023];
            uv[0] = itof15(uq->i[0]) * us[0];
            uv[1] = itof15(uq->i[1]) * us[1];
            if (variant & NRV_UVSCROLL) { uv[0] += mem[NRQ_UVOFS].f[0]; uv[1] += mem[NRQ_UVOFS].f[1]; }
            if (variant & NRV_ENVMAP) {
                uv[0] = (env[0][0] * nrm[0] + env[1][0] * nrm[1] + env[2][0] * nrm[2] + 1.0f) * 0.5f;
                uv[1] = (env[0][1] * nrm[0] + env[1][1] * nrm[1] + env[2][1] * nrm[2] + 1.0f) * 0.5f;
            }
            if (variant & NRV_REFLECT) reflect_uv(mem, p, nrm, uv);
        }
        if (variant & NRV_LIGHT) {
            float d[4];
            for (k = 0; k < 4; k++) {
                d[k] = mem[NRQ_LIGHTDIR].f[k] * nrm[0] + mem[NRQ_LIGHTDIR + 1].f[k] * nrm[1] +
                       mem[NRQ_LIGHTDIR + 2].f[k] * nrm[2];
                if (d[k] < 0.0f) d[k] = 0.0f;
            }
            for (k = 0; k < 3; k++)
                c[k] = lcol[4][k] + lcol[0][k] * d[0] + lcol[1][k] * d[1] + lcol[2][k] * d[2] + lcol[3][k] * d[3];
            c[3] = lcol[4][3];
            if (variant & NRV_VCOL) {
                /* 0x43B120: lights x vertex colour / 128, or (87.y & 0x100) lights + vertex colour;
                 * alpha = ambient alpha x vertex alpha / 128 either way */
                const nr_qw *cq = &mem[(a_col + i) & 1023];
                float vc[4];
                for (k = 0; k < 4; k++) vc[k] = itof15(cq->i[k]) * 256.0f;
                for (k = 0; k < 3; k++) c[k] = (flags87 & 0x100) ? c[k] + vc[k] * 128.0f : c[k] * vc[k];
                c[3] *= vc[3];
            }
        } else if (variant & NRV_VCOL) {
            const nr_qw *cq = &mem[(a_col + i) & 1023];
            for (k = 0; k < 4; k++) c[k] = mat[k] * (itof15(cq->i[k]) * 256.0f);
        } else {
            for (k = 0; k < 4; k++) c[k] = mat[k];
        }
        for (k = 0; k < 4; k++) {
            float cl = mem[NRQ_COLCLAMP].f[k];
            if (c[k] > cl) c[k] = cl;
        }
        for (k = 0; k < 4; k++)
            clip[k] = mem[NRQ_SCREEN].f[k] * p[0] + mem[NRQ_SCREEN + 1].f[k] * p[1] +
                      mem[NRQ_SCREEN + 2].f[k] * p[2] + mem[NRQ_SCREEN + 3].f[k];
        q = 1.0f / clip[3];
        o->sx = clip[0] * q;
        o->sy = clip[1] * q;
        o->sz = clip[2] * q;
        if (variant & NRV_ZSCALE) {
            o->sz *= mem[NRQ_MAT].f[2];
            if (o->sz > mem[NRQ_ZMAX].f[1]) o->sz = mem[NRQ_ZMAX].f[1];
        }
        {
            const float *fg = mem[NRQ_FOG].f;
            float f = fg[0] + fg[3] * clip[3];
            if (f > fg[1]) f = fg[1];
            if (f < fg[2]) f = fg[2];
            o->fog = f;
        }
        memcpy(o->clip, clip, sizeof clip);
        o->r = c[0]; o->g = c[1]; o->b = c[2]; o->a = c[3];
        o->s = uv[0] * q; o->t = uv[1] * q; o->q = q;
        o->adc = 0;
    }
    return (int)n;
}

/* The native pipeline's per-vertex math (nr_draw.hlsl VS_nr, transcribed),
 * from a decoded vertex instead of VU memory: the in-game check
 * (RG_RENDER=verify, docs "Verification") compares it with the VU1 program's
 * output for the same mesh and constants. */
int nr_vu1_vertex(const nr_qw *c, const nr_qw *bones768, int variant, const int16_t pos[3], const int8_t nrm[3],
                  const int16_t uvb[2], const uint8_t col[4], const uint8_t bone[4], const uint8_t wgt[4],
                  nr_vout *o)
{
    float p[3], n[3], uv[2], cc[4], mat[4], clip[4], q;
    int k;
    for (k = 0; k < 3; k++) {
        p[k] = (float)pos[k] * (1.0f / 32768.0f) * c[NRQ_POSSCALE].f[k];
        n[k] = (float)nrm[k] * (1.0f / 32768.0f) * c[NRQ_NRMSCALE].f[k];
    }
    if (variant & NRV_SKIN) {
        float ap[3] = { 0, 0, 0 }, an[3] = { 0, 0, 0 };
        int b;
        for (b = 0; b < 4; b++) {
            float w = (float)wgt[b] * NR_W255;
            const float *r0, *r1, *r2, *r3;
            if (w == 0.0f) continue;
            r0 = bones768[bone[b]].f; r1 = bones768[bone[b] + 1].f; r2 = bones768[bone[b] + 2].f; r3 = bones768[bone[b] + 3].f;
            for (k = 0; k < 3; k++) {
                ap[k] += r0[k] * p[0] * w + r1[k] * p[1] * w + r2[k] * p[2] * w + r3[k] * w;
                an[k] += r0[k] * n[0] * w + r1[k] * n[1] * w + r2[k] * n[2] * w;
            }
        }
        for (k = 0; k < 3; k++) { p[k] = ap[k]; n[k] = an[k]; }
    }
    uv[0] = (float)uvb[0] * (1.0f / 32768.0f) * c[NRQ_UVSCALE].f[0];
    uv[1] = (float)uvb[1] * (1.0f / 32768.0f) * c[NRQ_UVSCALE].f[1];
    if (variant & NRV_UVSCROLL) { uv[0] += c[NRQ_UVOFS].f[0]; uv[1] += c[NRQ_UVOFS].f[1]; }
    {
        float m82[4];
        memcpy(m82, c[NRQ_COLMUL].f, 16);
        m82[3] *= c[NRQ_FLAGS].f[3];
        for (k = 0; k < 4; k++) {
            if (c[NRQ_MAT].u[1] & 0x200) mat[k] = m82[k] * c[NRQ_MATCOL2].f[k];
            else mat[k] = m82[k] * c[NRQ_MATCOL].f[k] + (k < 3 ? c[NRQ_COLADD].f[k] : 0.0f) * 128.0f;
        }
    }
    if (variant & NRV_ENVMAP) {
        float e[3][2];
        for (k = 0; k < 3; k++) {
            const float *rr = c[NRQ_NRMMTX + k].f;
            e[k][0] = c[NRQ_VIEW].f[0] * rr[0] + c[NRQ_VIEW + 1].f[0] * rr[1] + c[NRQ_VIEW + 2].f[0] * rr[2];
            e[k][1] = c[NRQ_VIEW].f[1] * rr[0] + c[NRQ_VIEW + 1].f[1] * rr[1] + c[NRQ_VIEW + 2].f[1] * rr[2];
        }
        uv[0] = (e[0][0] * n[0] + e[1][0] * n[1] + e[2][0] * n[2] + 1.0f) * 0.5f;
        uv[1] = (e[0][1] * n[0] + e[1][1] * n[1] + e[2][1] * n[2] + 1.0f) * 0.5f;
    }
    if (variant & NRV_REFLECT) reflect_uv(c, p, n, uv);
    if (variant & NRV_LIGHT) {
        float d[4];
        for (k = 0; k < 4; k++) {
            d[k] = c[NRQ_LIGHTDIR].f[k] * n[0] + c[NRQ_LIGHTDIR + 1].f[k] * n[1] + c[NRQ_LIGHTDIR + 2].f[k] * n[2];
            if (d[k] < 0.0f) d[k] = 0.0f;
        }
        for (k = 0; k < 3; k++) {
            float m = c[NRQ_COLMUL].f[k];
            cc[k] = c[NRQ_LIGHTCOL + 4].f[k] * m + c[NRQ_LIGHTCOL].f[k] * m * d[0] + c[NRQ_LIGHTCOL + 1].f[k] * m * d[1] +
                    c[NRQ_LIGHTCOL + 2].f[k] * m * d[2] + c[NRQ_LIGHTCOL + 3].f[k] * m * d[3];
        }
        cc[3] = c[NRQ_LIGHTCOL + 4].f[3] * c[NRQ_COLMUL].f[3] * c[NRQ_FLAGS].f[3];
        if (variant & NRV_VCOL) {   /* 0x43B120 (nr_vu1_batch) */
            float vc[4];
            for (k = 0; k < 4; k++) vc[k] = (float)col[k] * (256.0f / 32768.0f);
            for (k = 0; k < 3; k++) cc[k] = (c[NRQ_MAT].u[1] & 0x100) ? cc[k] + vc[k] * 128.0f : cc[k] * vc[k];
            cc[3] *= vc[3];
        }
    } else if (variant & NRV_VCOL) {
        for (k = 0; k < 4; k++) cc[k] = mat[k] * ((float)col[k] * (256.0f / 32768.0f));
    } else {
        for (k = 0; k < 4; k++) cc[k] = mat[k];
    }
    if (variant & NRV_REFRACT) {
        /* kind 0x43ECD0: the vertex through the clip matrix (xyw), around the
         * object origin (qw75 / qw75.w), y flipped, scaled by 82.z, offset by
         * (82.xy - 1) * 0.05, to 0..1; output 0x43E380: RGB 128 */
        float cx = c[NRQ_CLIP].f[0] * p[0] + c[NRQ_CLIP + 1].f[0] * p[1] + c[NRQ_CLIP + 2].f[0] * p[2] + c[NRQ_CLIP + 3].f[0];
        float cy = c[NRQ_CLIP].f[1] * p[0] + c[NRQ_CLIP + 1].f[1] * p[1] + c[NRQ_CLIP + 2].f[1] * p[2] + c[NRQ_CLIP + 3].f[1];
        float cw = c[NRQ_CLIP].f[3] * p[0] + c[NRQ_CLIP + 1].f[3] * p[1] + c[NRQ_CLIP + 2].f[3] * p[2] + c[NRQ_CLIP + 3].f[3];
        float qc = 1.0f / cw, qo = 1.0f / c[NRQ_CLIP + 3].f[3];
        float ox = c[NRQ_CLIP + 3].f[0] * qo, oy = -(c[NRQ_CLIP + 3].f[1] * qo);
        float kz = c[NRQ_COLMUL].f[2];
        float fx = (c[NRQ_COLMUL].f[0] - 1.0f) * 0.05f + ox, fy = (c[NRQ_COLMUL].f[1] - 1.0f) * 0.05f + oy;
        uv[0] = ((cx * qc - ox) * kz + fx + 1.0f) * 0.5f;
        uv[1] = ((-(cy * qc) - oy) * kz + fy + 1.0f) * 0.5f;
        cc[0] = cc[1] = cc[2] = 128.0f;
    }
    for (k = 0; k < 4; k++) if (cc[k] > c[NRQ_COLCLAMP].f[k]) cc[k] = c[NRQ_COLCLAMP].f[k];
    for (k = 0; k < 4; k++)
        clip[k] = c[NRQ_SCREEN].f[k] * p[0] + c[NRQ_SCREEN + 1].f[k] * p[1] + c[NRQ_SCREEN + 2].f[k] * p[2] + c[NRQ_SCREEN + 3].f[k];
    q = 1.0f / clip[3];
    o->sx = clip[0] * q; o->sy = clip[1] * q; o->sz = clip[2] * q;
    if (variant & (NRV_ZSCALE | NRV_REFRACT)) {
        o->sz *= c[NRQ_MAT].f[2];
        if (o->sz > c[NRQ_ZMAX].f[1]) o->sz = c[NRQ_ZMAX].f[1];
    }
    {
        const float *fg = c[NRQ_FOG].f;
        float f = fg[0] + fg[3] * clip[3];
        if (f > fg[1]) f = fg[1];
        if (f < fg[2]) f = fg[2];
        o->fog = f;
    }
    memcpy(o->clip, clip, sizeof clip);
    o->r = cc[0]; o->g = cc[1]; o->b = cc[2]; o->a = cc[3];
    o->s = uv[0] * q; o->t = uv[1] * q; o->q = q;
    if (variant & NRV_REFRACT) { o->s = uv[0]; o->t = uv[1]; o->q = 1.0f; }   /* STQ (u, v, 1) */
    o->adc = 0;
    return 0;
}
