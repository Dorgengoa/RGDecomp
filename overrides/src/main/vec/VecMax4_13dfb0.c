/* rg-override: replaces game/src/main/vec/VecMax4_13dfb0.c sha256 09f3e468fb6d72c85cb41fccffb35227ff04867feb6357c4c3d98b5be2365bf4
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecMax4_13dfb0(void *d, const void *a, const void *b, const void *c, const void *e)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(15, (char *)(a)); /* lqc2       $vf15, 0x0($5) */
    rg_vu0_lqc2(16, (char *)(b)); /* lqc2       $vf16, 0x0($6) */
    rg_vu0_lqc2(17, (char *)(c)); /* lqc2       $vf17, 0x0($7) */
    rg_vu0_lqc2(18, (char *)(e)); /* lqc2       $vf18, 0x0($8) */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 20, 15, 16, RG_BC_NONE); /* vmax.xyzw  $vf20, $vf15, $vf16 */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 20, 20, 17, RG_BC_NONE); /* vmax.xyzw  $vf20, $vf20, $vf17 */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 20, 20, 18, RG_BC_NONE); /* vmax.xyzw  $vf20, $vf20, $vf18 */
    rg_vu0_sqc2(20, (char *)(d)); /* sqc2      $vf20, 0x0($4) */
}
