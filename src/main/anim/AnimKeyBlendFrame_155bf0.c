/* VU0 code as mwcc intrinsics + file-scope VU0 register bindings (vu0_mmi_reg_binding).
 * Sony sceVu0InterVector: only the blocked spans use SDK macros from libvu0.h --
 * Vu0InterVectorLoad (asm scheduling barrier: lqc2 vf4 after the div.s),
 * Vu0ScaleF(t0, t, vf6) (bare mfc1 via t0), Vu0InterVectorAcc (vmulaw ACC-dest).
 * Proof: build/s88m/acc5/NOTES.md. */
#include "types.h"
#include "libvu0.h"

#pragma optimization_level 3
#pragma vu0_mmi_reg_binding on

typedef unsigned __int128 u128_155bf0;

extern u128_155bf0 v4_155bf0 asm("vf4");
extern u128_155bf0 v5_155bf0 asm("vf5");
extern u128_155bf0 v6_155bf0 asm("vf6");
extern u128_155bf0 v7_155bf0 asm("vf7");
extern u128_155bf0 v8_155bf0 asm("vf8");
extern u128_155bf0 acc_155bf0 asm("ACC");

/* d = p1 * t + p2 * (1 - t)   (Sony sceVu0InterVector) */
static inline void InterVector_155bf0(void *d, void *p1, void *p2, f32 t)
{
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

extern void AnimKeyEvalFrame_155e10(Out155bf0 *);
extern void QuatSlerp_13c270(u128_155bf0 *, u128_155bf0 *, u128_155bf0 *, f32);

void AnimKeyBlendFrame_155bf0(Out155bf0 *arg0, f32 unused, f32 t)
{
    Out155bf0 s;
    f32 f;
    f32 r;

    AnimKeyEvalFrame_155e10(&s);
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
            InterVector_155bf0(&arg0->v20, &s.v20, &arg0->v20, r);
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
            InterVector_155bf0(&arg0->v30, &s.v30, &arg0->v30, r);
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
            InterVector_155bf0(&arg0->v40, &s.v40, &arg0->v40, r);
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
