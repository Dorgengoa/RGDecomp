/* rg-override: replaces game/src/main/math/RayTriIntersect_13d8c0.c sha256 e298a37c227a20d31d63822a311a14bd94e4f7ab5596b538126c97199048bd64
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

static inline void rg_vadd(rg_vu0_state *rg_vu0_p_, void *d, const void *a, const void *b)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    rg_vu0_lqc2(4, a);                                  /* lqc2 vf4, a */
    rg_vu0_lqc2(5, b);                                  /* lqc2 vf5, b */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 6, 4, 5, RG_BC_NONE); /* vadd.xyzw vf6, vf4, vf5 */
    rg_vu0_sqc2(6, d);                                  /* sqc2 vf6, d */

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

static inline void rg_vscale(rg_vu0_state *rg_vu0_p_, void *d, const void *a, f32 s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    rg_vu0_lqc2(4, a);                                  /* lqc2 vf4, a */
    rg_vu0_mfc1(8, s);                                  /* mfc1 $8, s */
    rg_vu0_qmtc2(8, 5);                                 /* qmtc2 $8, vf5 */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 6, 4, 5, RG_BC_X);    /* vmulx.xyzw vf6, vf4, vf5x */
    rg_vu0_sqc2(6, d);                                  /* sqc2 vf6, d */

#undef rg_vu0
#pragma pop_macro("rg_vu0")
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

extern s32 PointInTriangle_13d720(const void *p, const void *a, const void *b,
                                  const void *c, const void *n);

/* Project along (p0 - o) onto the plane through p1 with normal n:
   hit = o + (p0 - o) * dot(n, p1 - o) / dot(n, p0 - o), written to *hit, then
   test it against triangle (p1, p2, p3).  Returns 0 when the direction is
   parallel to the plane. */
s32 RayTriIntersect_13d8c0(const void *o, const void *p0, const void *p1, const void *p2,
                           const void *p3, const void *n, void *hit)
{ RG_VU0_FRAME;
    u8 d0[16], d1[16], d2[16], d3[16];                  /* sp+0x40, 0x30, 0x20, 0x10 */
    f32 num, den, t;

    rg_vsub(&rg_vu0, d0, p0, o);
    rg_vsub(&rg_vu0, d1, p1, o);
    rg_vsub(&rg_vu0, d2, p2, o);
    rg_vsub(&rg_vu0, d3, p3, o);
    num = -rg_vdot(&rg_vu0, n, d1);                              /* neg.s $f1, $f0 */
    den = rg_vdot(&rg_vu0, n, d0);                               /* $f2 */
    if (0.0f == den)                                    /* c.eq.s; bc1fl */
        return 0;
    t = -num / den;                                     /* neg.s $f0, $f1 (slot); div.s */
    rg_vscale(&rg_vu0, hit, d0, t);
    rg_vadd(&rg_vu0, hit, hit, o);
    return PointInTriangle_13d720(hit, p1, p2, p3, n);
}
