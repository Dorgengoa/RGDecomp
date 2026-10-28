/* rg-override: replaces game/src/main/vec/VecTriCross_13de70.c sha256 4503a0deb602f6648c534cc31ff90f268eb5f5711ee56db95f8431d46691268f
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecTriCross_13de70(void *d, const void *a, const void *b, const void *c)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(15, (char *)(a)); /* lqc2       $vf15, 0x0($5) */
    rg_vu0_lqc2(16, (char *)(b)); /* lqc2       $vf16, 0x0($6) */
    rg_vu0_lqc2(17, (char *)(c)); /* lqc2       $vf17, 0x0($7) */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 10, 16, 15, RG_BC_NONE); /* vsub.xyzw  $vf10, $vf16, $vf15 */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 11, 17, 15, RG_BC_NONE); /* vsub.xyzw  $vf11, $vf17, $vf15 */
    rg_vu0_opmula(10, 11); /* vopmula.xyz $ACC, $vf10, $vf11 */
    rg_vu0_opmsub(12, 11, 10); /* vopmsub.xyz $vf12, $vf11, $vf10 */
    rg_vu0_sqc2(12, (char *)(d)); /* sqc2      $vf12, 0x0($4) */
}
