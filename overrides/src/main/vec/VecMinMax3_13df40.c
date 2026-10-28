/* rg-override: replaces game/src/main/vec/VecMinMax3_13df40.c sha256 da3e7fa40aa526ec14f01e62ed3dfbfda484c03240b0a2018e588cc3b143d2ee
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecMinMax3_13df40(void *mx, void *mn, const void *a, const void *b, const void *c)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(15, (char *)(a)); /* lqc2       $vf15, 0x0($6) */
    rg_vu0_lqc2(16, (char *)(b)); /* lqc2       $vf16, 0x0($7) */
    rg_vu0_lqc2(17, (char *)(c)); /* lqc2       $vf17, 0x0($8) */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 18, 15, 16, RG_BC_NONE); /* vmax.xyzw  $vf18, $vf15, $vf16 */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 20, 15, 16, RG_BC_NONE); /* vmini.xyzw $vf20, $vf15, $vf16 */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 19, 18, 17, RG_BC_NONE); /* vmax.xyzw  $vf19, $vf18, $vf17 */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 21, 20, 17, RG_BC_NONE); /* vmini.xyzw $vf21, $vf20, $vf17 */
    rg_vu0_sqc2(19, (char *)(mx)); /* sqc2       $vf19, 0x0($4) */
    rg_vu0_sqc2(21, (char *)(mn)); /* sqc2      $vf21, 0x0($5) */
}
