/* Lane gamecop2: game-scope COP2 overrides (overrides/src/main/{vec,matrix,model,script}/...)
 * vs hand-computed values, including the VU rounding rule (toward zero). */
#include "bt.h"
#include "types.h"

f32 VecDot3_1cba90(void *pa, void *pb);
f32 VecLengthSq_1cb470(void *pv);
f32 VecLength_1cb4c0(void *pv);
void VecCross_1cb9f0(void *pd, void *pa, void *pb);
void VecSub_1cbd00(void *pd, const void *pa, const void *pb);
void VecDivScalar_1cbbf0(void *pd, void *ps, f32 s);
void VecScaleToLength_1cb510(void *pd, void *ps, f32 len);
void MatMul_1cb700(void *pd, void *pa, void *pb);
void VecNormalize_1cbb80(void *pd, void *ps);
f32 MtxInverseAffine_1cb640(void *pd, void *ps);
f32 TriNormalDot_1cb600(void *pa, void *pb, void *pc, void *pn);
void VertsPackQuantized_164bb0(void *dst, void *src, s32 count, s32 mode, void *range);
void VecMinMax_1cb570(void *pmax, void *pmin, void *pa, void *pb);
void VecLerp_1cbb20(void *pd, void *pa, void *pb, f32 t);
void MatMulVec4Args_1cb7f0(void *pd, void *pm, f32 x, f32 y, f32 z, f32 w);
void FixCameraRecInit_193860(void *p);

typedef struct { f32 v[4]; } __attribute__((aligned(16))) BtV;
typedef struct { f32 m[4][4]; } __attribute__((aligned(16))) BtM;

static BtV v4(f32 x, f32 y, f32 z, f32 w)
{
    BtV r;
    r.v[0] = x; r.v[1] = y; r.v[2] = z; r.v[3] = w;
    return r;
}

static void mset(BtM *m, const f32 *rows)
{
    __builtin_memcpy(m->m, rows, 64);
}

static u32 fbits(f32 f)
{
    u32 u;
    __builtin_memcpy(&u, &f, 4);
    return u;
}

int bt_ovr_gamecop2(void)
{
    int f = 0;
    BtV a, b, c, n, r, r2;
    BtM ma, mb, md;

    /* dot / lengths */
    a = v4(1, 2, 3, 9);
    b = v4(4, 5, 6, 9);
    BT_FBITS(f, VecDot3_1cba90(&a, &b), BT_WRONG(32.0f)); /* w ignored */
    BT_FBITS(f, VecLengthSq_1cb470(&a), 14.0f);
    a = v4(3, 4, 0, 100);
    BT_FBITS(f, VecLength_1cb4c0(&a), 5.0f);

    /* cross: x cross y = z, w cleared */
    a = v4(1, 0, 0, 7);
    b = v4(0, 1, 0, 7);
    VecCross_1cb9f0(&r, &a, &b);
    BT_FBITS(f, r.v[0], 0.0f);
    BT_FBITS(f, r.v[1], 0.0f);
    BT_FBITS(f, r.v[2], 1.0f);
    BT_FBITS(f, r.v[3], 0.0f);

    /* sub (the asm-block C file), all four lanes */
    a = v4(5, 7, 9, 1);
    b = v4(1, 2, 3, 1);
    VecSub_1cbd00(&r, &a, &b);
    BT_FBITS(f, r.v[0], 4.0f);
    BT_FBITS(f, r.v[2], 6.0f);
    BT_FBITS(f, r.v[3], 0.0f);

    /* 1/3 on the VU truncates: Q = 0x3EAAAAAA (IEEE would give ...AB) */
    a = v4(1, 1, 1, 1);
    VecDivScalar_1cbbf0(&r, &a, 3.0f);
    BT_EQ(f, fbits(r.v[0]), 0x3EAAAAAAu);
    BT_EQ(f, fbits(r.v[3]), 0x3EAAAAAAu);

    /* scale (3,0,4) to length 10: Q = 10/sqrt(25) = 2 */
    a = v4(3, 0, 4, 0);
    VecScaleToLength_1cb510(&r, &a, 10.0f);
    BT_FBITS(f, r.v[0], 6.0f);
    BT_FBITS(f, r.v[2], 8.0f);

    /* normalize (3,0,4): 1/5 truncates to 0x3E4CCCCC; w cleared */
    a = v4(3, 0, 4, 7);
    VecNormalize_1cbb80(&r, &a);
    BT_NEAR(f, r.v[0], 0.6, 1e-6);
    BT_NEAR(f, r.v[2], 0.8, 1e-6);
    BT_FBITS(f, r.v[3], 0.0f);
    BT_EQ(f, rg_vu0.q, 0x3E4CCCCCu);

    /* MatMul: row k of d = sum_j a[j] * b[k][j]; b rows all ones */
    {
        static const f32 A[16] = { 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1 };
        static const f32 B[16] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4 };
        mset(&ma, A);
        mset(&mb, B);
        MatMul_1cb700(&md, &ma, &mb);
        BT_FBITS(f, md.m[0][0], 2.0f);
        BT_FBITS(f, md.m[0][1], 3.0f);
        BT_FBITS(f, md.m[0][2], 4.0f);
        BT_FBITS(f, md.m[0][3], 1.0f);
        BT_FBITS(f, md.m[3][1], 6.0f);  /* 3 * 2 */
        BT_FBITS(f, md.m[3][2], 12.0f); /* 4 * 3 */
    }

    /* affine inverse of diag(2,4,8) + translation (1,2,3); returns det */
    {
        static const f32 M[16] = { 2, 0, 0, 0, 0, 4, 0, 0, 0, 0, 8, 0, 1, 2, 3, 1 };
        mset(&ma, M);
        BT_FBITS(f, MtxInverseAffine_1cb640(&md, &ma), 64.0f);
        BT_FBITS(f, md.m[0][0], 0.5f);
        BT_FBITS(f, md.m[1][1], 0.25f);
        BT_FBITS(f, md.m[2][2], 0.125f);
        BT_FBITS(f, md.m[3][0], -0.5f);
        BT_FBITS(f, md.m[3][1], -0.5f);
        BT_FBITS(f, md.m[3][2], -0.375f);
        BT_FBITS(f, md.m[3][3], 1.0f);
    }

    /* triangle normal (b-a) x (c-b) = +z, dotted with (0,0,2) */
    a = v4(0, 0, 0, 1);
    b = v4(1, 0, 0, 1);
    c = v4(1, 1, 0, 1);
    n = v4(0, 0, 2, 0);
    BT_FBITS(f, TriNormalDot_1cb600(&a, &b, &c, &n), 2.0f);

    /* min / max: first output is the max */
    a = v4(1, 5, 3, 0);
    b = v4(4, 2, 6, -1);
    VecMinMax_1cb570(&r, &r2, &a, &b);
    BT_FBITS(f, r.v[0], 4.0f);
    BT_FBITS(f, r.v[1], 5.0f);
    BT_FBITS(f, r.v[3], 0.0f);
    BT_FBITS(f, r2.v[1], 2.0f);
    BT_FBITS(f, r2.v[3], -1.0f);

    /* VecLerp(d, a, b, t) = a*t + b*(1-t) */
    a = v4(2, 2, 2, 2);
    b = v4(4, 4, 4, 4);
    VecLerp_1cbb20(&r, &a, &b, 0.25f);
    BT_FBITS(f, r.v[0], 3.5f);
    BT_FBITS(f, r.v[3], 3.5f);

    /* row-vector x matrix with the vector passed as four floats */
    {
        static const f32 M[16] = { 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 10, 20, 30, 1 };
        mset(&ma, M);
        MatMulVec4Args_1cb7f0(&r, &ma, 1.0f, 1.0f, 1.0f, 1.0f);
        BT_FBITS(f, r.v[0], 12.0f);
        BT_FBITS(f, r.v[1], 23.0f);
        BT_FBITS(f, r.v[2], 34.0f);
        BT_FBITS(f, r.v[3], 1.0f);
    }

    /* quantize: s16 (32768 / range), s8 (128 / range), plain copy */
    {
        BtV src[2], range;
        s16 o16[6];
        u8 o8[6];
        f32 o32[6];
        src[0] = v4(0.5f, -0.5f, 0.25f, 0);
        src[1] = v4(1.0f, 0, -1.0f, 0);
        range = v4(1, 2, 4, 1);
        VertsPackQuantized_164bb0(o16, src, 2, 0x10, &range);
        BT_EQ(f, o16[0], 16384);
        BT_EQ(f, o16[1], -8192);
        BT_EQ(f, o16[2], 2048);
        BT_EQ(f, o16[3], -32768); /* 32768 stored as a halfword wraps */
        BT_EQ(f, o16[5], -8192);
        src[0] = v4(0.5f, -1.0f, 0.999f, 0);
        range = v4(1, 1, 1, 1);
        VertsPackQuantized_164bb0(o8, src, 1, 8, &range);
        BT_EQ(f, o8[0], 64);
        BT_EQ(f, o8[1], 0x80);
        BT_EQ(f, o8[2], 127); /* 127.87 truncates */
        VertsPackQuantized_164bb0(o32, src, 2, 0x20, &range);
        BT_FBITS(f, o32[2], 0.999f);
        BT_FBITS(f, o32[3], 1.0f);
    }

    /* camera record init: vf0 rows, counts 4, pair table (-1, 0) */
    {
        u32 rec[0xD0 / 4];
        __builtin_memset(rec, 0xAB, sizeof rec);
        FixCameraRecInit_193860(rec);
        BT_EQ(f, rec[0], 0);
        BT_EQ(f, rec[0x10 / 4], 0);
        BT_EQ(f, rec[0x1C / 4], 0x3F800000u);
        BT_EQ(f, rec[0x8C / 4], 0x3F800000u);
        BT_EQ(f, rec[0x90 / 4], 4);
        BT_EQ(f, rec[0xA0 / 4], 0);
        BT_EQ(f, rec[0xA4 / 4], 4);
        BT_EQ(f, rec[0xC0 / 4], 0xFFFFFFFFu);
        BT_EQ(f, rec[0xC4 / 4], 0);
        BT_EQ(f, rec[0xC8 / 4], 0xABABABABu); /* past the 4 pairs */
    }
    return f;
}
