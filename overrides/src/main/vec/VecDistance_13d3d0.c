/* rg-override: replaces game/src/main/vec/VecDistance_13d3d0.c sha256 0f9bc13b15d744a735256b853e504e16a0a2917334b0448c003a8b24a7ff9589
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

f32 VecDistance_13d3d0(const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(2, (char *)(a)); /* lqc2       $vf2, 0x0($4) */
    rg_vu0_lqc2(3, (char *)(b)); /* lqc2       $vf3, 0x0($5) */
    rg_vu0_fmac(RG_VSUB, RG_XYZ, 4, 3, 2, RG_BC_NONE); /* vsub.xyz   $vf4, $vf3, $vf2 */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 4, 4, 4, RG_BC_NONE); /* vmul.xyz   $vf4, $vf4, $vf4 */
    rg_vu0_mr32(RG_XY, 5, 4); /* vmr32.xy   $vf5, $vf4 */
    rg_vu0_mr32(RG_X, 6, 5); /* vmr32.x    $vf6, $vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 7, 4, 5, RG_BC_NONE); /* vadd.x     $vf7, $vf4, $vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 6, 7, RG_BC_NONE); /* vadd.x     $vf5, $vf6, $vf7 */
    rg_vu0_sqrt(5, RG_BC_X); /* .word      0x4A0503BD */
    /* vwaitq */
    /* cfc2.ni    $2, $vi22 */
    /* mtc1       $2, $f0 */
    /* nop */
    return rg_vu0_getq(); /* cfc2 $2, vi22 (Q); mtc1 $2, $f0 */
}
