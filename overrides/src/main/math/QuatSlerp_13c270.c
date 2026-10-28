/* rg-override: replaces game/src/main/math/QuatSlerp_13c270.c sha256 e899747362818fcdfd0762a9b06e8ae1a3d175de7ae1fe029128c77e12ddab50
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern f32 D_0047D268;                                  /* -0x7F08(gp) = 0.97 */
extern f32 Acosf_129178(f32);
extern f32 Sinf_128fd0(f32);

/* Load f into vfN.x the way the listing does: mfc1 $8, f; qmtc2 $8, vfN. */
static void rg_f2vf(rg_vu0_state *rg_vu0_p_, int vf, f32 f)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    rg_vu0_mfc1(8, f);
    rg_vu0_qmtc2(8, vf);

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* out = slerp(a, b, t) on the shorter arc; above cos 0.97 it is a normalised
   lerp instead. */
void QuatSlerp_13c270(void *out, const void *a, const void *b, f32 t)
{ RG_VU0_FRAME;
    u8 qa[16];                                          /* sp+0x40 */
    u8 qb[16];                                          /* sp+0x30 */
    f32 d, u, th, s, invs, ka, kb;

    __builtin_memcpy(qa, a, 16);                        /* lq $5, 0($5); sq $5, 0x40($29) */
    __builtin_memcpy(qb, b, 16);                        /* lq $3, 0($6); sq $3, 0x30($29) */
    rg_vu0_lqc2(4, qa);                                 /* lqc2 vf4, 0x40(sp) */
    rg_vu0_lqc2(5, qb);                                 /* lqc2 vf5, 0x30(sp) */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 5, 4, 5, RG_BC_NONE); /* vmul.xyzw vf5, vf4, vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Y);       /* vaddy.x vf5, vf5, vf5y */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Z);       /* vaddz.x vf5, vf5, vf5z */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_W);       /* vaddw.x vf5, vf5, vf5w */
    d = rg_vu0_getf(5, 0);                              /* qmfc2 $2, vf5; mtc1 $2, $f12 */
    if (d < 0.0f) {                                     /* c.lt.s; bc1fl */
        d = -d;                                         /* neg.s $f12, $f12 */
        rg_vu0_lqc2(4, qb);                             /* lqc2 vf4, 0($4=sp+0x30) */
        rg_f2vf(&rg_vu0, 5, -1.0f);                              /* mfc1 $8, -1.0; qmtc2 $8, vf5 */
        rg_vu0_fmac(RG_VMUL, RG_XYZW, 6, 4, 5, RG_BC_X); /* vmulx.xyzw vf6, vf4, vf5x */
        rg_vu0_sqc2(6, qb);                             /* sqc2 vf6, 0($4) */
    }
    u = 1.0f - t;                                       /* sub.s $f21, 1.0, $f22 */
    if (!(d <= D_0047D268)) {                           /* c.le.s; bc1f (slot $3 = 1) */
        /* normalised lerp */
        rg_vu0_lqc2(1, qa);                             /* lqc2 vf1, 0x40(sp) */
        rg_f2vf(&rg_vu0, 11, u);                                 /* mfc1 $8, $f21; qmtc2 $8, vf11 */
        rg_vu0_lqc2(2, qb);                             /* lqc2 vf2, 0x30(sp) */
        rg_f2vf(&rg_vu0, 12, t);                                 /* mfc1 $8, $f22; qmtc2 $8, vf12 */
        rg_vu0_fmac(RG_VMUL, RG_XYZW, 1, 1, 11, RG_BC_X); /* vmulx.xyzw vf1, vf1, vf11x */
        rg_vu0_fmac(RG_VMUL, RG_XYZW, 2, 2, 12, RG_BC_X); /* vmulx.xyzw vf2, vf2, vf12x */
        rg_vu0_fmac(RG_VADD, RG_XYZW, 3, 1, 2, RG_BC_NONE); /* vadd.xyzw vf3, vf1, vf2 */
        rg_vu0_fmac(RG_VMUL, RG_XYZW, 5, 3, 3, RG_BC_NONE); /* vmul.xyzw vf5, vf3, vf3 */
        rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Y);   /* vaddy.x vf5, vf5, vf5y */
        rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Z);   /* vaddz.x vf5, vf5, vf5z */
        rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_W);   /* vaddw.x vf5, vf5, vf5w */
        rg_vu0_sqrt(5, RG_BC_X);                        /* .word 0x4A0503BD = vsqrt Q, vf5x; vwaitq */
        rg_vu0_fmac(RG_VADD, RG_X, 5, 0, RG_FT_Q, RG_BC_NONE); /* .word 0x4B000160 = vaddq.x vf5, vf0, Q */
        rg_vu0_div(0, RG_BC_W, 5, RG_BC_X);             /* .word 0x4A6503BC = vdiv Q, vf0w, vf5x */
        rg_vu0_fmac(RG_VSUB, RG_XYZW, 6, 0, 0, RG_BC_NONE); /* vsub.xyzw vf6, vf0, vf0 */
        rg_vu0_fmac(RG_VMUL, RG_XYZW, 6, 3, RG_FT_Q, RG_BC_NONE); /* .word 0x4BE0199C = vmulq.xyzw vf6, vf3, Q */
        rg_vu0_sqc2(6, out);                            /* sqc2 vf6, 0($16) */
        return;
    }
    th = Acosf_129178(d);                               /* jal Acosf_129178 ($f12 = d) */
    s = Sinf_128fd0(th);
    invs = 1.0f / s;                                    /* div.s $f21, 1.0, $f0 */
    ka = Sinf_128fd0(u * th);                           /* mul.s $f12, $f21, $f20 (before the div) */
    ka = invs * ka;                                     /* mul.s $f20, $f21, $f0 (jal slot) */
    kb = Sinf_128fd0(t * th);                           /* mul.s $f12, $f22, $f20 */
    kb = invs * kb;                                     /* mul.s $f0, $f21, $f0 */
    rg_vu0_lqc2(1, qa);                                 /* lqc2 vf1, 0x40(sp) */
    rg_f2vf(&rg_vu0, 11, ka);                                    /* mfc1 $8, $f20; qmtc2 $8, vf11 */
    rg_vu0_lqc2(2, qb);                                 /* lqc2 vf2, 0x30(sp) */
    rg_f2vf(&rg_vu0, 12, kb);                                    /* mfc1 $8, $f0; qmtc2 $8, vf12 */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 1, 1, 11, RG_BC_X);   /* vmulx.xyzw vf1, vf1, vf11x */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 2, 2, 12, RG_BC_X);   /* vmulx.xyzw vf2, vf2, vf12x */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 3, 1, 2, RG_BC_NONE); /* vadd.xyzw vf3, vf1, vf2 */
    rg_vu0_sqc2(3, out);                                /* sqc2 vf3, 0($16) */
}
