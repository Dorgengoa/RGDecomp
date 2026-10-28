/* rg-override: replaces game/src/main/vec/VecMaxMin_13df70.c sha256 57a1caf3ae31c036e1c34ec2232e675f0299a6d6075a759d6c0d675fcf6dcdd7
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecMaxMin_13df70(void *mx, void *mn, const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(15, (char *)(a)); /* lqc2       $vf15, 0x0($6) */
    rg_vu0_lqc2(16, (char *)(b)); /* lqc2       $vf16, 0x0($7) */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 18, 15, 16, RG_BC_NONE); /* vmax.xyzw  $vf18, $vf15, $vf16 */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 20, 15, 16, RG_BC_NONE); /* vmini.xyzw $vf20, $vf15, $vf16 */
    rg_vu0_sqc2(18, (char *)(mx)); /* sqc2       $vf18, 0x0($4) */
    rg_vu0_sqc2(20, (char *)(mn)); /* sqc2      $vf20, 0x0($5) */
}
