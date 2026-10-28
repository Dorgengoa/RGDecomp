/* rgp:protos */
#define RGP_SELF_AnimKeyBlendFrame_155bf0 1
#define RGP_SELF_InterVector_155bf0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
/* VU0 code as mwcc intrinsics + file-scope VU0 register bindings (vu0_mmi_reg_binding).
 * Sony sceVu0InterVector: only the blocked spans use SDK macros from libvu0.h --
 * Vu0InterVectorLoad (asm scheduling barrier: lqc2 vf4 after the div.s),
 * Vu0ScaleF(t0, t, vf6) (bare mfc1 via t0), Vu0InterVectorAcc (vmulaw ACC-dest).
 * Proof: build/s88m/acc5/NOTES.md. */
#include "types.h"
#include "libvu0.h"

#pragma optimization_level 3
#pragma vu0_mmi_reg_binding on

typedef rg_u128 u128_155bf0;

typedef u128_155bf0 __attribute__((aligned(4))) rgvb_v4_155bf0_t; /* rg:vu0bind vf4 */
#define v4_155bf0 RG_VU0_BIND_VF(4, rgvb_v4_155bf0_t)

typedef u128_155bf0 __attribute__((aligned(4))) rgvb_v5_155bf0_t; /* rg:vu0bind vf5 */
#define v5_155bf0 RG_VU0_BIND_VF(5, rgvb_v5_155bf0_t)

typedef u128_155bf0 __attribute__((aligned(4))) rgvb_v6_155bf0_t; /* rg:vu0bind vf6 */
#define v6_155bf0 RG_VU0_BIND_VF(6, rgvb_v6_155bf0_t)

typedef u128_155bf0 __attribute__((aligned(4))) rgvb_v7_155bf0_t; /* rg:vu0bind vf7 */
#define v7_155bf0 RG_VU0_BIND_VF(7, rgvb_v7_155bf0_t)

typedef u128_155bf0 __attribute__((aligned(4))) rgvb_v8_155bf0_t; /* rg:vu0bind vf8 */
#define v8_155bf0 RG_VU0_BIND_VF(8, rgvb_v8_155bf0_t)

typedef u128_155bf0 __attribute__((aligned(4))) rgvb_acc_155bf0_t; /* rg:vu0bind ACC */
#define acc_155bf0 RG_VU0_BIND_ACC(rgvb_acc_155bf0_t)


/* d = p1 * t + p2 * (1 - t)   (Sony sceVu0InterVector) */
static inline void InterVector_155bf0(rg_vu0_state *rg_vu0_p_, void *d, void *p1, void *p2, f32 t)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    u128_155bf0 *a = (u128_155bf0 *)(s32)p1;
    u128_155bf0 *b;

    a = (u128_155bf0 *)(s32)a;
    b = (u128_155bf0 *)(s32)p2;
    Vu0InterVectorLoad(b);
    v5_155bf0 = *a;
    Vu0ScaleF(t0, t, vf6);
    v7_155bf0 = _vsub(v7_155bf0, 0xF, v5_155bf0, v4_155bf0);
    Vu0InterVectorAcc();
    v8_155bf0 = _vmaddbc(v8_155bf0, 0xF, acc_155bf0, v7_155bf0, v6_155bf0, 8);
    *(u128_155bf0 *)d = v8_155bf0;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

typedef struct Out155bf0 {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;
    s32 f14;
    u8 pad18[8];
    u128_155bf0 v20;
    u128_155bf0 v30;
    u128_155bf0 v40;
    u128_155bf0 v50;
} Out155bf0;

/*rgp*/
/*rgp*/

void AnimKeyBlendFrame_155bf0(Out155bf0 *arg0, f32 unused, f32 t, void *rgp_a1)
{ RG_VU0_FRAME;
    Out155bf0 s __attribute__((aligned(16)));
    f32 f;
    f32 r;

    AnimKeyEvalFrame_155e10(&s, (void *)rgp_a1, (float)unused);
    if (!(s.a <= 0.0f)) {
        if (!(arg0->a <= 0.0f)) {
            f = arg0->a + t;
            QuatSlerp_13c270(&arg0->v50, &arg0->v50, &s.v50, t / f);
            arg0->a = f;
        } else {
            arg0->v50 = s.v50;
            arg0->a = t;
        }
    }
    if (!(s.c <= 0.0f)) {
        if (!(arg0->c <= 0.0f)) {
            f = arg0->c + t;
            r = t / f;
            InterVector_155bf0(&rg_vu0, &arg0->v20, &s.v20, &arg0->v20, r);
            arg0->c = f;
        } else {
            arg0->v20 = s.v20;
            arg0->c = t;
        }
    }
    if (!(s.b <= 0.0f)) {
        if (!(arg0->b <= 0.0f)) {
            f = arg0->b + t;
            r = t / f;
            InterVector_155bf0(&rg_vu0, &arg0->v30, &s.v30, &arg0->v30, r);
            arg0->b = f;
        } else {
            arg0->v30 = s.v30;
            arg0->b = t;
        }
    }
    if (!(s.d <= 0.0f)) {
        if (!(arg0->d <= 0.0f)) {
            f = arg0->d + t;
            r = t / f;
            InterVector_155bf0(&rg_vu0, &arg0->v40, &s.v40, &arg0->v40, r);
            arg0->d = f;
        } else {
            arg0->v40 = s.v40;
            arg0->d = t;
        }
    }
    if (!(s.e <= 0.0f)) {
        if (!(arg0->e <= 0.0f)) {
            f = arg0->e + t;
            if (!(t <= arg0->e)) {
                arg0->f14 = s.f14;
            }
            arg0->e = f;
        } else {
            arg0->f14 = s.f14;
            arg0->e = t;
        }
    }
}
