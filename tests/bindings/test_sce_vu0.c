/* SPDX-License-Identifier: CC0-1.0 */
/* src/sce/vu0 libvu0 functions vs hand-computed values, including the VU
 * rounding rules (round toward zero) and the register-file side effects. */
#include "bt.h"
#include "sce_vu0.h"

#include <math.h>
#include <string.h>

static void setv(sceVu0FVECTOR v, float x, float y, float z, float w)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

static void unit(sceVu0FMATRIX m)
{
    memset(m, 0, 64);
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
}

int bt_sce_vu0(void)
{
    int f = 0;
    sceVu0FVECTOR a, b, r;
    sceVu0FMATRIX m1, m2, m0;

    setv(a, 1, 2, 3, 4);
    setv(b, 5, 6, 7, 8);
    sceVu0AddVector(r, a, b);
    BT_FBITS(f, r[0], 6.0f);
    BT_FBITS(f, r[3], 12.0f);
    /* the hardware leaves the sum in vf6 and the operands in vf4/vf5 */
    BT_FBITS(f, rg_vu0.vf[6].f[2], 10.0f);
    BT_FBITS(f, rg_vu0.vf[5].f[0], 5.0f);

    sceVu0SubVector(r, a, b);
    BT_FBITS(f, r[1], -4.0f);

    sceVu0ScaleVector(r, a, 0.5f);
    BT_FBITS(f, r[3], 2.0f);
    setv(r, 9, 9, 9, 9);
    sceVu0ScaleVectorXYZ(r, a, 3.0f);
    BT_FBITS(f, r[2], 9.0f);
    BT_FBITS(f, r[3], 4.0f); /* w is the source's, unscaled */

    /* 1/3 on the VU truncates: 0x3EAAAAAA, IEEE would round to ...AB */
    setv(a, 1, 1, 1, 1);
    sceVu0DivVector(r, a, 3.0f);
    {
        unsigned bits;
        memcpy(&bits, &r[0], 4);
        BT_EQ(f, bits, BT_WRONG(0x3EAAAAAAu));
    }

    setv(a, 1, 2, 3, 99);
    setv(b, 4, 5, 6, 99);
    BT_FBITS(f, sceVu0InnerProduct(a, b), 32.0f);

    setv(a, 1, 0, 0, 7);
    setv(b, 0, 1, 0, 7);
    sceVu0OuterProduct(r, a, b);
    BT_FBITS(f, r[0], 0.0f);
    BT_FBITS(f, r[2], 1.0f);
    BT_FBITS(f, r[3], 0.0f);
    setv(a, 2, 3, 4, 0);
    setv(b, 5, 6, 7, 0);
    sceVu0OuterProduct(r, a, b); /* (3*7-4*6, 4*5-2*7, 2*6-3*5) */
    BT_FBITS(f, r[0], -3.0f);
    BT_FBITS(f, r[1], 6.0f);
    BT_FBITS(f, r[2], -3.0f);

    /* v1*t + v2*(1-t) */
    setv(a, 8, 0, 4, 1);
    setv(b, 0, 8, 4, 1);
    sceVu0InterVector(r, a, b, 0.25f);
    BT_FBITS(f, r[0], 2.0f);
    BT_FBITS(f, r[1], 6.0f);
    BT_FBITS(f, r[2], 4.0f);

    setv(a, 1, 2, 3, 4);
    sceVu0CopyVector(r, a);
    BT_FBITS(f, r[3], 4.0f);

    /* MulMatrix: row i = m1 applied to row i of m2 */
    unit(m1);
    m1[0][0] = 2;
    m1[1][1] = 3;
    m1[2][2] = 4;
    setv(m1[3], 10, 20, 30, 1);
    unit(m2);
    setv(m2[3], 5, 6, 7, 1);
    sceVu0MulMatrix(m0, m1, m2);
    BT_FBITS(f, m0[3][0], 20.0f);
    BT_FBITS(f, m0[3][1], 38.0f);
    BT_FBITS(f, m0[3][2], 58.0f);
    BT_FBITS(f, m0[3][3], 1.0f);
    BT_FBITS(f, m0[1][1], 3.0f);

    for (int i = 0; i < 16; i++)
        (&m1[0][0])[i] = (float)i;
    sceVu0TransposeMatrix(m0, m1);
    BT_FBITS(f, m0[0][1], 4.0f);
    BT_FBITS(f, m0[3][2], 11.0f);
    sceVu0TransposeMatrix(m1, m1); /* in place */
    BT_FBITS(f, m1[2][0], 2.0f);

    /* inverse of (Rz(90) | t=(5,6,7)) */
    memset(m1, 0, 64);
    setv(m1[0], 0, 1, 0, 0);
    setv(m1[1], -1, 0, 0, 0);
    setv(m1[2], 0, 0, 1, 0);
    setv(m1[3], 5, 6, 7, 1);
    sceVu0InversMatrix(m0, m1);
    BT_FBITS(f, m0[0][1], -1.0f);
    BT_FBITS(f, m0[1][0], 1.0f);
    BT_FBITS(f, m0[0][3], 0.0f);
    BT_FBITS(f, m0[3][0], -6.0f);
    BT_FBITS(f, m0[3][1], 5.0f);
    BT_FBITS(f, m0[3][2], -7.0f);
    BT_FBITS(f, m0[3][3], 1.0f);
    /* inverse * original = identity on a point */
    sceVu0MulMatrix(m2, m0, m1);
    BT_NEAR(f, m2[3][0], 0.0, 1e-6);
    BT_NEAR(f, m2[0][0], 1.0, 1e-6);

    sceVu0CopyMatrix(m2, m1);
    BT_FBITS(f, m2[3][2], 7.0f);

    /* rotations: Sony's polynomial sin + sqrt cos, compared to libm */
    {
        static const float angles[] = {0.0f, 0.3f, -0.3f, 1.5707963f, -1.5707963f, 2.5f, -3.0f};
        for (unsigned k = 0; k < sizeof angles / sizeof angles[0]; k++) {
            float t = angles[k];
            double c = cos(t), s = sin(t);
            unit(m1);
            sceVu0RotMatrixZ(m0, m1, t);
            BT_NEAR(f, m0[0][0], c, 2e-6);
            BT_NEAR(f, m0[0][1], s, 2e-6);
            BT_NEAR(f, m0[1][0], -s, 2e-6);
            BT_NEAR(f, m0[1][1], c, 2e-6);
            BT_FBITS(f, m0[3][3], 1.0f);
            sceVu0RotMatrixX(m0, m1, t);
            BT_NEAR(f, m0[1][1], c, 2e-6);
            BT_NEAR(f, m0[1][2], s, 2e-6);
            BT_NEAR(f, m0[2][1], -s, 2e-6);
            sceVu0RotMatrixY(m0, m1, t);
            BT_NEAR(f, m0[0][0], c, 2e-6);
            BT_NEAR(f, m0[0][2], -s, 2e-6);
            BT_NEAR(f, m0[2][0], s, 2e-6);
        }
        /* RotMatrix = X(rx) * Y(ry) * Z(rz) applied to m1: with only rz set
         * it equals RotMatrixZ */
        setv(a, 0, 0, 0.7f, 0);
        unit(m1);
        sceVu0RotMatrix(m0, m1, a);
        sceVu0RotMatrixZ(m2, m1, 0.7f);
        /* RotMatrixY/X(0) multiply by cos(0) computed as sqrt(1 - s^2) */
        BT_NEAR(f, m0[0][1], m2[0][1], 2e-6);
        BT_NEAR(f, m0[1][0], m2[1][0], 2e-6);
    }
    return f;
}
