/* rg-override: replaces game/src/main/vec/VecMulXyz_13bd20.c sha256 5add5e1e97e594f14d3f2ca13a58c268a288161356480acc3f5bd3d08dc2eacd
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecMulXyz_13bd20(void *d, const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, (char *)(a)); /* lqc2       $vf4, 0x0($5) */
    rg_vu0_lqc2(5, (char *)(b)); /* lqc2       $vf5, 0x0($6) */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 4, 4, 5, RG_BC_NONE); /* vmul.xyz   $vf4, $vf4, $vf5 */
    rg_vu0_sqc2(4, (char *)(d)); /* sqc2      $vf4, 0x0($4) */
}
