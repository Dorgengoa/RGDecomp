/* rg-override: replaces game/src/main/vec/BoundsFrom4Points_13df00.c sha256 cc9486632b1608e222db4b36452c53b206d8490b28c4e787c334dbcccfc0ed78
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void BoundsFrom4Points_13df00(void *mx, void *mn, const void *p0, const void *p1, const void *p2, const void *p3)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(15, (char *)(p0)); /* lqc2       $vf15, 0x0($6) */
    rg_vu0_lqc2(16, (char *)(p1)); /* lqc2       $vf16, 0x0($7) */
    rg_vu0_lqc2(17, (char *)(p2)); /* lqc2       $vf17, 0x0($8) */
    rg_vu0_lqc2(18, (char *)(p3)); /* lqc2       $vf18, 0x0($9) */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 20, 15, 16, RG_BC_NONE); /* vmax.xyzw  $vf20, $vf15, $vf16 */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 21, 15, 16, RG_BC_NONE); /* vmini.xyzw $vf21, $vf15, $vf16 */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 20, 20, 17, RG_BC_NONE); /* vmax.xyzw  $vf20, $vf20, $vf17 */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 21, 21, 17, RG_BC_NONE); /* vmini.xyzw $vf21, $vf21, $vf17 */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 20, 20, 18, RG_BC_NONE); /* vmax.xyzw  $vf20, $vf20, $vf18 */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 21, 21, 18, RG_BC_NONE); /* vmini.xyzw $vf21, $vf21, $vf18 */
    rg_vu0_sqc2(20, (char *)(mx)); /* sqc2       $vf20, 0x0($4) */
    rg_vu0_sqc2(21, (char *)(mn)); /* sqc2      $vf21, 0x0($5) */
}
