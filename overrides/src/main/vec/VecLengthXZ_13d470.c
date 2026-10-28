/* rg-override: replaces game/src/main/vec/VecLengthXZ_13d470.c sha256 35ee58b40d4c552ceea8396e68ec8bdfe25d324c41c91281a8eded2ea736f41f
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

f32 VecLengthXZ_13d470(const void *v)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(4, (char *)(v)); /* lqc2       $vf4, 0x0($4) */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 4, 4, 4, RG_BC_NONE); /* vmul.xyz   $vf4, $vf4, $vf4 */
    rg_vu0_mr32(RG_XY, 5, 4); /* vmr32.xy   $vf5, $vf4 */
    rg_vu0_mr32(RG_X, 6, 5); /* vmr32.x    $vf6, $vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 7, 4, 6, RG_BC_NONE); /* vadd.x     $vf7, $vf4, $vf6 */
    rg_vu0_sqrt(7, RG_BC_X); /* .word      0x4A0703BD = vsqrt Q, vf7x */
    /* vwaitq */
    /* cfc2.ni    $2, $vi22 */
    /* mtc1       $2, $f0 */
    /* nop */
    return rg_vu0_getq(); /* cfc2 $2, vi22 (Q); mtc1 $2, $f0 */
}
