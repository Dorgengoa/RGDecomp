/* rg-override: replaces game/src/main/math/SegmentSphereIntersectWorld_13d9d0.c sha256 0ce395b6ece15f8c724b620802841278bc130a8781fb1a2262c502f80e6c8eb2
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

static inline f32 rg_vdot(const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, a);                                  /* lqc2 vf4, a */
    rg_vu0_lqc2(5, b);                                  /* lqc2 vf5, b */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 5, 4, 5, RG_BC_NONE);  /* vmul.xyz vf5, vf4, vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Y);       /* vaddy.x vf5, vf5, vf5y */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Z);       /* vaddz.x vf5, vf5, vf5z */
    return rg_vu0_getf(5, 0);                           /* qmfc2 $2, vf5; mtc1 $2, $fN */
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

extern s32 SegmentSphereIntersect_13da60(const void *a, const void *b, void *out, f32 r);

/* Segment a->b against the sphere c (centre c.xyz, radius c.w), in world
   space: the hits come back translated by c.  Returns the hit count. */
s32 SegmentSphereIntersectWorld_13d9d0(const void *c, const void *a, const void *b, void *out)
{ RG_VU0_FRAME;
    u8 la[16];                                          /* sp+0x40 */
    u8 lb[16];                                          /* sp+0x30 */
    f32 r = ((const f32 *)c)[3];                        /* lwc1 $f12, 0xC($4) */
    s32 n, i;
    char *p;

    rg_vsub(&rg_vu0, la, a, c);
    rg_vsub(&rg_vu0, lb, b, c);
    n = SegmentSphereIntersect_13da60(la, lb, out, r);
    for (i = 0; i < n; i++) {                           /* slt; bnel (slot sll $3, $4, 4) */
        p = (char *)out + (i << 4);
        rg_vu0_lqc2(15, p);                             /* lqc2 vf15, 0($3) */
        rg_vu0_lqc2(16, c);                             /* lqc2 vf16, 0($17) */
        rg_vu0_fmac(RG_VADD, RG_XYZW, 15, 15, 16, RG_BC_NONE); /* vadd.xyzw vf15, vf15, vf16 */
        rg_vu0_sqc2(15, p);                             /* sqc2 vf15, 0($3) */
    }
    return n;
}
