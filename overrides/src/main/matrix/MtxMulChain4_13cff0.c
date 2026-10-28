/* rg-override: replaces game/src/main/matrix/MtxMulChain4_13cff0.c sha256 ad46d07b817458d772832d9b07d9aaa9a6d6ee47e4a5cb7eb7cf338d550516a6
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void MtxMulChain4_13cff0(void *d, const void *a, const void *b, const void *c, const void *e)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(1, (char *)(a)); /* lqc2       $vf1, 0x0($5) */
    rg_vu0_lqc2(2, (char *)(a) + 0x10); /* lqc2       $vf2, 0x10($5) */
    rg_vu0_lqc2(3, (char *)(a) + 0x20); /* lqc2       $vf3, 0x20($5) */
    rg_vu0_lqc2(4, (char *)(a) + 0x30); /* lqc2       $vf4, 0x30($5) */
    rg_vu0_lqc2(5, (char *)(b)); /* lqc2       $vf5, 0x0($6) */
    rg_vu0_lqc2(6, (char *)(b) + 0x10); /* lqc2       $vf6, 0x10($6) */
    rg_vu0_lqc2(7, (char *)(b) + 0x20); /* lqc2       $vf7, 0x20($6) */
    rg_vu0_lqc2(8, (char *)(b) + 0x30); /* lqc2       $vf8, 0x30($6) */
    rg_vu0_lqc2(9, (char *)(c)); /* lqc2       $vf9, 0x0($7) */
    rg_vu0_lqc2(10, (char *)(c) + 0x10); /* lqc2       $vf10, 0x10($7) */
    rg_vu0_lqc2(11, (char *)(c) + 0x20); /* lqc2       $vf11, 0x20($7) */
    rg_vu0_lqc2(12, (char *)(c) + 0x30); /* lqc2       $vf12, 0x30($7) */
    rg_vu0_lqc2(13, (char *)(e)); /* lqc2       $vf13, 0x0($8) */
    rg_vu0_lqc2(14, (char *)(e) + 0x10); /* lqc2       $vf14, 0x10($8) */
    rg_vu0_lqc2(15, (char *)(e) + 0x20); /* lqc2       $vf15, 0x20($8) */
    rg_vu0_lqc2(16, (char *)(e) + 0x30); /* lqc2       $vf16, 0x30($8) */
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
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 20, 9, RG_BC_X); /* vmulax.xyzw $ACC, $vf20, $vf9x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 21, 9, RG_BC_Y); /* vmadday.xyzw $ACC, $vf21, $vf9y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 22, 9, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf22, $vf9z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 24, 23, 9, RG_BC_W); /* vmaddw.xyzw $vf24, $vf23, $vf9w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 20, 10, RG_BC_X); /* vmulax.xyzw $ACC, $vf20, $vf10x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 21, 10, RG_BC_Y); /* vmadday.xyzw $ACC, $vf21, $vf10y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 22, 10, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf22, $vf10z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 25, 23, 10, RG_BC_W); /* vmaddw.xyzw $vf25, $vf23, $vf10w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 20, 11, RG_BC_X); /* vmulax.xyzw $ACC, $vf20, $vf11x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 21, 11, RG_BC_Y); /* vmadday.xyzw $ACC, $vf21, $vf11y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 22, 11, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf22, $vf11z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 26, 23, 11, RG_BC_W); /* vmaddw.xyzw $vf26, $vf23, $vf11w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 20, 12, RG_BC_X); /* vmulax.xyzw $ACC, $vf20, $vf12x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 21, 12, RG_BC_Y); /* vmadday.xyzw $ACC, $vf21, $vf12y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 22, 12, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf22, $vf12z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 27, 23, 12, RG_BC_W); /* vmaddw.xyzw $vf27, $vf23, $vf12w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 24, 13, RG_BC_X); /* vmulax.xyzw $ACC, $vf24, $vf13x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 25, 13, RG_BC_Y); /* vmadday.xyzw $ACC, $vf25, $vf13y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 26, 13, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf26, $vf13z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 20, 27, 13, RG_BC_W); /* vmaddw.xyzw $vf20, $vf27, $vf13w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 24, 14, RG_BC_X); /* vmulax.xyzw $ACC, $vf24, $vf14x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 25, 14, RG_BC_Y); /* vmadday.xyzw $ACC, $vf25, $vf14y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 26, 14, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf26, $vf14z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 21, 27, 14, RG_BC_W); /* vmaddw.xyzw $vf21, $vf27, $vf14w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 24, 15, RG_BC_X); /* vmulax.xyzw $ACC, $vf24, $vf15x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 25, 15, RG_BC_Y); /* vmadday.xyzw $ACC, $vf25, $vf15y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 26, 15, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf26, $vf15z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 22, 27, 15, RG_BC_W); /* vmaddw.xyzw $vf22, $vf27, $vf15w */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 24, 16, RG_BC_X); /* vmulax.xyzw $ACC, $vf24, $vf16x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 25, 16, RG_BC_Y); /* vmadday.xyzw $ACC, $vf25, $vf16y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 26, 16, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf26, $vf16z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 23, 27, 16, RG_BC_W); /* vmaddw.xyzw $vf23, $vf27, $vf16w */
    rg_vu0_sqc2(20, (char *)(d)); /* sqc2       $vf20, 0x0($4) */
    rg_vu0_sqc2(21, (char *)(d) + 0x10); /* sqc2       $vf21, 0x10($4) */
    rg_vu0_sqc2(22, (char *)(d) + 0x20); /* sqc2       $vf22, 0x20($4) */
    rg_vu0_sqc2(23, (char *)(d) + 0x30); /* sqc2      $vf23, 0x30($4) */
}
