/* rg-override: replaces game/src/main/vec/VecMin_13df90.c sha256 daf2c0dd4db9ec478cabe424b2c7151e5fa769907b5fa3a21b1a30e80213a607
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecMin_13df90(void *d, const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(15, (char *)(a)); /* lqc2       $vf15, 0x0($5) */
    rg_vu0_lqc2(16, (char *)(b)); /* lqc2       $vf16, 0x0($6) */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 18, 15, 16, RG_BC_NONE); /* vmini.xyzw $vf18, $vf15, $vf16 */
    rg_vu0_sqc2(18, (char *)(d)); /* sqc2      $vf18, 0x0($4) */
}
