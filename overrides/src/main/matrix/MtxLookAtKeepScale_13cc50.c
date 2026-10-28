/* rg-override: replaces game/src/main/matrix/MtxLookAtKeepScale_13cc50.c sha256 ca274b5fca3e6b9104127b8b1412982cca53fee55395a064deff0433925c115e
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

extern f32 D_0047DE00, D_0047DE04, D_0047DE08, D_0047DE0C; /* -0x7370(gp).. = {0, 1, 0, 0} */
extern void sceVu0UnitMatrix(void *m);
extern void sceVu0OuterProduct(void *d, void *a, void *b);
extern void VecNormalize_13bd90(void *d, const void *s);
extern void MatScaleRows_13cf00(void *d, const void *s, const void *scale);

/* Row length of m->r[i].xyz via the VU0 square root (vsqrt Q; cfc2 vi22). */
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

/* Re-aim the 3x3 part of m at target (from m's translation row), with world
   up (0,1,0), keeping each row's original length.  Rows 0-2 are rewritten;
   row 3 (translation) is untouched. */
void MtxLookAtKeepScale_13cc50(void *m, const void *target)
{ RG_VU0_FRAME;
    char *pm = (char *)m;
    f32 sc[4];                                          /* sp+0xC0 */
    f32 tmpm[16];                                       /* sp+0x40 (unit matrix, unused) */
    f32 r[16];                                          /* sp+0x80: rows 0x80 0x90 0xA0 0xB0 */
    f32 up[4];                                          /* sp+0x30 */

    sc[0] = rg_rowlen(&rg_vu0, pm);                              /* sw $2, 0xC0($29) */
    sc[1] = rg_rowlen(&rg_vu0, pm + 0x10);                       /* sw $2, 0xC4($29) */
    sc[2] = rg_rowlen(&rg_vu0, pm + 0x20);                       /* sw $2, 0xC8($29) */
    sc[3] = 0.0f;                                       /* 0xCC is never written by retail */
    sceVu0UnitMatrix(r);                                /* jal sceVu0UnitMatrix(sp+0x80) */
    sceVu0UnitMatrix(tmpm);                             /* jal sceVu0UnitMatrix(sp+0x40) */
    up[0] = D_0047DE00;
    up[1] = D_0047DE04;
    up[2] = D_0047DE08;
    up[3] = D_0047DE0C;
    rg_vsub(&rg_vu0, &r[8], target, pm + 0x30);                  /* sp+0xA0 = target - m.r[3] */
    *(u32 *)&r[11] = 0;                                 /* sw $0, 0xAC($29) (jal slot) */
    VecNormalize_13bd90(&r[8], &r[8]);
    sceVu0OuterProduct(&r[0], up, &r[8]);               /* row0 = up x fwd */
    VecNormalize_13bd90(&r[0], &r[0]);
    sceVu0OuterProduct(&r[4], &r[8], &r[0]);            /* row1 = fwd x row0 */
    MatScaleRows_13cf00(r, r, sc);
    __builtin_memcpy(pm, &r[0], 16);                    /* lq/sq rows 0..2 */
    __builtin_memcpy(pm + 0x10, &r[4], 16);
    __builtin_memcpy(pm + 0x20, &r[8], 16);
}
