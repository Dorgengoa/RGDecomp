/* rg-override: replaces game/src/main/vec/BBoxUnion_13dea0.c sha256 8a76821561c4c9ee47c454cd18aed078597eed8fadd302a3cf9366653b395b5c
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void BBoxUnion_13dea0(void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(15, (char *)(a)); /* lqc2       $vf15, 0x0($4) */
    rg_vu0_lqc2(16, (char *)(a) + 0x10); /* lqc2       $vf16, 0x10($4) */
    rg_vu0_lqc2(17, (char *)(b)); /* lqc2       $vf17, 0x0($5) */
    rg_vu0_lqc2(18, (char *)(b) + 0x10); /* lqc2       $vf18, 0x10($5) */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 20, 15, 16, RG_BC_NONE); /* vmax.xyzw  $vf20, $vf15, $vf16 */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 21, 15, 16, RG_BC_NONE); /* vmini.xyzw $vf21, $vf15, $vf16 */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 20, 20, 17, RG_BC_NONE); /* vmax.xyzw  $vf20, $vf20, $vf17 */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 21, 21, 17, RG_BC_NONE); /* vmini.xyzw $vf21, $vf21, $vf17 */
    rg_vu0_fmac(RG_VMAX, RG_XYZW, 20, 20, 18, RG_BC_NONE); /* vmax.xyzw  $vf20, $vf20, $vf18 */
    rg_vu0_fmac(RG_VMINI, RG_XYZW, 21, 21, 18, RG_BC_NONE); /* vmini.xyzw $vf21, $vf21, $vf18 */
    rg_vu0_sqc2(20, (char *)(a)); /* sqc2       $vf20, 0x0($4) */
    rg_vu0_sqc2(21, (char *)(a) + 0x10); /* sqc2      $vf21, 0x10($4) */
}
