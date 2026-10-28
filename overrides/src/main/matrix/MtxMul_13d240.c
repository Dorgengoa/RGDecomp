/* rg-override: replaces game/src/main/matrix/MtxMul_13d240.c sha256 3c9ebd0542c605419dfc7bfadea778d5c2b0af31b08f6fc2bc8530f7edc69d87
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void MtxMul_13d240(void *d, const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(1, (char *)(a)); /* lqc2       $vf1, 0x0($5) */
    rg_vu0_lqc2(2, (char *)(a) + 0x10); /* lqc2       $vf2, 0x10($5) */
    rg_vu0_lqc2(3, (char *)(a) + 0x20); /* lqc2       $vf3, 0x20($5) */
    rg_vu0_lqc2(4, (char *)(a) + 0x30); /* lqc2       $vf4, 0x30($5) */
    rg_vu0_lqc2(5, (char *)(b)); /* lqc2       $vf5, 0x0($6) */
    rg_vu0_lqc2(6, (char *)(b) + 0x10); /* lqc2       $vf6, 0x10($6) */
    rg_vu0_lqc2(7, (char *)(b) + 0x20); /* lqc2       $vf7, 0x20($6) */
    rg_vu0_lqc2(8, (char *)(b) + 0x30); /* lqc2       $vf8, 0x30($6) */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 5, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf5x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 5, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf5y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 3, 5, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf3, $vf5z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 20, 4, 5, RG_BC_W); /* vmaddw.xyzw $vf20, $vf4, $vf5w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 6, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf6x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 6, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf6y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 3, 6, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf3, $vf6z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 21, 4, 6, RG_BC_W); /* vmaddw.xyzw $vf21, $vf4, $vf6w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 7, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf7x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 7, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf7y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 3, 7, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf3, $vf7z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 22, 4, 7, RG_BC_W); /* vmaddw.xyzw $vf22, $vf4, $vf7w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 1, 8, RG_BC_X); /* vmulax.xyzw $ACC, $vf1, $vf8x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 2, 8, RG_BC_Y); /* vmadday.xyzw $ACC, $vf2, $vf8y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 3, 8, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf3, $vf8z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 23, 4, 8, RG_BC_W); /* vmaddw.xyzw $vf23, $vf4, $vf8w */
    rg_vu0_sqc2(20, (char *)(d)); /* sqc2       $vf20, 0x0($4) */
    rg_vu0_sqc2(21, (char *)(d) + 0x10); /* sqc2       $vf21, 0x10($4) */
    rg_vu0_sqc2(22, (char *)(d) + 0x20); /* sqc2       $vf22, 0x20($4) */
    rg_vu0_sqc2(23, (char *)(d) + 0x30); /* sqc2      $vf23, 0x30($4) */
}
