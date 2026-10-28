/* rg-override: replaces game/src/main/vec/Vu0InnerProduct_13bd60.c sha256 a7b24a77e1c26a1d7071f1ff7ea375be61e95872149ab97acb3a27bfb8d5434d
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

f32 Vu0InnerProduct_13bd60(const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, (char *)(a)); /* lqc2      vf4, 0x0($4) */
    rg_vu0_lqc2(5, (char *)(b)); /* lqc2      vf5, 0x0($5) */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 5, 4, 5, RG_BC_NONE); /* vmul.xyz  vf5, vf4, vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Y); /* vaddy.x   vf5, vf5, vf5y */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 5, 5, RG_BC_Z); /* vaddz.x   vf5, vf5, vf5z */
    /* qmfc2.ni  $2, vf5 */
    /* mtc1      $2, $f0 */
    return rg_vu0_getf(5, 0); /* qmfc2 $2, vf5; mtc1 $2, $f0 (lane x) */
}
