/* rgp:protos */
#define RGP_SELF_AnimKeyEvalScalarLinear_154a10 1
#define RGP_SELF_InterVector_154a10 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

#pragma vu0_mmi_reg_binding on

typedef rg_u128 u128_154a10;

typedef u128_154a10 __attribute__((aligned(4))) rgvb_v4_154a10_t; /* rg:vu0bind vf4 */
#define v4_154a10 RG_VU0_BIND_VF(4, rgvb_v4_154a10_t)

typedef u128_154a10 __attribute__((aligned(4))) rgvb_v5_154a10_t; /* rg:vu0bind vf5 */
#define v5_154a10 RG_VU0_BIND_VF(5, rgvb_v5_154a10_t)

typedef u128_154a10 __attribute__((aligned(4))) rgvb_v6_154a10_t; /* rg:vu0bind vf6 */
#define v6_154a10 RG_VU0_BIND_VF(6, rgvb_v6_154a10_t)

typedef u128_154a10 __attribute__((aligned(4))) rgvb_v7_154a10_t; /* rg:vu0bind vf7 */
#define v7_154a10 RG_VU0_BIND_VF(7, rgvb_v7_154a10_t)

typedef u128_154a10 __attribute__((aligned(4))) rgvb_v8_154a10_t; /* rg:vu0bind vf8 */
#define v8_154a10 RG_VU0_BIND_VF(8, rgvb_v8_154a10_t)

typedef u128_154a10 __attribute__((aligned(4))) rgvb_acc_154a10_t; /* rg:vu0bind ACC */
#define acc_154a10 RG_VU0_BIND_ACC(rgvb_acc_154a10_t)


/* d = p1 * t + p2 * (1 - t)   (Sony sceVu0InterVector) */
static inline void InterVector_154a10(rg_vu0_state *rg_vu0_p_, void *d, void *p1, void *p2, f32 t)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    u128_154a10 *b = (u128_154a10 *)(s32)p2;
    u128_154a10 *a = (u128_154a10 *)(s32)p1;

    if (b) {
        b = (u128_154a10 *)(s32)(u32)b;
    }
    v4_154a10 = *b;
    v5_154a10 = *a;
    Vu0ScaleF(t0, t, vf6);
    v7_154a10 = _vsub(v7_154a10, 0xF, v5_154a10, v4_154a10);
    Vu0InterVectorAcc();
    v8_154a10 = _vmaddbc(v8_154a10, 0xF, acc_154a10, v7_154a10, v6_154a10, 8);
    *(u128_154a10 *)d = v8_154a10;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

typedef struct V4_154a10 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) V4_154a10;

typedef struct Chan154a10 {
    u8 b0;
    u8 fmt;
    u8 b2;
    u8 b3;
    s16 h4;
    u16 h6;
    s32 w8;
    void *data;
    f32 scale;
} Chan154a10;

typedef struct Key154a10 {
    f32 time;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 i0;
    s32 i1;
    s32 pad1C[3];
} Key154a10;

/*rgp*/

void AnimKeyEvalScalarLinear_154a10(f32 *out, Chan154a10 *ch, f32 time)
{ RG_VU0_FRAME;
    Key154a10 k __attribute__((aligned(16)));
    V4_154a10 a8 __attribute__((aligned(16)));
    V4_154a10 b8 __attribute__((aligned(16)));
    V4_154a10 af __attribute__((aligned(16)));
    V4_154a10 bf __attribute__((aligned(16)));
    V4_154a10 as __attribute__((aligned(16)));
    V4_154a10 bs __attribute__((aligned(16)));
    f32 t;
    f32 v;

    k.a = ch->b2;
    k.b = ch->w8;
    k.d = ch->h6;
    k.time = time;
    k.c = ch->h4;
    t = AnimKeyFindSpan_155ff0(&k);
    if (ch->fmt == 8) {
        s8 *d8 = ch->data;
        if (t == 0.0f) {
            v = (1.0f / 128.0f) * d8[k.i0];
            *out = v * ch->scale;
        } else {
            v = (1.0f / 128.0f) * d8[k.i0];
            a8.x = v * ch->scale;
            v = (1.0f / 128.0f) * d8[k.i1];
            b8.x = v * ch->scale;
            InterVector_154a10(&rg_vu0, out, &b8, &a8, t);
        }
    } else if (ch->fmt == 0x20) {
        f32 *df = ch->data;
        if (t == 0.0f) {
            *out = df[k.i0];
        } else {
            af.x = df[k.i0];
            bf.x = df[k.i1];
            InterVector_154a10(&rg_vu0, out, &bf, &af, t);
        }
    } else if (ch->fmt == 0x10) {
        s16 *ds = ch->data;
        if (t == 0.0f) {
            v = (1.0f / 32768.0f) * ds[k.i0];
            *out = v * ch->scale;
        } else {
            v = (1.0f / 32768.0f) * ds[k.i0];
            as.x = v * ch->scale;
            v = (1.0f / 32768.0f) * ds[k.i1];
            bs.x = v * ch->scale;
            InterVector_154a10(&rg_vu0, out, &bs, &as, t);
        }
    }
}
