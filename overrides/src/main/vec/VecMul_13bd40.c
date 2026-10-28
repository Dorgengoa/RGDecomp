/* rg-override: replaces game/src/main/vec/VecMul_13bd40.c sha256 bc013cbbbaa0407c7eeb8a6dc7a49d3082fb703b1fabcd973c6c4d728a94e550
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecMul_13bd40(void *d, const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, (char *)(a)); /* lqc2      vf4, 0x0($5) */
    rg_vu0_lqc2(5, (char *)(b)); /* lqc2      vf5, 0x0($6) */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 6, 4, 5, RG_BC_NONE); /* vmul.xyzw vf6, vf4, vf5 */
    rg_vu0_sqc2(6, (char *)(d)); /* sqc2      vf6, 0x0($4) */
}
