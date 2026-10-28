/* rg-override: replaces game/src/main/math/PointSegmentClosest_13dcc0.c sha256 187a17c2abf59dfa169c8c311ab9507f2f94e6fee889c59c7cfa344b2229bd13
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

static inline f32 rg_vlensq(rg_vu0_state *rg_vu0_p_, const void *a)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    rg_vu0_lqc2(4, a);                                  /* lqc2 vf4, a */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 4, 4, 4, RG_BC_NONE);  /* vmul.xyz vf4, vf4, vf4 */
    rg_vu0_mr32(RG_XY, 5, 4);                           /* vmr32.xy vf5, vf4 */
    rg_vu0_mr32(RG_X, 6, 5);                            /* vmr32.x vf6, vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 7, 4, 5, RG_BC_NONE);    /* vadd.x vf7, vf4, vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 6, 7, RG_BC_NONE);    /* vadd.x vf5, vf6, vf7 */
    return rg_vu0_getf(5, 0);                           /* qmfc2 $2, vf5; mtc1 $2, $fN */

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

extern f32 VecDistance_13d3d0(const void *a, const void *b);

/* Closest point on segment a-b to p, written to *out; returns its distance
   from p.  Off the ends, the nearer endpoint is chosen by distance. */
f32 PointSegmentClosest_13dcc0(const void *p, const void *a, const void *b, void *out)
{ RG_VU0_FRAME;
    u8 pa[16];                                          /* sp+0x90 */
    u8 pb[16];                                          /* sp+0x80 */
    u8 tv[16];                                          /* sp+0x70 */
    u8 ab[16];                                          /* sp+0x60 */
    f32 len, len2, t, d1, d2;
    u8 q[16];

    rg_vsub(&rg_vu0, pa, a, p);
    rg_vsub(&rg_vu0, pb, b, p);
    rg_vsub(&rg_vu0, ab, pb, pa);
    rg_vlensq(&rg_vu0, ab);
    rg_vu0_sqrt(5, RG_BC_X);                            /* vsqrt Q, vf5x; vwaitq */
    len = rg_vu0_getq();                                /* cfc2 $2, vi22; mtc1 $2, $f0 */
    len2 = len * len;                                   /* mul.s $f1, $f0, $f0 */
    t = -rg_vdot(&rg_vu0, pa, ab) / len2;                        /* neg.s; div.s $f1 */
    if (t < 0.0f || !(t <= 1.0f)) {                     /* c.lt.s; bc1tl / c.le.s 1.0; bc1tl */
        d1 = VecDistance_13d3d0(p, a);                  /* $f20 */
        d2 = VecDistance_13d3d0(p, b);
        if (d1 < d2) {                                  /* c.lt.s; bc1fl (slot lq $2, 0($17)) */
            __builtin_memcpy(q, a, 16);                 /* lq $2, 0($18) */
            __builtin_memcpy(out, q, 16);               /* sq $2, 0($16) */
            return d1;
        }
        __builtin_memcpy(q, b, 16);
        __builtin_memcpy(out, q, 16);
        return d2;
    }
    rg_vscale(&rg_vu0, tv, ab, t);                               /* tv = ab * t */
    rg_vadd(&rg_vu0, tv, pa, tv);                                /* tv = (a - p) + tv */
    rg_vadd(&rg_vu0, out, tv, p);                                /* out = tv + p */
    rg_vlensq(&rg_vu0, tv);
    rg_vu0_sqrt(5, RG_BC_X);                            /* vsqrt Q, vf5x; vwaitq */
    return rg_vu0_getq();                               /* cfc2 $2, vi22; mtc1 $2, $f0 */
}
