/* rg-override: replaces game/src/main/vec/VecLengthSq_13d440.c sha256 43e568bfa28f9fae61af3186e320843e37a19822a25c1d7d016b11bd75c10fd4
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

f32 VecLengthSq_13d440(const void *v)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, (char *)(v)); /* lqc2       $vf4, 0x0($4) */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 4, 4, 4, RG_BC_NONE); /* vmul.xyz   $vf4, $vf4, $vf4 */
    rg_vu0_mr32(RG_XY, 5, 4); /* vmr32.xy   $vf5, $vf4 */
    rg_vu0_mr32(RG_X, 6, 5); /* vmr32.x    $vf6, $vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 7, 4, 5, RG_BC_NONE); /* vadd.x     $vf7, $vf4, $vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 5, 6, 7, RG_BC_NONE); /* vadd.x     $vf5, $vf6, $vf7 */
    /* qmfc2.ni   $2, $vf5 */
    /* mtc1       $2, $f0 */
    /* nop */
    return rg_vu0_getf(5, 0); /* qmfc2 $2, vf5; mtc1 $2, $f0 (lane x) */
}
