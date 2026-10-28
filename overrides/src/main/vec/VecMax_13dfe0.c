/* rg-override: replaces game/src/main/vec/VecMax_13dfe0.c sha256 ddba9e3a878c571ff3efc7a8372e154a147a921d2a3585538922519819581df0
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecMax_13dfe0(void *d, const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(15, (char *)(a)); /* lqc2       $vf15, 0x0($5) */
    rg_vu0_lqc2(16, (char *)(b)); /* lqc2       $vf16, 0x0($6) */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 18, 15, 16, RG_BC_NONE); /* vmax.xyzw  $vf18, $vf15, $vf16 */
    rg_vu0_sqc2(18, (char *)(d)); /* sqc2      $vf18, 0x0($4) */
}
