/* Every macro of the port include/libvu0.h, with known vectors.  Each macro
 * is a fragment of a Sony-style routine; where the original closes the
 * routine with a C intrinsic (vmaddw/vmaddz/vopmsub ...), the test closes it
 * with the matching rg_vu0_* op and checks the routine's documented result. */
#include <stdio.h>
#include "types.h"
#include "libvu0.h"

#define CHECK(c) do { if (!(c)) { printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); fails++; } } while (0)
#define CHECKV(v, X, Y, Z, W) CHECK((v)[0] == (X) && (v)[1] == (Y) && (v)[2] == (Z) && (v)[3] == (W))

typedef struct { f32 v[4]; } __attribute__((aligned(16))) Q;

static void ld(int vf, f32 x, f32 y, f32 z, f32 w)
{
    Q q = { { x, y, z, w } };
    rg_vu0_lqc2(vf, &q);
}

int test_libvu0(void)
{
    int fails = 0;
    Q a = { { 1, 2, 3, 4 } }, b = { { 5, 6, 7, 8 } }, d;
    Q m[4], o[4];
    f32 r;
    int i;

    /* ---- qword moves */
    Vu0UnitVector(&d);
    CHECKV(d.v, 0, 0, 0, 1);
    Vu0CopyVector(&d, &a);
    CHECKV(d.v, 1, 2, 3, 4);
    CHECK(rg_vu0.gpr[5][0] == rg_f2u(1.0f));             /* through a1 */
    Vu0SwapVector(&a, &b);
    CHECKV(a.v, 5, 6, 7, 8);
    CHECKV(b.v, 1, 2, 3, 4);
    for (i = 0; i < 4; i++) {
        m[i].v[0] = (f32)i; m[i].v[1] = 10.0f + i; m[i].v[2] = 20.0f + i; m[i].v[3] = 30.0f + i;
    }
    Vu0CopyMatrix(o, m);
    for (i = 0; i < 4; i++)
        CHECKV(o[i].v, (f32)i, 10.0f + i, 20.0f + i, 30.0f + i);

    /* ---- scalar moves */
    Vu0ScaleF(t0, 2.5f, vf6);
    CHECK(rg_vu0.vf[6].f[0] == 2.5f);
    ld(4, 9, 16, 25, 36);
    Vu0Length(r, y);
    CHECK(r == 4.0f);
    Vu0Length(r, w);
    CHECK(r == 6.0f && rg_u2f(rg_vu0.q) == 6.0f);

    /* ---- ACC heads */
    ld(4, 1, 2, 3, 4); ld(6, 3, 0, 0, 0);
    Vu0MulAccX(xyzw, vf4, vf6);
    CHECKV(rg_vu0.acc.f, 3, 6, 9, 12);
    Vu0MulAccX(xyz, vf4, vf6);                            /* w of ACC kept */
    CHECKV(rg_vu0.acc.f, 3, 6, 9, 12);

    /* M * v with rows vf1..vf3 (+vf4 translation): ApplyMatrix3Acc + closing vmaddz */
    ld(1, 1, 0, 0, 0); ld(2, 0, 2, 0, 0); ld(3, 0, 0, 3, 0); ld(4, 10, 20, 30, 1);
    ld(5, 1, 1, 1, 1);
    Vu0ApplyMatrix3Acc(xyz, vf1, vf2, vf5);
    rg_vu0_fmac(RG_VMADD, RG_XYZ, 7, 3, 5, RG_BC_Z);     /* vmaddz.xyz vf7, vf3, vf5z */
    CHECK(rg_vu0.vf[7].f[0] == 1 && rg_vu0.vf[7].f[1] == 2 && rg_vu0.vf[7].f[2] == 3);
    /* full ApplyMatrix: MulMatrixAcc + vmaddw vf7, vf4, vf5w */
    ld(5, 1, 1, 1, 1);
    Vu0MulMatrixAcc(xyzw, vf1, vf2, vf3, vf5);
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 7, 4, 5, RG_BC_W);
    CHECKV(rg_vu0.vf[7].f, 11, 22, 33, 1);
    /* the same closing through vf26 + store */
    Vu0MulMatrixAcc(xyzw, vf1, vf2, vf3, vf5);
    Vu0StoreAccW26(&d);                                   /* + vf4 * vf0w (=1) */
    CHECKV(d.v, 11, 22, 33, 1);

    ld(1, 1, 2, 3, 4); ld(2, 10, 20, 30, 40);
    Vu0AddAcc(vf1, vf2);
    CHECKV(rg_vu0.acc.f, 11, 22, 33, 44);

    /* cross product: OuterProductAcc + vopmsub vf3, b, a */
    ld(1, 1, 2, 3, 0); ld(2, 4, 5, 6, 0);
    Vu0OuterProductAcc(vf1, vf2);
    rg_vu0_opmsub(3, 2, 1);
    CHECK(rg_vu0.vf[3].f[0] == -3 && rg_vu0.vf[3].f[1] == 6 && rg_vu0.vf[3].f[2] == -3);

    /* Sony InterVector in its libvu0 pieces: d = p2 + (p1 - p2) * t */
    {
        Q p1 = { { 1, 1, 1, 1 } }, p2 = { { 3, 5, 7, 9 } };
        Vu0InterVectorLoad(&p2);
        rg_vu0_lqc2(5, &p1);
        Vu0ScaleF(t0, 0.5f, vf6);
        rg_vu0_fmac(RG_VSUB, RG_XYZW, 7, 5, 4, RG_BC_NONE);
        Vu0InterVectorAcc();
        CHECKV(rg_vu0.acc.f, 3, 5, 7, 9);
        rg_vu0_fmac(RG_VMADD, RG_XYZW, 8, 7, 6, RG_BC_X);
        rg_vu0_sqc2(8, &d);
        CHECKV(d.v, 2, 3, 4, 5);
    }

    /* blend: d = a*s + b*t, and the 3-term form */
    ld(4, 1, 2, 3, 4); ld(5, 10, 20, 30, 40); ld(6, 100, 200, 300, 400);
    Vu0BlendVectorF(2.0f, 3.0f);
    Vu0BlendVectorAcc();
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 9, 5, 9, RG_BC_X);     /* vmaddx vf9, vf5, vf9x */
    CHECKV(rg_vu0.vf[9].f, 32, 64, 96, 128);
    Vu0BlendVector3F(1.0f, 2.0f, 0.5f);
    Vu0BlendVector3Acc();
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 11, 6, 10, RG_BC_X);   /* vmaddx vf11, vf6, vf10x */
    CHECKV(rg_vu0.vf[11].f, 71, 142, 213, 284);

    /* orthonormalise step: Q = sqrt(vf8x), vf7.w = 0 */
    ld(8, 16, 0, 0, 0); ld(7, 1, 1, 1, 1);
    Vu0OrthoNormalSqrt(vf7);
    CHECK(rg_u2f(rg_vu0.q) == 4.0f);
    CHECKV(rg_vu0.vf[7].f, 1, 1, 1, 0);

    /* inverse pieces */
    for (i = 0; i < 4; i++) {
        m[i].v[0] = 1.0f + i; m[i].v[1] = 2.0f + i; m[i].v[2] = 3.0f + i; m[i].v[3] = 4.0f + i;
    }
    Vu0InversMatrixLoad(m);
    CHECKV(rg_vu0.vf[1].f, 1, 2, 3, 4);
    CHECKV(rg_vu0.vf[4].f, 4, 5, 6, 7);
    CHECK(rg_vu0_gptr(RG_GPR_a3) == (char *)&m[2]);
    ld(9, 4, 0, 0, 0);
    Vu0InversMatrixDet(r);
    CHECK(r == 4.0f && rg_u2f(rg_vu0.q) == 0.25f);

    /* push-apart pieces (FUN_00364740 family) */
    ld(31, 7, 7, 7, 7);
    Vu0PushApartOne();
    CHECKV(rg_vu0.vf[31].f, 1, 1, 1, 1);
    ld(2, 9, 16, 0, 0);                                   /* squared diff of (3,4,0) */
    Vu0PushApartLen(10.0f, 0.5f);
    CHECK(rg_vu0.vf[6].f[0] == 25.0f && rg_vu0.vf[12].f[0] == 10.0f && rg_vu0.vf[13].f[0] == 0.5f);
    Vu0PushApartRsqrt();
    CHECK(rg_u2f(rg_vu0.q) == 2.0f && rg_vu0.vf[14].f[0] == 0.5f);
    Vu0PushApartSubQ();
    CHECK(rg_vu0.vf[20].f[0] == -1.0f);

    /* sin/cos ACC spans: check the accumulate formulas */
    ld(4, 1, 2, 3, 4); ld(5, 0, 2, 3, 10); ld(8, 1, 1, 1, 1);
    Vu0SinCosAccR();                 /* 2a - 3e + 3e - 2a, step by step */
    CHECKV(rg_vu0.acc.f, 0, 0, 0, 0);
    ld(9, 1, 2, 3, 4); ld(12, 2, 2, 2, 2); ld(10, 1, 1, 1, 1); ld(11, 3, 3, 3, 3); ld(13, 1, 1, 1, 1);
    Vu0SinCosAccP0();
    CHECKV(rg_vu0.acc.f, 2, 4, 6, 8);
    Vu0SinCosAccP1();                /* + 3 + 1 + vf4*10 */
    CHECKV(rg_vu0.acc.f, 16, 28, 40, 52);

    if (fails)
        printf("test_libvu0: %d failures\n", fails);
    return fails == 0;
}
