/* rg-override: replaces game/src/main/vec/VecLengthSqXZ_13d410.c sha256 a3a48024d6edba1d227e160c7f4720ba187fea954eb09e613c89b310d753dcd9
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

f32 VecLengthSqXZ_13d410(const void *v)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, (char *)(v)); /* lqc2       $vf4, 0x0($4) */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 4, 4, 4, RG_BC_NONE); /* vmul.xyz   $vf4, $vf4, $vf4 */
    rg_vu0_mr32(RG_XY, 5, 4); /* vmr32.xy   $vf5, $vf4 */
    rg_vu0_mr32(RG_X, 6, 5); /* vmr32.x    $vf6, $vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 7, 4, 6, RG_BC_NONE); /* vadd.x     $vf7, $vf4, $vf6 */
    /* qmfc2.ni   $2, $vf7 */
    /* mtc1       $2, $f0 */
    /* nop */
    return rg_vu0_getf(7, 0); /* qmfc2 $2, vf7; mtc1 $2, $f0 (lane x) */
}
