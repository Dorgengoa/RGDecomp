/* Bindings test for the l5math lane: Level-5's own VU0 vector/matrix library
 * (MAIN 0x13BC20..0x140000), ported as overrides.  Self-contained functions
 * only (no game data, no calls out), checked against hand-computed values.
 * This file is derived from the game's behaviour and, like overrides/, is not
 * covered by the repository's CC0 dedication. */
#include "types.h"
#include "bt.h"

extern f32 Vu0InnerProduct_13bd60(const void *a, const void *b);
extern f32 VecDistance_13d3d0(const void *a, const void *b);
extern f32 VecDistanceXZ_13d390(const void *a, const void *b);
extern f32 VecLengthSq_13d440(const void *v);
extern void MtxIdentity_13d2e0(void *m);
extern void MtxMul_13d240(void *d, const void *a, const void *b);
extern void MtxInverse_13cf40(void *d, const void *s);
extern void MtxProjectPoint_13c8c0(void *d, const void *m, const void *v);
extern void MtxTransformPoints_13c810(void *d, const void *m, const void *s, s32 n);
extern s32 AabbContainsPoint_13e130(const void *p, const void *a, const void *b);
extern s32 AabbOverlap_13e0e0(const void *a, const void *b, const void *c, const void *d);
extern void VecTriCross_13de70(void *d, const void *a, const void *b, const void *c);
extern s32 PointInTriangle2D_13d4d0(f32 px, f32 py, f32 ax, f32 ay, f32 bx, f32 by, f32 cx, f32 cy);
extern s32 SegmentSphereIntersect_13da60(const void *a, const void *b, void *out, f32 r);

typedef struct { f32 v[4]; } __attribute__((aligned(16))) BtV4;
typedef struct { f32 m[16]; } __attribute__((aligned(16))) BtM4;

static f32 bt_u2f(u32 u)
{
    f32 f;
    __builtin_memcpy(&f, &u, 4);
    return f;
}

static void bt_set(BtV4 *p, f32 x, f32 y, f32 z, f32 w)
{
    p->v[0] = x; p->v[1] = y; p->v[2] = z; p->v[3] = w;
}

int bt_ovr_l5math(void)
{
    int fails = 0;
    BtV4 a, b, c, p, o[2];
    BtM4 m, n, r;
    int i;

    /* dot (1,2,3).(4,5,6) = 32; w ignored */
    bt_set(&a, 1, 2, 3, 100);
    bt_set(&b, 4, 5, 6, 100);
    BT_FBITS(fails, Vu0InnerProduct_13bd60(&a, &b), 32.0f);

    /* |(3,4,0) - 0| = 5 (vsqrt), |(1,2,2)|^2 = 9 */
    bt_set(&a, 0, 0, 0, 0);
    bt_set(&b, 3, 4, 0, 7);
    BT_FBITS(fails, VecDistance_13d3d0(&a, &b), 5.0f);
    bt_set(&a, 1, 2, 2, 9);
    BT_FBITS(fails, VecLengthSq_13d440(&a), BT_WRONG(9.0f));
    /* XZ distance ignores y: dx 3, dz 4 */
    bt_set(&a, 1, 100, 1, 0);
    bt_set(&b, 4, -7, 5, 0);
    BT_FBITS(fails, VecDistanceXZ_13d390(&a, &b), 5.0f);

    /* identity */
    for (i = 0; i < 16; i++)
        m.m[i] = 9.0f;
    MtxIdentity_13d2e0(&m);
    for (i = 0; i < 16; i++)
        BT_FBITS(fails, m.m[i], (i % 5 == 0) ? 1.0f : 0.0f);

    /* d.r[i] = sum_k a.r[k] * b.r[i][k]: a = diag(2,3,4,1), b = translate(5,6,7) */
    __builtin_memset(&m, 0, sizeof m);
    m.m[0] = 2; m.m[5] = 3; m.m[10] = 4; m.m[15] = 1;
    MtxIdentity_13d2e0(&n);
    n.m[12] = 5; n.m[13] = 6; n.m[14] = 7;
    MtxMul_13d240(&r, &m, &n);
    BT_FBITS(fails, r.m[0], 2.0f);
    BT_FBITS(fails, r.m[5], 3.0f);
    BT_FBITS(fails, r.m[12], 10.0f);
    BT_FBITS(fails, r.m[13], 18.0f);
    BT_FBITS(fails, r.m[14], 28.0f);
    BT_FBITS(fails, r.m[15], 1.0f);

    /* inverse of diag(2,4,8) + translation (1,2,3) */
    __builtin_memset(&m, 0, sizeof m);
    m.m[0] = 2; m.m[5] = 4; m.m[10] = 8;
    m.m[12] = 1; m.m[13] = 2; m.m[14] = 3; m.m[15] = 1;
    MtxInverse_13cf40(&r, &m);
    BT_FBITS(fails, r.m[0], 0.5f);
    BT_FBITS(fails, r.m[5], 0.25f);
    BT_FBITS(fails, r.m[10], 0.125f);
    BT_FBITS(fails, r.m[3], 0.0f);
    BT_FBITS(fails, r.m[12], -0.5f);
    BT_FBITS(fails, r.m[13], -0.5f);
    BT_FBITS(fails, r.m[14], -0.375f);
    BT_FBITS(fails, r.m[15], 1.0f);

    /* projective divide: 1/3 through vdiv truncates (0x3EAAAAAA, IEEE would
       round up to 0x3EAAAAAB) */
    MtxIdentity_13d2e0(&m);
    bt_set(&a, 1, 2, 1, 3);
    MtxProjectPoint_13c8c0(&p, &m, &a);
    BT_FBITS(fails, p.v[0], bt_u2f(0x3EAAAAAAu));
    BT_FBITS(fails, p.v[3], 3.0f);

    /* two points through translate(1,2,3) */
    MtxIdentity_13d2e0(&m);
    m.m[12] = 1; m.m[13] = 2; m.m[14] = 3;
    {
        BtV4 src[3];
        bt_set(&src[0], 1, 0, 0, 1);
        bt_set(&src[1], 0, 0, 0, 0);
        bt_set(&src[2], 0, 0, 0, 0); /* the pipelined lqc2 reads one past */
        MtxTransformPoints_13c810(o, &m, src, 2);
        BT_FBITS(fails, o[0].v[0], 2.0f);
        BT_FBITS(fails, o[0].v[2], 3.0f);
        BT_FBITS(fails, o[1].v[0], 0.0f); /* w = 0: no translation */
    }

    /* AABB tests: sign of (hi - p) and (p - lo) */
    bt_set(&a, 2, 2, 2, 0);
    bt_set(&b, 0, 0, 0, 0);
    bt_set(&p, 1, 1, 1, 0);
    BT_EQ(fails, AabbContainsPoint_13e130(&p, &a, &b), 1);
    bt_set(&p, 3, 1, 1, 0);
    BT_EQ(fails, AabbContainsPoint_13e130(&p, &a, &b), 0);
    bt_set(&p, 1, 1, -0.5f, 0);
    BT_EQ(fails, AabbContainsPoint_13e130(&p, &a, &b), 0);
    /* overlap(a_hi, a_lo, b_hi, b_lo): a - d >= 0 and c - b >= 0 */
    bt_set(&c, 3, 3, 3, 0);
    bt_set(&p, 1, 1, 1, 0);
    BT_EQ(fails, AabbOverlap_13e0e0(&a, &b, &c, &p), 1);
    bt_set(&c, 5, 5, 5, 0);
    bt_set(&p, 4, 4, 4, 0);
    BT_EQ(fails, AabbOverlap_13e0e0(&a, &b, &c, &p), 0);

    /* (b - a) x (c - a) = x cross y = z */
    bt_set(&a, 0, 0, 0, 0);
    bt_set(&b, 1, 0, 0, 0);
    bt_set(&c, 0, 1, 0, 0);
    VecTriCross_13de70(&p, &a, &b, &c);
    BT_FBITS(fails, p.v[0], 0.0f);
    BT_FBITS(fails, p.v[1], 0.0f);
    BT_FBITS(fails, p.v[2], 1.0f);

    /* 2D point in triangle (0,0) (1,0) (0,1) */
    BT_EQ(fails, PointInTriangle2D_13d4d0(0.25f, 0.25f, 0, 0, 1, 0, 0, 1), 1);
    BT_EQ(fails, PointInTriangle2D_13d4d0(2.0f, 2.0f, 0, 0, 1, 0, 0, 1), 0);
    BT_EQ(fails, PointInTriangle2D_13d4d0(0.5f, 0.0f, 0, 0, 1, 0, 0, 1), 2);
    BT_EQ(fails, PointInTriangle2D_13d4d0(0.75f, 0.75f, 0, 0, 1, 0, 0, 1), 0);

    /* segment (-2,0,0)->(2,0,0) against the unit sphere: t = 0.25, 0.75 */
    bt_set(&a, -2, 0, 0, 0);
    bt_set(&b, 2, 0, 0, 0);
    BT_EQ(fails, SegmentSphereIntersect_13da60(&a, &b, o, 1.0f), 2);
    BT_FBITS(fails, o[0].v[0], -1.0f);
    BT_FBITS(fails, o[1].v[0], 1.0f);
    bt_set(&b, -2, 5, 0, 0); /* misses */
    BT_EQ(fails, SegmentSphereIntersect_13da60(&a, &b, o, 1.0f), 0);

    return fails;
}
