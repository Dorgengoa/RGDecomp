/* rg-override: replaces game/src/main/matrix/MatScaleRows_13cf00.c sha256 d356e4a9909688f48f0bc145b7ae07f0d4ffab310a5dd7822ead273eb839ca41
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void MatScaleRows_13cf00(void *d, const void *s, const void *scale)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(10, (char *)(scale)); /* lqc2       $vf10, 0x0($6) */
    rg_vu0_lqc2(1, (char *)(s)); /* lqc2       $vf1, 0x0($5) */
    rg_vu0_lqc2(2, (char *)(s) + 0x10); /* lqc2       $vf2, 0x10($5) */
    rg_vu0_lqc2(3, (char *)(s) + 0x20); /* lqc2       $vf3, 0x20($5) */
    rg_vu0_lqc2(4, (char *)(s) + 0x30); /* lqc2       $vf4, 0x30($5) */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 1, 1, 10, RG_BC_X); /* vmulx.xyzw $vf1, $vf1, $vf10x */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 2, 2, 10, RG_BC_Y); /* vmuly.xyzw $vf2, $vf2, $vf10y */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 3, 3, 10, RG_BC_Z); /* vmulz.xyzw $vf3, $vf3, $vf10z */
    rg_vu0_sqc2(1, (char *)(d)); /* sqc2       $vf1, 0x0($4) */
    rg_vu0_sqc2(2, (char *)(d) + 0x10); /* sqc2       $vf2, 0x10($4) */
    rg_vu0_sqc2(3, (char *)(d) + 0x20); /* sqc2       $vf3, 0x20($4) */
    rg_vu0_sqc2(4, (char *)(d) + 0x30); /* sqc2      $vf4, 0x30($4) */
}
