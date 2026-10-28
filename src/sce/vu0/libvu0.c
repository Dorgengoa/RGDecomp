/* SPDX-License-Identifier: CC0-1.0 */
/* libvu0: the sceVu0* functions the game calls (census/platform_sdk_surface.tsv,
 * family libvu0, boundary rows that are excluded asm units; docs/BINDINGS.md).
 *
 * Written on the VU0 macro-mode model (include/port/vu0.h): every COP2
 * instruction of the retail routine is one rg_vu0_* call on the same
 * registers, so the results carry the VU rounding rules (round toward zero,
 * clamp, no denormals) AND the global register file is left exactly as the
 * hardware leaves it (game code reads vf registers set by earlier routines).
 * EE-side MMI moves (lq/sq, pextlw/pcpyld transposes) are plain 16-byte
 * copies and lane shuffles; the EE GPRs they use are not part of the model.
 * The FPU prologue of the RotMatrix* family (angle -> pi/2 -+ angle) is IEEE
 * single arithmetic on the host, the accepted EE-FPU approximation.
 *
 * Sony's names are kept (the game calls them unsuffixed). */
#include "sce_vu0.h"

#include <string.h>

/* lqc2/sqc2 with an offset */
#define LQ(vf, p, off) rg_vu0_lqc2((vf), (const char *)(p) + (off))
#define SQ(vf, p, off) rg_vu0_sqc2((vf), (char *)(p) + (off))
#define FMAC(op, m, d, s, t, bc) rg_vu0_fmac(RG_##op, (m), (d), (s), (t), (bc))
#define X RG_BC_X
#define Y RG_BC_Y
#define Z RG_BC_Z
#define W RG_BC_W
#define NB RG_BC_NONE

/* qmtc2 of an FPU value: the low word of the GPR is the float, the upper
 * 96 bits are whatever mfc1 sign-extension left (bits 63:32 = sign of the
 * float bits, 127:64 = untouched GPR contents).  Only lane x is ever read
 * by these routines; lanes y/z/w are set like mfc1 + qmtc2 would (y = sign
 * extension, z/w = 0, the model's view of an untouched GPR). */
static void qmtc2_float(rg_vu0_state *rg_vu0_p_, int vf, float f)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    rg_vu0_mfc1(8, f);
    rg_vu0_qmtc2(8, vf);

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* ---- vectors ------------------------------------------------------------ */

void sceVu0AddVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2)
{ RG_VU0_FRAME;
    LQ(4, v1, 0);
    LQ(5, v2, 0);
    FMAC(VADD, RG_XYZW, 6, 4, 5, NB);
    SQ(6, v0, 0);
}

void sceVu0SubVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2)
{ RG_VU0_FRAME;
    LQ(4, v1, 0);
    LQ(5, v2, 0);
    FMAC(VSUB, RG_XYZW, 6, 4, 5, NB);
    SQ(6, v0, 0);
}

void sceVu0ScaleVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, float t)
{ RG_VU0_FRAME;
    LQ(4, v1, 0);
    qmtc2_float(&rg_vu0, 5, t);
    FMAC(VMUL, RG_XYZW, 6, 4, 5, X);
    SQ(6, v0, 0);
}

void sceVu0ScaleVectorXYZ(sceVu0FVECTOR v0, sceVu0FVECTOR v1, float t)
{ RG_VU0_FRAME;
    LQ(4, v1, 0);
    qmtc2_float(&rg_vu0, 5, t);
    FMAC(VMUL, RG_XYZ, 4, 4, 5, X);
    SQ(4, v0, 0);
}

/* v0 = v1 * (1 / t): vdiv Q = vf0.w / t, then vmulq (two roundings) */
void sceVu0DivVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, float t)
{ RG_VU0_FRAME;
    LQ(4, v1, 0);
    qmtc2_float(&rg_vu0, 5, t);
    rg_vu0_div(0, 3, 5, 0);
    rg_vu0_waitq();
    FMAC(VMUL, RG_XYZW, 4, 4, RG_FT_Q, NB);
    SQ(4, v0, 0);
}

/* v0 = v1 * t + v2 * (1 - t) */
void sceVu0InterVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2, float t)
{ RG_VU0_FRAME;
    LQ(4, v1, 0);
    LQ(5, v2, 0);
    qmtc2_float(&rg_vu0, 6, t);
    FMAC(VADD, RG_X, 7, 0, 0, W);
    FMAC(VSUB, RG_X, 8, 7, 6, NB);
    FMAC(VMULA, RG_XYZW, 0, 4, 6, X);
    FMAC(VMADD, RG_XYZW, 9, 5, 8, X);
    SQ(9, v0, 0);
}

/* The game declares it void and int; it returns nothing ($v0 untouched).
 * Returning dst in EAX keeps both kinds of caller defined. */
void *sceVu0CopyVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1)
{
    memmove(v0, v1, 16); /* lq $6 / sq $6 */
    return v0;
}

/* (x*x' + y*y') + z*z', each step VU-rounded */
float sceVu0InnerProduct(sceVu0FVECTOR v0, sceVu0FVECTOR v1)
{ RG_VU0_FRAME;
    LQ(4, v0, 0);
    LQ(5, v1, 0);
    FMAC(VMUL, RG_XYZ, 5, 4, 5, NB);
    FMAC(VADD, RG_X, 5, 5, 5, Y);
    FMAC(VADD, RG_X, 5, 5, 5, Z);
    return rg_vu0.vf[5].f[0]; /* qmfc2 $2, vf5; mtc1 $2, $f0 */
}

/* v0 = v1 x v2, w = 0 */
void sceVu0OuterProduct(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2)
{ RG_VU0_FRAME;
    LQ(4, v1, 0);
    LQ(5, v2, 0);
    rg_vu0_opmula(4, 5);
    rg_vu0_opmsub(6, 5, 4);
    FMAC(VSUB, RG_W, 6, 6, 6, NB);
    SQ(6, v0, 0);
}

/* ---- matrices ----------------------------------------------------------- */

void sceVu0CopyMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1)
{
    memmove(m0, m1, 64); /* 4 x lq / 4 x sq; all loads before the stores */
}

/* m0 = m1 * m2 (column-vector convention: row i of the result is
 * m1 applied to row i of m2) */
void sceVu0MulMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, sceVu0FMATRIX m2)
{ RG_VU0_FRAME;
    int i;
    LQ(4, m1, 0x00);
    LQ(5, m1, 0x10);
    LQ(6, m1, 0x20);
    LQ(7, m1, 0x30);
    for (i = 0; i < 4; i++) {
        LQ(8, m2, i * 16);
        FMAC(VMULA, RG_XYZW, 0, 4, 8, X);
        FMAC(VMADDA, RG_XYZW, 0, 5, 8, Y);
        FMAC(VMADDA, RG_XYZW, 0, 6, 8, Z);
        FMAC(VMADD, RG_XYZW, 9, 7, 8, W);
        SQ(9, m0, i * 16);
    }
}

void sceVu0TransposeMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1)
{
    float t[4][4];
    int r, c;
    for (r = 0; r < 4; r++)
        for (c = 0; c < 4; c++)
            t[c][r] = m1[r][c];
    memcpy(m0, t, 64);
}

/* Inverse of a rotation+translation matrix: the 3x3 part transposed (w
 * lanes 0), row 3 = -(R^T * t) with w kept from m1[3][3]. */
void sceVu0InversMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1)
{ RG_VU0_FRAME;
    float r0[4], r1[4], r2[4];
    rg_vf v4;
    /* lq $8..$10 = rows 0..2 (EE side, read before anything is stored) */
    LQ(4, m1, 0x30);
    rg_vu0_move(RG_XYZW, 5, 4);
    FMAC(VSUB, RG_XYZ, 4, 4, 4, NB);
    rg_vu0_move(RG_XYZW, 9, 4);
    v4 = rg_vu0.vf[4]; /* qmfc2 $11, vf4 = (0, 0, 0, m1[3][3]) */
    /* pextlw/pextuw/pcpyld/pcpyud: the transposed 3x3 with w = $11 lanes */
    r0[0] = m1[0][0]; r0[1] = m1[1][0]; r0[2] = m1[2][0]; r0[3] = v4.f[0];
    r1[0] = m1[0][1]; r1[1] = m1[1][1]; r1[2] = m1[2][1]; r1[3] = v4.f[1];
    r2[0] = m1[0][2]; r2[1] = m1[1][2]; r2[2] = m1[2][2]; r2[3] = v4.f[2];
    rg_vu0_lqc2(6, r0);
    rg_vu0_lqc2(7, r1);
    rg_vu0_lqc2(8, r2);
    FMAC(VMULA, RG_XYZ, 0, 6, 5, X);
    FMAC(VMADDA, RG_XYZ, 0, 7, 5, Y);
    FMAC(VMADD, RG_XYZ, 4, 8, 5, Z);
    FMAC(VSUB, RG_XYZ, 4, 9, 4, NB);
    memcpy(m0[0], r0, 16);
    memcpy(m0[1], r1, 16);
    memcpy(m0[2], r2, 16);
    SQ(4, m0, 0x30);
}

/* ---- rotations ---------------------------------------------------------- */

/* Sony's sin polynomial constants (S5432), read from retail 0x00445F60. */
static const rg_vf ecossin_k = {.u = {0x362E9C14u, 0xB94FB21Fu, 0x3C08873Eu, 0xBE2AAAA4u}};

/* _sceVu0ecossin: in vf6.x = a (|a| <= pi), $7 = cos sign flag.
 * out vf4 = (s, s, 0, 0) with s = sin(a), then vf4.x = +-sqrt(1 - s*s) (the
 * sign flag makes it sin(rz) for a = pi/2 -+ rz, so vf4 = (sin rz, cos rz)); vf5 = 0. */
static void ecossin(rg_vu0_state *rg_vu0_p_, int neg)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    rg_vu0_lqc2(5, &ecossin_k);
    rg_vu0_mr32(RG_W, 6, 6);
    FMAC(VADD, RG_X, 4, 0, 6, X);
    FMAC(VMUL, RG_X, 6, 6, 6, NB);
    FMAC(VMUL, RG_YZW, 4, 4, 0, X);
    FMAC(VMUL, RG_XYZW, 8, 5, 6, W);
    FMAC(VSUB, RG_XYZW, 5, 0, 0, NB);
    FMAC(VMUL, RG_XYZW, 8, 8, 6, X);
    FMAC(VMUL, RG_XYZ, 8, 8, 6, X);
    FMAC(VADD, RG_X, 4, 4, 8, W);
    FMAC(VMUL, RG_XY, 8, 8, 6, X);
    FMAC(VADD, RG_X, 4, 4, 8, Z);
    FMAC(VMUL, RG_X, 8, 8, 6, X);
    FMAC(VADD, RG_X, 4, 4, 8, Y);
    FMAC(VADD, RG_X, 4, 4, 8, X);
    FMAC(VADD, RG_XY, 4, 5, 4, X);
    FMAC(VMUL, RG_X, 7, 4, 4, NB);
    FMAC(VSUB, RG_W, 7, 0, 7, X);
    rg_vu0_sqrt(7, 3); /* .word 0x4B8703BD = vsqrt Q, vf7w */
    rg_vu0_waitq();
    FMAC(VADD, RG_X, 7, 0, RG_FT_Q, NB);
    if (neg)
        FMAC(VSUB, RG_X, 4, 5, 7, X);
    else
        FMAC(VADD, RG_X, 4, 5, 7, X);

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* angle prologue shared by RotMatrixX/Y/Z: f12 = pi/2 -+ rz, $7 = (rz < 0) */
static void rot_angle(rg_vu0_state *rg_vu0_p_, float rz)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    const float half_pi = rg_u2f(0x3FC90FDBu);
    int neg = rz < 0.0f;
    float a = neg ? half_pi + rz : half_pi - rz;
    qmtc2_float(&rg_vu0, 6, a);
    ecossin(&rg_vu0, neg);

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* m0 = R * m1, R built in vf6..vf9 (columns), applied row by row */
static void rot_apply(rg_vu0_state *rg_vu0_p_, sceVu0FMATRIX m0, sceVu0FMATRIX m1)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    int i;
    for (i = 0; i < 4; i++) {
        LQ(4, m1, i * 16);
        FMAC(VMULA, RG_XYZW, 0, 6, 4, X);
        FMAC(VMADDA, RG_XYZW, 0, 7, 4, Y);
        FMAC(VMADDA, RG_XYZW, 0, 8, 4, Z);
        FMAC(VMADD, RG_XYZW, 5, 9, 4, W);
        SQ(5, m0, i * 16);
    }

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

void sceVu0RotMatrixZ(sceVu0FMATRIX m0, sceVu0FMATRIX m1, float rz)
{ RG_VU0_FRAME;
    rot_angle(&rg_vu0, rz); /* vf4 = (sin, cos, 0, 0), vf5 = 0 */
    rg_vu0_move(RG_XYZW, 6, 5);
    rg_vu0_move(RG_XYZW, 7, 5);
    rg_vu0_move(RG_XYZW, 9, 0);
    FMAC(VSUB, RG_XYZ, 9, 9, 9, NB);
    rg_vu0_mr32(RG_XYZW, 8, 9);
    FMAC(VSUB, RG_ZW, 4, 4, 4, NB);
    FMAC(VADD, RG_Y, 6, 5, 4, X);
    FMAC(VADD, RG_X, 6, 5, 4, Y);
    FMAC(VSUB, RG_X, 7, 5, 4, X);
    FMAC(VADD, RG_Y, 7, 5, 4, Y);
    rot_apply(&rg_vu0, m0, m1);
}

void sceVu0RotMatrixX(sceVu0FMATRIX m0, sceVu0FMATRIX m1, float rx)
{ RG_VU0_FRAME;
    rot_angle(&rg_vu0, rx);
    rg_vu0_move(RG_XYZW, 6, 5);
    rg_vu0_move(RG_XYZW, 7, 5);
    rg_vu0_move(RG_XYZW, 8, 5);
    rg_vu0_move(RG_XYZW, 9, 5);
    FMAC(VADD, RG_X, 6, 5, 0, W);
    FMAC(VADD, RG_W, 9, 5, 0, W);
    FMAC(VSUB, RG_ZW, 4, 4, 4, NB);
    FMAC(VADD, RG_Z, 7, 5, 4, X);
    FMAC(VADD, RG_Y, 7, 5, 4, Y);
    FMAC(VSUB, RG_Y, 8, 5, 4, X);
    FMAC(VADD, RG_Z, 8, 5, 4, Y);
    rot_apply(&rg_vu0, m0, m1);
}

void sceVu0RotMatrixY(sceVu0FMATRIX m0, sceVu0FMATRIX m1, float ry)
{ RG_VU0_FRAME;
    rot_angle(&rg_vu0, ry);
    rg_vu0_move(RG_XYZW, 6, 5);
    rg_vu0_move(RG_XYZW, 7, 5);
    rg_vu0_move(RG_XYZW, 8, 5);
    rg_vu0_move(RG_XYZW, 9, 5);
    FMAC(VADD, RG_Y, 7, 5, 0, W);
    FMAC(VADD, RG_W, 9, 5, 0, W);
    FMAC(VSUB, RG_ZW, 4, 4, 4, NB);
    FMAC(VSUB, RG_Z, 6, 5, 4, X);
    FMAC(VADD, RG_X, 6, 5, 4, Y);
    FMAC(VADD, RG_X, 8, 5, 4, X);
    FMAC(VADD, RG_Z, 8, 5, 4, Y);
    rot_apply(&rg_vu0, m0, m1);
}

/* m0 = RotX(rot.x) * RotY(rot.y) * RotZ(rot.z) * m1 */
void sceVu0RotMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, sceVu0FVECTOR rot)
{
    sceVu0RotMatrixZ(m0, m1, rot[2]);
    sceVu0RotMatrixY(m0, m0, rot[1]);
    sceVu0RotMatrixX(m0, m0, rot[0]);
}
