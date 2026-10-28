/* rg-override: replaces game/src/main/math/PointInTriangle_13d720.c sha256 fdf0dd1e0e07cbbaccca45f23fbc6f854a22954b09923899a3e6fd7b8c2517bd
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* The listing inlines libvu0-style vector macros with fixed registers; each
   helper is one such macro, instruction for instruction. */
static inline void rg_vsub(rg_vu0_state *rg_vu0_p_, void *d, const void *a, const void *b)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    rg_vu0_lqc2(4, a);                                  /* lqc2 vf4, a */
    rg_vu0_lqc2(5, b);                                  /* lqc2 vf5, b */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 6, 4, 5, RG_BC_NONE); /* vsub.xyzw vf6, vf4, vf5 */
    rg_vu0_sqc2(6, d);                                  /* sqc2 vf6, d */

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

static inline void rg_vadd(void *d, const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, a);                                  /* lqc2 vf4, a */
    rg_vu0_lqc2(5, b);                                  /* lqc2 vf5, b */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 6, 4, 5, RG_BC_NONE); /* vadd.xyzw vf6, vf4, vf5 */
    rg_vu0_sqc2(6, d);                                  /* sqc2 vf6, d */
}

static inline void rg_vscale(void *d, const void *a, f32 s)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, a);                                  /* lqc2 vf4, a */
    rg_vu0_mfc1(8, s);                                  /* mfc1 $8, s */
    rg_vu0_qmtc2(8, 5);                                 /* qmtc2 $8, vf5 */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 6, 4, 5, RG_BC_X);    /* vmulx.xyzw vf6, vf4, vf5x */
    rg_vu0_sqc2(6, d);                                  /* sqc2 vf6, d */
}

static inline f32 rg_vdot(rg_vu0_state *rg_vu0_p_, const void *a, const void *b)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    rg_vu0_lqc2(4, a);                                  /* lqc2 vf4, a */
    rg_vu0_lqc2(5, b);                                  /* lqc2 vf5, b */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 5, 4, 5, RG_BC_NONE);  /* vmul.xyz vf5, vf4, vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Y);       /* vaddy.x vf5, vf5, vf5y */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Z);       /* vaddz.x vf5, vf5, vf5z */
    return rg_vu0_getf(5, 0);                           /* qmfc2 $2, vf5; mtc1 $2, $fN */

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

static inline f32 rg_vlensq(const void *a)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, a);                                  /* lqc2 vf4, a */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 4, 4, 4, RG_BC_NONE);  /* vmul.xyz vf4, vf4, vf4 */
    rg_vu0_mr32(RG_XY, 5, 4);                           /* vmr32.xy vf5, vf4 */
    rg_vu0_mr32(RG_X, 6, 5);                            /* vmr32.x vf6, vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 7, 4, 5, RG_BC_NONE);    /* vadd.x vf7, vf4, vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 6, 7, RG_BC_NONE);    /* vadd.x vf5, vf6, vf7 */
    return rg_vu0_getf(5, 0);                           /* qmfc2 $2, vf5; mtc1 $2, $fN */
}

extern void sceVu0OuterProduct(void *d, void *a, void *b);

/* 1 when p lies inside triangle (a, b, c) seen along normal n: the three edge
   cross products all have dot(., n) >= 0, or all <= 0. */
s32 PointInTriangle_13d720(const void *p, const void *a, const void *b, const void *c,
                           const void *n)
{ RG_VU0_FRAME;
    u8 pa[16], pb[16], pc[16], ab[16], bc[16], ca[16];  /* sp+0xA0 .. sp+0x50 */
    u8 x0[16], x1[16], x2[16];                          /* sp+0x40, 0x30, 0x20 */
    f32 d0, d1, d2;

    rg_vsub(&rg_vu0, pa, p, a);                                  /* sp+0xA0 */
    rg_vsub(&rg_vu0, pb, p, b);                                  /* sp+0x90 */
    rg_vsub(&rg_vu0, pc, p, c);                                  /* sp+0x80 */
    rg_vsub(&rg_vu0, ab, b, a);                                  /* sp+0x70 */
    rg_vsub(&rg_vu0, bc, c, b);                                  /* sp+0x60 */
    rg_vsub(&rg_vu0, ca, a, c);                                  /* sp+0x50 */
    sceVu0OuterProduct(x0, ab, pa);
    sceVu0OuterProduct(x1, bc, pb);
    sceVu0OuterProduct(x2, ca, pc);
    d0 = rg_vdot(&rg_vu0, x0, n);                                /* $f3 */
    d1 = rg_vdot(&rg_vu0, x1, n);                                /* $f2 */
    d2 = rg_vdot(&rg_vu0, x2, n);                                /* $f1 */
    if (!(d0 < 0.0f) && !(d1 < 0.0f) && !(d2 < 0.0f))   /* c.lt.s; bc1t x3 */
        return 1;
    if (!(d0 <= 0.0f))                                  /* c.le.s; bc1fl (slot $2 = 0) */
        return 0;
    if (!(d1 <= 0.0f))
        return 0;
    if (!(d2 <= 0.0f))
        return 0;
    return 1;
}
