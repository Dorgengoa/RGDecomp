/* rg-override: replaces game/src/main/vec/BoundsAddPoint_13dee0.c sha256 ce0a83179d1ccbf7ed62ee679806378dccb10db520f938ba8c394edd155c7ce2
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void BoundsAddPoint_13dee0(void *mx, void *mn, const void *p)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(15, (char *)(mx)); /* lqc2       $vf15, 0x0($4) */
    rg_vu0_lqc2(16, (char *)(mn)); /* lqc2       $vf16, 0x0($5) */
    rg_vu0_lqc2(17, (char *)(p)); /* lqc2       $vf17, 0x0($6) */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 15, 15, 17, RG_BC_NONE); /* vmax.xyzw  $vf15, $vf15, $vf17 */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 16, 16, 17, RG_BC_NONE); /* vmini.xyzw $vf16, $vf16, $vf17 */
    rg_vu0_sqc2(15, (char *)(mx)); /* sqc2       $vf15, 0x0($4) */
    rg_vu0_sqc2(16, (char *)(mn)); /* sqc2      $vf16, 0x0($5) */
}
