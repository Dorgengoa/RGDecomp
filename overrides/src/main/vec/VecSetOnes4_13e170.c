/* rg-override: replaces game/src/main/vec/VecSetOnes4_13e170.c sha256 57cef282672938c03bd34af34f677b01cd94ef78beec7aedd03b675c6c740db5
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecSetOnes4_13e170(void *d)
{ RG_VU0_FRAME;
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 1, 0, 0, RG_BC_W); /* vmaxw.xyzw $vf1, $vf0, $vf0w */
    rg_vu0_sqc2(1, (char *)(d)); /* sqc2      $vf1, 0x0($4) */
}
