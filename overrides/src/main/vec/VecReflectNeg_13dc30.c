/* rg-override: replaces game/src/main/vec/VecReflectNeg_13dc30.c sha256 0965d5903d4ed495f0fc4cc2683ba0960ee4b3820c11f9ffa3dfd74274ce8a3d
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* out = (b - c) - (-2 * dot3(n, c - b)) * n, through two stack temps exactly as
   the listing stages it (out may alias the inputs). */
void VecReflectNeg_13dc30(const void *n, const void *b, const void *c, void *out)
{ RG_VU0_FRAME;
    u8 t0[16], t1[16];                                      /* sp+0x00, sp+0x10 */
    f32 dot, k;

    rg_vu0_lqc2(4, c);                                      /* lqc2 vf4, 0($6) */
    rg_vu0_lqc2(5, b);                                      /* lqc2 vf5, 0($5) */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 6, 4, 5, RG_BC_NONE);     /* vsub.xyzw vf6, vf4, vf5 */
    rg_vu0_sqc2(6, t0);                                     /* sqc2 vf6, 0($2=sp) */
    rg_vu0_lqc2(4, n);                                      /* lqc2 vf4, 0($4) */
    rg_vu0_lqc2(5, t0);                                     /* lqc2 vf5, 0($2) */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 5, 4, 5, RG_BC_NONE);      /* vmul.xyz vf5, vf4, vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Y);           /* vaddy.x vf5, vf5, vf5y */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Z);           /* vaddz.x vf5, vf5, vf5z */
    dot = rg_vu0_getf(5, 0);                                /* qmfc2 $2, vf5; mtc1 $2, $f1 */
    k = -(2.0f * dot);                                      /* mul.s $f0, 2.0, $f1; neg.s $f1, $f0 */
    rg_vu0_lqc2(4, n);                                      /* lqc2 vf4, 0($4) */
    rg_vu0_mfc1(8, k);                                      /* mfc1 $8, $f1 */
    rg_vu0_qmtc2(8, 5);                                     /* qmtc2 $8, vf5 */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 6, 4, 5, RG_BC_X);        /* vmulx.xyzw vf6, vf4, vf5x */
    rg_vu0_sqc2(6, t1);                                     /* sqc2 vf6, 0($2=sp+0x10) */
    rg_vu0_lqc2(4, b);                                      /* lqc2 vf4, 0($5) */
    rg_vu0_lqc2(5, c);                                      /* lqc2 vf5, 0($6) */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 6, 4, 5, RG_BC_NONE);     /* vsub.xyzw vf6, vf4, vf5 */
    rg_vu0_sqc2(6, out);                                    /* sqc2 vf6, 0($7) */
    rg_vu0_lqc2(4, out);                                    /* lqc2 vf4, 0($7) */
    rg_vu0_lqc2(5, t1);                                     /* lqc2 vf5, 0($2) */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 6, 4, 5, RG_BC_NONE);     /* vsub.xyzw vf6, vf4, vf5 */
    rg_vu0_sqc2(6, out);                                    /* sqc2 vf6, 0($7) */
}
