/* rg-override: replaces game/src/main/matrix/MtxMulDir_13c860.c sha256 48e01276ceee7656c5f34e278af828452f1c6ee1fb3774607fd56ee38a2ae1cb
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void MtxMulDir_13c860(void *d, const void *m, const void *v)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(16, (char *)(v)); /* lqc2       $vf16, 0x0($6) */
    rg_vu0_lqc2(10, (char *)(m)); /* lqc2       $vf10, 0x0($5) */
    rg_vu0_lqc2(11, (char *)(m) + 0x10); /* lqc2       $vf11, 0x10($5) */
    rg_vu0_lqc2(12, (char *)(m) + 0x20); /* lqc2       $vf12, 0x20($5) */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 10, 16, RG_BC_X); /* vmulax.xyzw $ACC, $vf10, $vf16x */
    rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 11, 16, RG_BC_Y); /* vmadday.xyzw $ACC, $vf11, $vf16y */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 17, 12, 16, RG_BC_Z); /* vmaddz.xyzw $vf17, $vf12, $vf16z */
    rg_vu0_sqc2(17, (char *)(d)); /* sqc2      $vf17, 0x0($4) */
}
