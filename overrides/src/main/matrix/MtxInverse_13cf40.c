/* rg-override: replaces game/src/main/matrix/MtxInverse_13cf40.c sha256 8ecd3e9c3587531c7438c7e0079fd16eb01cc4002793610b2973cb77d2e09ac5
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void MtxInverse_13cf40(void *d, const void *s)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(1, (char *)(s)); /* lqc2       $vf1, 0x0($5) */
    rg_vu0_lqc2(2, (char *)(s) + 0x10); /* lqc2       $vf2, 0x10($5) */
    rg_vu0_lqc2(3, (char *)(s) + 0x20); /* lqc2       $vf3, 0x20($5) */
    rg_vu0_lqc2(4, (char *)(s) + 0x30); /* lqc2       $vf4, 0x30($5) */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 5, 5, 5, RG_BC_NONE); /* vsub.xyzw  $vf5, $vf5, $vf5 */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 6, 6, 6, RG_BC_NONE); /* vsub.xyzw  $vf6, $vf6, $vf6 */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 7, 7, 7, RG_BC_NONE); /* vsub.xyzw  $vf7, $vf7, $vf7 */
    rg_vu0_fmac(RG_VADD, RG_XYZW, 8, 0, 0, RG_BC_X); /* vaddx.xyzw $vf8, $vf0, $vf0x */
    rg_vu0_opmula(2, 3); /* vopmula.xyz $ACC, $vf2, $vf3 */
    rg_vu0_opmsub(10, 3, 2); /* vopmsub.xyz $vf10, $vf3, $vf2 */
    rg_vu0_opmula(3, 1); /* vopmula.xyz $ACC, $vf3, $vf1 */
    rg_vu0_opmsub(11, 1, 3); /* vopmsub.xyz $vf11, $vf1, $vf3 */
    rg_vu0_opmula(1, 2); /* vopmula.xyz $ACC, $vf1, $vf2 */
    rg_vu0_opmsub(12, 2, 1); /* vopmsub.xyz $vf12, $vf2, $vf1 */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 15, 10, 1, RG_BC_NONE); /* vmul.xyz   $vf15, $vf10, $vf1 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 0, 10, RG_BC_X); /* vaddx.x    $vf5, $vf0, $vf10x */
    rg_vu0_fmac(RG_VADD, RG_X, 6, 0, 10, RG_BC_Y); /* vaddy.x    $vf6, $vf0, $vf10y */
    rg_vu0_fmac(RG_VADD, RG_X, 7, 0, 10, RG_BC_Z); /* vaddz.x    $vf7, $vf0, $vf10z */
    rg_vu0_fmac(RG_VADD, RG_X, 15, 15, 15, RG_BC_Y); /* vaddy.x    $vf15, $vf15, $vf15y */
    rg_vu0_fmac(RG_VADD, RG_Y, 5, 0, 11, RG_BC_X); /* vaddx.y    $vf5, $vf0, $vf11x */
    rg_vu0_fmac(RG_VADD, RG_Y, 6, 0, 11, RG_BC_Y); /* vaddy.y    $vf6, $vf0, $vf11y */
    rg_vu0_fmac(RG_VADD, RG_Y, 7, 0, 11, RG_BC_Z); /* vaddz.y    $vf7, $vf0, $vf11z */
    rg_vu0_fmac(RG_VADD, RG_X, 15, 15, 15, RG_BC_Z); /* vaddz.x    $vf15, $vf15, $vf15z */
    rg_vu0_fmac(RG_VADD, RG_Z, 5, 0, 12, RG_BC_X); /* vaddx.z    $vf5, $vf0, $vf12x */
    rg_vu0_fmac(RG_VADD, RG_Z, 6, 0, 12, RG_BC_Y); /* vaddy.z    $vf6, $vf0, $vf12y */
    rg_vu0_fmac(RG_VADD, RG_Z, 7, 0, 12, RG_BC_Z); /* vaddz.z    $vf7, $vf0, $vf12z */
    rg_vu0_div(0, RG_BC_W, 15, RG_BC_X); /* vdiv       $Q, $vf0w, $vf15x */
    /* vwaitq */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 5, 5, RG_FT_Q, RG_BC_NONE); /* vmulq.xyz  $vf5, $vf5, $Q */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 6, 6, RG_FT_Q, RG_BC_NONE); /* vmulq.xyz  $vf6, $vf6, $Q */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 7, 7, RG_FT_Q, RG_BC_NONE); /* vmulq.xyz  $vf7, $vf7, $Q */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 5, 4, RG_BC_X); /* vmulax.xyzw $ACC, $vf5, $vf4x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 6, 4, RG_BC_Y); /* vmadday.xyzw $ACC, $vf6, $vf4y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 8, 7, 4, RG_BC_Z); /* vmaddz.xyzw $vf8, $vf7, $vf4z */
    rg_vu0_fmac(RG_VSUB, RG_XYZ, 8, 0, 8, RG_BC_NONE); /* vsub.xyz   $vf8, $vf0, $vf8 */
    rg_vu0_fmac(RG_VADD, RG_W, 8, 0, 0, RG_BC_X); /* vaddx.w    $vf8, $vf0, $vf0x */
    rg_vu0_sqc2(5, (char *)(d)); /* sqc2       $vf5, 0x0($4) */
    rg_vu0_sqc2(6, (char *)(d) + 0x10); /* sqc2       $vf6, 0x10($4) */
    rg_vu0_sqc2(7, (char *)(d) + 0x20); /* sqc2       $vf7, 0x20($4) */
    rg_vu0_sqc2(8, (char *)(d) + 0x30); /* sqc2      $vf8, 0x30($4) */
}
