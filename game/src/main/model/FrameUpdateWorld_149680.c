/* rgp:protos */
#define RGP_SELF_FrameUpdateWorld_149680 1
#define RGP_SELF_InvScaleLoad 1
#define RGP_SELF_InvScaleMul 1
#define RGP_SELF_LoadScaleVec 1
#define RGP_SELF_ScaleLoad 1
#define RGP_SELF_ScaleMul 1
#define RGP_SELF_StoreMatrix 1
#define RGP_SELF_Vu0ScaleMatrix 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
/* VU0 code as mwcc intrinsics (no inline-assembly blocks): file-scope VU0 register bindings under
 * vu0_mmi_reg_binding. Retail's inline-assembly blocks were scheduling barriers; the empty
 * `if (p) { p = launder(p); }` statements below emit no code but keep a basic-block
 * boundary through both scheduling passes, reproducing that order. */
#pragma optimization_level 3
#pragma vu0_mmi_reg_binding on
typedef rg_u128 __attribute__((aligned(4))) rgvb_vz149680_t; /* rg:vu0bind vf0 */
#define vz149680 RG_VU0_BIND_VF(0, rgvb_vz149680_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_v1_149680_t; /* rg:vu0bind vf1 */
#define v1_149680 RG_VU0_BIND_VF(1, rgvb_v1_149680_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_v2_149680_t; /* rg:vu0bind vf2 */
#define v2_149680 RG_VU0_BIND_VF(2, rgvb_v2_149680_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_v3_149680_t; /* rg:vu0bind vf3 */
#define v3_149680 RG_VU0_BIND_VF(3, rgvb_v3_149680_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_v4_149680_t; /* rg:vu0bind vf4 */
#define v4_149680 RG_VU0_BIND_VF(4, rgvb_v4_149680_t)

typedef rg_u128 __attribute__((aligned(4))) rgvb_va149680_t; /* rg:vu0bind vf10 */
#define va149680 RG_VU0_BIND_VF(10, rgvb_va149680_t)

typedef float __attribute__((aligned(4))) rgvb_q149680_t; /* rg:vu0bind Q */
#define q149680 RG_VU0_BIND_Q(rgvb_q149680_t)

typedef volatile rg_u128 VQ149680;

#define SPLIT149680(p, T) if (p) { p = (T *)(s32)(u32)p; }

/* d = s * diag(v.x, v.y, v.z, 1) */
static inline void Vu0ScaleMatrix(rg_vu0_state *rg_vu0_p_, void *d0, void *v0, void *s0)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    VQ149680 *d = (VQ149680 *)(s32)d0;
    VQ149680 *v = (VQ149680 *)(s32)v0;
    VQ149680 *s = (VQ149680 *)(s32)s0;
    v = (VQ149680 *)(s32)v;
    SPLIT149680(d, VQ149680)
    va149680 = *v;
    v1_149680 = s[0];
    v2_149680 = s[1];
    v3_149680 = s[2];
    v4_149680 = s[3];
    SPLIT149680(d, VQ149680)
    v1_149680 = _vmulbc(v1_149680, 0xF, v1_149680, va149680, 8);
    v2_149680 = _vmulbc(v2_149680, 0xF, v2_149680, va149680, 4);
    v3_149680 = _vmulbc(v3_149680, 0xF, v3_149680, va149680, 2);
    SPLIT149680(d, VQ149680)
    d[0] = v1_149680;
    d[1] = v2_149680;
    d[2] = v3_149680;
    d[3] = v4_149680;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

typedef union V4_149680 {
    struct {
        f32 x, y, z;
        s32 w;
    } v;
    rg_u128 q;
} __attribute__((aligned(16))) V4_149680;

typedef struct M4_149680 {
    V4_149680 r[4];
} M4_149680;

typedef struct Xf149680 {
    u8 pad0[4];
    struct Xf149680 *parent;
    struct Xf149680 *child;
    struct Xf149680 *next;
    u8 pad10[4];
    V4_149680 *pos;
    V4_149680 *rot;
    V4_149680 *scale;
    u8 pad20[4];
    u8 f24;
    u8 f25;
    s16 f26;
    u8 pad28;
    u8 dirty;
    u8 pad2A;
    s8 f2B;
    u8 pad2C;
    s8 f2D;
    u8 pad2E[0x60 - 0x2E];
    M4_149680 local;
    M4_149680 world;
} Xf149680;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern V4_149680 D_00481090 __attribute__((section(".sdata")));
extern f32 D_0047DE70;
extern f32 D_0047DE74;
extern f32 D_0047DE78;
extern f32 D_0047DE7C;

static inline void ScaleLoad(rg_vu0_state *rg_vu0_p_, void *v0, void *s0)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    VQ149680 *v = (VQ149680 *)(s32)v0;
    VQ149680 *s = (VQ149680 *)(s32)s0;
    v = (VQ149680 *)(s32)v;
    SPLIT149680(s, VQ149680)
    va149680 = *v;
    v1_149680 = s[0];
    v2_149680 = s[1];
    v3_149680 = s[2];
    v4_149680 = s[3];

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

static inline void ScaleMul(rg_vu0_state *rg_vu0_p_)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    v1_149680 = _vmulbc(v1_149680, 0xF, v1_149680, va149680, 8);
    v2_149680 = _vmulbc(v2_149680, 0xF, v2_149680, va149680, 4);
    v3_149680 = _vmulbc(v3_149680, 0xF, v3_149680, va149680, 2);

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

static inline void InvScaleLoad(rg_vu0_state *rg_vu0_p_, void *v0, void *s0)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    VQ149680 *v = (VQ149680 *)(u32)v0;
    VQ149680 *s = (VQ149680 *)(u32)s0;
    v = (VQ149680 *)(s32)v;
    va149680 = *v;
    v1_149680 = s[0];
    v2_149680 = s[1];
    v3_149680 = s[2];
    v4_149680 = s[3];

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

static inline void InvScaleMul(rg_vu0_state *rg_vu0_p_)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    q149680 = _vdiv(q149680, vz149680, 1, va149680, 8);
    v1_149680 = _vmulf(v1_149680, 0xF, v1_149680, q149680);
    q149680 = _vdiv(q149680, vz149680, 1, va149680, 4);
    v2_149680 = _vmulf(v2_149680, 0xF, v2_149680, q149680);
    q149680 = _vdiv(q149680, vz149680, 1, va149680, 2);
    v3_149680 = _vmulf(v3_149680, 0xF, v3_149680, q149680);

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

static inline void StoreMatrix(rg_vu0_state *rg_vu0_p_, void *d0)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    VQ149680 *d = (VQ149680 *)(s32)d0;
    d[0] = v1_149680;
    d[1] = v2_149680;
    d[2] = v3_149680;
    d[3] = v4_149680;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

static inline void LoadScaleVec(rg_vu0_state *rg_vu0_p_, void *v0)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    VQ149680 *v = (VQ149680 *)(s32)v0;
    v = (VQ149680 *)(s32)v;
    va149680 = *v;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

#define MS if (mode) { mode = (s32)(u32)mode; }
#define XS SPLIT149680(x, Xf149680)

void FrameUpdateWorld_149680(Xf149680 *x, s32 mode)
{ RG_VU0_FRAME;
    M4_149680 m __attribute__((aligned(16)));
    V4_149680 ps __attribute__((aligned(16)));
    V4_149680 s __attribute__((aligned(16)));
    M4_149680 a __attribute__((aligned(16)));
    M4_149680 b __attribute__((aligned(16)));
    M4_149680 unused __attribute__((aligned(16)));
    V4_149680 up __attribute__((aligned(16)));
    Xf149680 *c;

    if (mode == 0) {
        x->f25 = 0;
    } else {
        x->f25 = (x->f24 & 1) != 0;
        if (mode > 0 && (x->f24 & 4)) {
            x->f25 = 0;
        }
        if (x->f24 & 6) {
            mode = 0;
        }
    }
    if (x->f2D == 0) {
        if (x->f2B != 0) {
            FrameCalcLocalMatrix_149b40(x, &m);
        } else {
            m.r[0].q = x->local.r[0].q;
            m.r[1].q = x->local.r[1].q;
            m.r[2].q = x->local.r[2].q;
            m.r[3].q = x->local.r[3].q;
        }
        if (x->parent == NULL) {
            x->world.r[0].q = m.r[0].q;
            x->world.r[1].q = m.r[1].q;
            x->world.r[2].q = m.r[2].q;
            x->world.r[3].q = m.r[3].q;
        } else {
            MtxMulAffine_13d110(&x->world, &x->parent->world, &m);
        }
    } else {
        if (x->f2B != 0) {
            FrameCalcLocalMatrix_149b40(x, &m);
        } else {
            m.r[0].q = x->local.r[0].q;
            m.r[1].q = x->local.r[1].q;
            m.r[2].q = x->local.r[2].q;
            m.r[3].q = x->local.r[3].q;
        }
        if (x->parent == NULL) {
            if (x->scale != NULL) {
                ScaleLoad(&rg_vu0, x->scale, &m);
                void ScaleMul(rg_vu0_state *rg_vu0_p_);

                XS
                StoreMatrix(&rg_vu0, &x->world);
            } else {
                x->world.r[0].q = m.r[0].q;
                x->world.r[1].q = m.r[1].q;
                x->world.r[2].q = m.r[2].q;
                x->world.r[3].q = m.r[3].q;
            }
        } else {
            ps.v.w = 0;
            ps.v.x = VecLength_13d4a0(&x->parent->world.r[0]);
            ps.v.y = VecLength_13d4a0(&x->parent->world.r[1]);
            ps.v.z = VecLength_13d4a0(&x->parent->world.r[2]);
            InvScaleLoad(&rg_vu0, &ps, &x->parent->world);
            void InvScaleMul(rg_vu0_state *rg_vu0_p_);

            XS
            StoreMatrix(&rg_vu0, &x->world);
            if (x->scale != NULL) {
                VecMul_13bd40(&ps, &ps, x->scale);
            }
            MatMul33_13d180(&x->world, &x->world, &m);
            LoadScaleVec(&rg_vu0, &ps);
            MS
            v1_149680 = x->world.r[0].q;
            v2_149680 = x->world.r[1].q;
            v3_149680 = x->world.r[2].q;
            v4_149680 = x->world.r[3].q;
            void ScaleMul(rg_vu0_state *rg_vu0_p_);

            MS
            x->world.r[0].q = v1_149680;
            x->world.r[1].q = v2_149680;
            x->world.r[2].q = v3_149680;
            x->world.r[3].q = v4_149680;
            XS
            {
                V4_149680 *p0 = &x->world.r[3];
                V4_149680 *p2 = &m.r[3];

                SPLIT149680(p0, V4_149680)
                MtxMulPoint_13c890(p0, &x->parent->world, p2);
            }
        }
    }
    if (x->f26 & 6) {
        s.v.x = VecLength_13d4a0(&x->world.r[0]);
        s.v.y = VecLength_13d4a0(&x->world.r[1]);
        s.v.z = VecLength_13d4a0(&x->world.r[2]);
        if (x->f26 & 4) {
            f32 cz;
            f32 cx;

            sceVu0UnitMatrix(&a);
            VecSub_13be40(&a.r[2], &D_00481090, &x->world.r[3]);
            a.r[2].v.y = 0.0f;
            a.r[2].v.w = 0;
            VecNormalize_13bd90(&a.r[2], &a.r[2]);
            cz = a.r[2].v.z;
            cx = a.r[2].v.x;
            a.r[0].v.x = cz;
            a.r[2].v.z = cz;
            a.r[0].v.z = -cx;
            a.r[2].v.x = cx;
            Vu0ScaleMatrix(&rg_vu0, &a, &s, &a);
            x->world.r[0].q = a.r[0].q;
            x->world.r[1].q = a.r[1].q;
            x->world.r[2].q = a.r[2].q;
        } else {
            sceVu0UnitMatrix(&b);
            sceVu0UnitMatrix(&unused);
            up.v.x = D_0047DE70;
            up.v.y = D_0047DE74;
            up.v.z = D_0047DE78;
            *(f32 *)&up.v.w = D_0047DE7C;
            VecSub_13be40(&b.r[2], &D_00481090, &x->world.r[3]);
            b.r[2].v.w = 0;
            VecNormalize_13bd90(&b.r[2], &b.r[2]);
            sceVu0OuterProduct(&b.r[0], &up, &b.r[2]);
            VecNormalize_13bd90(&b.r[0], &b.r[0]);
            sceVu0OuterProduct(&b.r[1], &b.r[2], &b.r[0]);
            Vu0ScaleMatrix(&rg_vu0, &b, &s, &b);
            x->world.r[0].q = b.r[0].q;
            x->world.r[1].q = b.r[1].q;
            x->world.r[2].q = b.r[2].q;
        }
    }
    for (c = x->child; c != NULL; c = c->next) {
        FrameUpdateWorld_149680(c, mode);
    }
    x->dirty = 0;
}
