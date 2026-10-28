/* rg-override: replaces game/src/main/matrix/MtxProjectPoint_13c8c0.c sha256 039669e379332a2181c117bf6f1cdd10c1dc5cf05ef9639c83358fb999ba920b
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void MtxProjectPoint_13c8c0(void *d, const void *m, const void *v)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, (char *)(m)); /* lqc2       $vf4, 0x0($5) */
    rg_vu0_lqc2(5, (char *)(m) + 0x10); /* lqc2       $vf5, 0x10($5) */
    rg_vu0_lqc2(6, (char *)(m) + 0x20); /* lqc2       $vf6, 0x20($5) */
    rg_vu0_lqc2(7, (char *)(m) + 0x30); /* lqc2       $vf7, 0x30($5) */
    rg_vu0_lqc2(8, (char *)(v)); /* lqc2       $vf8, 0x0($6) */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 8, RG_BC_X); /* vmulax.xyzw $ACC, $vf4, $vf8x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 5, 8, RG_BC_Y); /* vmadday.xyzw $ACC, $vf5, $vf8y */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 6, 8, RG_BC_Z); /* vmaddaz.xyzw $ACC, $vf6, $vf8z */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 9, 7, 8, RG_BC_W); /* vmaddw.xyzw $vf9, $vf7, $vf8w */
    rg_vu0_div(0, RG_BC_W, 9, RG_BC_W); /* vdiv       $Q, $vf0w, $vf9w */
    /* vwaitq */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 9, 9, RG_FT_Q, RG_BC_NONE); /* vmulq.xyz  $vf9, $vf9, $Q */
    rg_vu0_sqc2(9, (char *)(d)); /* sqc2      $vf9, 0x0($4) */
}
