/* rg-override: replaces game/src/main/matrix/MatMul33_13d180.c sha256 21bff7b8172a1dfd08eb6dcac4f6f9d3def000ce50e9effcc99b7b09663226c6
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void MatMul33_13d180(void *d, const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(1, (char *)(a)); /* lqc2       $vf1, 0x0($5) */
    rg_vu0_lqc2(2, (char *)(a) + 0x10); /* lqc2       $vf2, 0x10($5) */
    rg_vu0_lqc2(3, (char *)(a) + 0x20); /* lqc2       $vf3, 0x20($5) */
    rg_vu0_lqc2(5, (char *)(b)); /* lqc2       $vf5, 0x0($6) */
    rg_vu0_lqc2(6, (char *)(b) + 0x10); /* lqc2       $vf6, 0x10($6) */
    rg_vu0_lqc2(7, (char *)(b) + 0x20); /* lqc2       $vf7, 0x20($6) */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 5, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf5x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 5, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf5y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 20, 3, 5, RG_BC_Z); /* vmaddz.xyzw $vf20, $vf3, $vf5z */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 6, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf6x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 6, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf6y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 21, 3, 6, RG_BC_Z); /* vmaddz.xyzw $vf21, $vf3, $vf6z */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 7, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf7x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 7, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf7y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 22, 3, 7, RG_BC_Z); /* vmaddz.xyzw $vf22, $vf3, $vf7z */
    rg_vu0_sqc2(20, (char *)(d)); /* sqc2       $vf20, 0x0($4) */
    rg_vu0_sqc2(21, (char *)(d) + 0x10); /* sqc2       $vf21, 0x10($4) */
    rg_vu0_sqc2(22, (char *)(d) + 0x20); /* sqc2      $vf22, 0x20($4) */
}
