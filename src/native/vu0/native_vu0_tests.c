/* SPDX-License-Identifier: CC0-1.0 */
/* native_vu0.libvu0: src/native/vu0/libvu0_native.c (plain C lanes, compiled here
 * with RG_VU0N_TEST: rg_vu0n_* names) against src/sce/vu0/libvu0.c (the COP2
 * transcription on the VU register struct, rg_sce_vu0 in the same RG_VU0_MODE):
 * every output word must be bit-identical, on random vectors / matrices / angles
 * and on edge values (signed zeros, denormals, exponent-255 words, huge, tiny).
 * Also every aliasing form the game uses (dst == src).  `--wrong` flips one
 * output bit of the native side (the control must fail). */
#include "sce_vu0.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define N(n) rg_vu0n_##n
void N(AddVector)(sceVu0FVECTOR, sceVu0FVECTOR, sceVu0FVECTOR);
void N(SubVector)(sceVu0FVECTOR, sceVu0FVECTOR, sceVu0FVECTOR);
void N(ScaleVector)(sceVu0FVECTOR, sceVu0FVECTOR, float);
void N(ScaleVectorXYZ)(sceVu0FVECTOR, sceVu0FVECTOR, float);
void N(DivVector)(sceVu0FVECTOR, sceVu0FVECTOR, float);
void N(InterVector)(sceVu0FVECTOR, sceVu0FVECTOR, sceVu0FVECTOR, float);
void *N(CopyVector)(sceVu0FVECTOR, sceVu0FVECTOR);
float N(InnerProduct)(sceVu0FVECTOR, sceVu0FVECTOR);
void N(OuterProduct)(sceVu0FVECTOR, sceVu0FVECTOR, sceVu0FVECTOR);
void N(CopyMatrix)(sceVu0FMATRIX, sceVu0FMATRIX);
void N(MulMatrix)(sceVu0FMATRIX, sceVu0FMATRIX, sceVu0FMATRIX);
void N(TransposeMatrix)(sceVu0FMATRIX, sceVu0FMATRIX);
void N(InversMatrix)(sceVu0FMATRIX, sceVu0FMATRIX);
void N(RotMatrixX)(sceVu0FMATRIX, sceVu0FMATRIX, float);
void N(RotMatrixY)(sceVu0FMATRIX, sceVu0FMATRIX, float);
void N(RotMatrixZ)(sceVu0FMATRIX, sceVu0FMATRIX, float);
void N(RotMatrix)(sceVu0FMATRIX, sceVu0FMATRIX, sceVu0FVECTOR);

static uint32_t g_rng = 0x12345678u;
static int g_wrong, g_fail, g_checks;

static uint32_t rnd(void)
{
    g_rng ^= g_rng << 13;
    g_rng ^= g_rng >> 17;
    g_rng ^= g_rng << 5;
    return g_rng;
}

static const uint32_t k_edge[] = {
    0x00000000u, 0x80000000u, 0x3F800000u, 0xBF800000u, 0x00000001u, 0x807FFFFFu,
    0x7F7FFFFFu, 0xFF7FFFFFu, 0x7F800000u, 0x7FFFFFFFu, 0xFFFFFFFFu, 0x4B400000u,
    0xCB400000u, 0x00800000u, 0x3FC90FDBu, 0xC0490FDBu, 0x5F000000u, 0x20000000u,
};

static float rf(int edge)
{
    uint32_t u;
    float f;
    if (edge && (rnd() & 3) == 0)
        u = k_edge[rnd() % (sizeof k_edge / sizeof k_edge[0])];
    else {
        f = (float)((int32_t)rnd() % 200000) / 1000.0f;   /* -200..200 */
        return f;
    }
    memcpy(&f, &u, 4);
    return f;
}

static float rangle(int edge)
{
    if (edge && (rnd() & 7) == 0)
        return rf(1);
    return (float)((int32_t)rnd() % 31416) / 10000.0f;     /* |a| < pi */
}

static void fill(float *p, int n, int edge)
{
    int i;
    for (i = 0; i < n; i++)
        p[i] = rf(edge);
}

static void cmp(const char *what, int iter, const void *a, const void *b, int nwords)
{
    uint32_t x[16], y[16];
    int i;
    memcpy(x, a, (size_t)nwords * 4);
    memcpy(y, b, (size_t)nwords * 4);
    if (g_wrong && iter == 7)
        x[0] ^= 1;
    g_checks++;
    for (i = 0; i < nwords; i++)
        if (x[i] != y[i]) {
            if (g_fail < 20)
                fprintf(stderr, "%s iter %d word %d: native 0x%08X libvu0 0x%08X\n", what, iter, i,
                        x[i], y[i]);
            g_fail++;
            return;
        }
}

int main(int argc, char **argv)
{
    int it;
    g_wrong = argc > 1 && !strcmp(argv[1], "--wrong");
    for (it = 0; it < 20000; it++) {
        int edge = it >= 10000;
        sceVu0FVECTOR a, b, ra, rb, rot;
        sceVu0FMATRIX m1, m2, ma, mb;
        float t = rf(edge), ang = rangle(edge);
        fill(a, 4, edge);
        fill(b, 4, edge);
        fill(&m1[0][0], 16, edge);
        fill(&m2[0][0], 16, edge);
        rot[0] = rangle(edge);
        rot[1] = rangle(edge);
        rot[2] = rangle(edge);
        rot[3] = 0;

#define V2(f) N(f)(ra, a, b); sceVu0##f(rb, a, b); cmp(#f, it, ra, rb, 4)
#define VT(f) N(f)(ra, a, t); sceVu0##f(rb, a, t); cmp(#f, it, ra, rb, 4)
        V2(AddVector);
        V2(SubVector);
        V2(OuterProduct);
        VT(ScaleVector);
        VT(DivVector);
        memcpy(ra, b, 16);
        memcpy(rb, b, 16);
        VT(ScaleVectorXYZ);
        N(InterVector)(ra, a, b, t);
        sceVu0InterVector(rb, a, b, t);
        cmp("InterVector", it, ra, rb, 4);
        {
            float x = N(InnerProduct)(a, b), y = sceVu0InnerProduct(a, b);
            cmp("InnerProduct", it, &x, &y, 1);
        }
        /* in place */
        memcpy(ra, a, 16);
        memcpy(rb, a, 16);
        N(AddVector)(ra, ra, ra);
        sceVu0AddVector(rb, rb, rb);
        cmp("AddVector(a,a,a)", it, ra, rb, 4);

#define M2(f) N(f)(ma, m1, m2); sceVu0##f(mb, m1, m2); cmp(#f, it, ma, mb, 16)
        M2(MulMatrix);
        memcpy(ma, m1, 64);
        memcpy(mb, m1, 64);
        N(MulMatrix)(ma, ma, ma);
        sceVu0MulMatrix(mb, mb, mb);
        cmp("MulMatrix(m,m,m)", it, ma, mb, 16);
        N(TransposeMatrix)(ma, m1);
        sceVu0TransposeMatrix(mb, m1);
        cmp("TransposeMatrix", it, ma, mb, 16);
        N(InversMatrix)(ma, m1);
        sceVu0InversMatrix(mb, m1);
        cmp("InversMatrix", it, ma, mb, 16);
        memcpy(ma, m1, 64);
        memcpy(mb, m1, 64);
        N(InversMatrix)(ma, ma);
        sceVu0InversMatrix(mb, mb);
        cmp("InversMatrix(m,m)", it, ma, mb, 16);
        N(CopyMatrix)(ma, m1);
        sceVu0CopyMatrix(mb, m1);
        cmp("CopyMatrix", it, ma, mb, 16);
        N(CopyVector)(ra, a);
        sceVu0CopyVector(rb, a);
        cmp("CopyVector", it, ra, rb, 4);

#define MR(f) N(f)(ma, m1, ang); sceVu0##f(mb, m1, ang); cmp(#f, it, ma, mb, 16)
        MR(RotMatrixX);
        MR(RotMatrixY);
        MR(RotMatrixZ);
        N(RotMatrix)(ma, m1, rot);
        sceVu0RotMatrix(mb, m1, rot);
        cmp("RotMatrix", it, ma, mb, 16);
        memcpy(ma, m1, 64);
        memcpy(mb, m1, 64);
        N(RotMatrix)(ma, ma, rot);
        sceVu0RotMatrix(mb, mb, rot);
        cmp("RotMatrix(m,m)", it, ma, mb, 16);
    }
    printf("native_vu0.libvu0: %d comparisons, %d mismatches\n", g_checks, g_fail);
    return g_fail ? 1 : 0;
}
