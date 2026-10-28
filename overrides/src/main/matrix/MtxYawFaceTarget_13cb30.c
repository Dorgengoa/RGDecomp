/* rg-override: replaces game/src/main/matrix/MtxYawFaceTarget_13cb30.c sha256 74b0dadff57a5d5a5eb9aac6a4fd9cf767d8d18904be7ed3463644314dffdb1d
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

extern void sceVu0UnitMatrix(void *m);
extern void VecNormalize_13bd90(void *d, const void *s);
extern void MatScaleRows_13cf00(void *d, const void *s, const void *scale);

static f32 rg_rowlen(rg_vu0_state *rg_vu0_p_, const void *row)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

    rg_vlensq(&rg_vu0, row);
    rg_vu0_sqrt(5, RG_BC_X);                            /* vsqrt Q, vf5x; vwaitq */
    return rg_vu0_getq();                               /* cfc2 $2, vi22; mtc1 $2, $f0 */

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* Turn the 3x3 part of m to face target in the XZ plane (yaw only), keeping
   each row's original length: rows become (z,0,-x), (0,1,0), (x,0,z) of the
   normalised horizontal direction, scaled. */
void MtxYawFaceTarget_13cb30(void *m, const void *target)
{ RG_VU0_FRAME;
    char *pm = (char *)m;
    f32 sc[4];                                          /* sp+0x70 */
    f32 r[16];                                          /* sp+0x30: rows 0x30 0x40 0x50 0x60 */
    f32 x, z;

    sc[0] = rg_rowlen(&rg_vu0, pm);                              /* sw $2, 0x70($29) */
    sc[1] = rg_rowlen(&rg_vu0, pm + 0x10);                       /* sw $2, 0x74($29) */
    sc[2] = rg_rowlen(&rg_vu0, pm + 0x20);                       /* sw $2, 0x78($29) */
    sc[3] = 0.0f;                                       /* 0x7C is never written by retail */
    sceVu0UnitMatrix(r);                                /* jal sceVu0UnitMatrix(sp+0x30) */
    rg_vsub(&rg_vu0, &r[8], target, pm + 0x30);                  /* sp+0x50 = target - m.r[3] */
    *(u32 *)&r[9] = 0;                                  /* sw $0, 0x54($29) */
    *(u32 *)&r[11] = 0;                                 /* sw $0, 0x5C($29) (jal slot) */
    VecNormalize_13bd90(&r[8], &r[8]);
    z = r[10];                                          /* lwc1 $f0, 0x58($29) */
    x = r[8];                                           /* lwc1 $f1, 0x50($29) */
    r[0] = z;                                           /* swc1 $f0, 0x30($29) */
    r[10] = z;                                          /* swc1 $f0, 0x58($29) */
    r[2] = -x;                                          /* neg.s; swc1 $f0, 0x38($29) */
    r[8] = x;                                           /* swc1 $f1, 0x50($29) (jal slot) */
    MatScaleRows_13cf00(r, r, sc);
    __builtin_memcpy(pm, &r[0], 16);                    /* lq/sq rows 0..2 */
    __builtin_memcpy(pm + 0x10, &r[4], 16);
    __builtin_memcpy(pm + 0x20, &r[8], 16);
}
