/* rgp:protos */
#define RGP_SELF_AnimKeyBlendMaterial_1559e0 1
#define RGP_SELF_InterVector_1559e0 1
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

typedef rg_u128 u128_1559e0;

typedef u128_1559e0 __attribute__((aligned(4))) rgvb_v4_1559e0_t; /* rg:vu0bind vf4 */
#define v4_1559e0 RG_VU0_BIND_VF(4, rgvb_v4_1559e0_t)

typedef u128_1559e0 __attribute__((aligned(4))) rgvb_v5_1559e0_t; /* rg:vu0bind vf5 */
#define v5_1559e0 RG_VU0_BIND_VF(5, rgvb_v5_1559e0_t)

typedef u128_1559e0 __attribute__((aligned(4))) rgvb_v6_1559e0_t; /* rg:vu0bind vf6 */
#define v6_1559e0 RG_VU0_BIND_VF(6, rgvb_v6_1559e0_t)

typedef u128_1559e0 __attribute__((aligned(4))) rgvb_v7_1559e0_t; /* rg:vu0bind vf7 */
#define v7_1559e0 RG_VU0_BIND_VF(7, rgvb_v7_1559e0_t)

typedef u128_1559e0 __attribute__((aligned(4))) rgvb_v8_1559e0_t; /* rg:vu0bind vf8 */
#define v8_1559e0 RG_VU0_BIND_VF(8, rgvb_v8_1559e0_t)

typedef u128_1559e0 __attribute__((aligned(4))) rgvb_acc_1559e0_t; /* rg:vu0bind ACC */
#define acc_1559e0 RG_VU0_BIND_ACC(rgvb_acc_1559e0_t)


/* d = p1 * t + p2 * (1 - t)   (Sony sceVu0InterVector) */
static inline void InterVector_1559e0(rg_vu0_state *rg_vu0_p_, void *d, void *p1, void *p2, f32 t)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    u128_1559e0 *a = (u128_1559e0 *)(s32)p1;
    u128_1559e0 *b;

    a = (u128_1559e0 *)(s32)a;
    b = (u128_1559e0 *)(s32)p2;
    Vu0InterVectorLoad(b);
    v5_1559e0 = *a;
    Vu0ScaleF(t0, t, vf6);
    v7_1559e0 = _vsub(v7_1559e0, 0xF, v5_1559e0, v4_1559e0);
    Vu0InterVectorAcc();
    v8_1559e0 = _vmaddbc(v8_1559e0, 0xF, acc_1559e0, v7_1559e0, v6_1559e0, 8);
    *(u128_1559e0 *)d = v8_1559e0;

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

typedef struct Out1559e0 {
    f32 a;
    f32 b;
    u8 pad8[8];
    u128_1559e0 v10;
    u128_1559e0 v20;
} Out1559e0;

typedef struct Tgt1559e0 {
    f32 a;
    f32 b;
    u8 pad8[8];
    u128_1559e0 v40;
    u128_1559e0 v50;
} Tgt1559e0;

/*rgp*/

void AnimKeyBlendMaterial_1559e0(Out1559e0 *arg0, f32 unused, f32 t, void *rgp_a1)
{ RG_VU0_FRAME;
    Tgt1559e0 s __attribute__((aligned(16)));
    f32 f;
    f32 r;

    AnimKeyEvalMaterial_155af0(&s, (void *)rgp_a1, (float)unused);
    if (!(s.a <= 0.0f)) {
        if (!(arg0->a <= 0.0f)) {
            f = arg0->a + t;
            r = t / f;
            InterVector_1559e0(&rg_vu0, &arg0->v10, &s.v40, &arg0->v10, r);
            arg0->a = f;
        } else {
            arg0->v10 = s.v40;
            arg0->a = t;
        }
    }
    if (!(s.b <= 0.0f)) {
        if (!(arg0->b <= 0.0f)) {
            f = arg0->b + t;
            r = t / f;
            InterVector_1559e0(&rg_vu0, &arg0->v20, &s.v50, &arg0->v20, r);
            arg0->b = f;
        } else {
            arg0->v20 = s.v50;
            arg0->b = t;
        }
    }
}
