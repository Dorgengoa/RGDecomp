/* rg-override: replaces game/src/main/vec/VecSetOnes_13e180.c sha256 ad6b89d1e37f249edc3f1f4359f00753d9ab44439d507bdfd3265cec7e101c5b
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecSetOnes_13e180(void *d)
{ RG_VU0_FRAME;
    rg_vu0_fmac(RG_VMAX, RG_XYZ, 1, 0, 0, RG_BC_W); /* vmaxw.xyz  $vf1, $vf0, $vf0w */
    rg_vu0_fmac(RG_VMUL, RG_W, 1, 0, 0, RG_BC_X); /* vmulx.w    $vf1, $vf0, $vf0x */
    rg_vu0_sqc2(1, (char *)(d)); /* sqc2      $vf1, 0x0($4) */
}
