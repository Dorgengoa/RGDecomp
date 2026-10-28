/* rg-override: replaces game/src/main/math/SegmentSphereIntersect_13da60.c sha256 8a97bd4f3f1a3a0941f0f371887d1142c12992f80f7cf38aaeb89e2497b50f1b
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

/* Intersect segment a->b with the sphere of radius r at the origin.  Writes
   the 0..2 hit points (a + t * (b - a), 0 <= t <= 1; a tangent hit is written
   whatever t is) to out[] and returns their count. */
s32 SegmentSphereIntersect_13da60(const void *a, const void *b, void *out, f32 r)
{ RG_VU0_FRAME;
    u8 tmp[16];                                         /* sp+0x00 */
    u8 dir[16];                                         /* sp+0x10 */
    f32 rr, dd, bd, aa, c, disc, sq, t1, t2, nb;
    s32 n;

    rg_vsub(&rg_vu0, dir, b, a);                                 /* dir = b - a */
    rr = r * r;                                         /* mul.s $f0, $f12, $f12 */
    dd = rg_vlensq(&rg_vu0, dir);                                /* $f4 */
    bd = rg_vdot(&rg_vu0, dir, a);                               /* $f2 */
    aa = rg_vlensq(&rg_vu0, a);                                  /* $f1 */
    c = aa - rr;                                        /* sub.s $f0, $f1, $f0 */
    disc = bd * bd - dd * c;                            /* mula.s $f2,$f2; msub.s $f1, $f4, $f0 */
    if (disc < 0.0f)                                    /* c.lt.s; bc1fl (slot: nb = -bd) */
        return 0;
    nb = -bd;
    sq = __builtin_sqrtf(disc);                         /* sqrt.s $f2, $f1 */
    t1 = (nb - sq) / dd;                                /* sub.s; div.s $f1 */
    t2 = (nb + sq) / dd;                                /* add.s; div.s $f2 */
    if (0.0f == disc) {                                 /* c.eq.s $f3(0), $f1; bc1f */
        rg_vscale(&rg_vu0, tmp, dir, t1);
        rg_vadd(&rg_vu0, out, a, tmp);
        return 1;
    }
    n = 0;
    if (!(t1 < 0.0f)) {                                 /* c.lt.s; bc1t */
        if (t1 <= 1.0f) {                               /* c.le.s; bc1f */
            rg_vscale(&rg_vu0, tmp, dir, t1);
            rg_vadd(&rg_vu0, out, a, tmp);
            n = n + 1;
        }
    }
    if (t2 < 0.0f)                                      /* c.lt.s; bc1t out */
        return n;
    if (!(t2 <= 1.0f))                                  /* c.le.s; bc1f out */
        return n;
    rg_vscale(&rg_vu0, tmp, dir, t2);
    rg_vadd(&rg_vu0, (char *)out + (n << 4), a, tmp);            /* sll $3, $2, 4; addu $3, $6, $3 */
    return n + 1;
}
