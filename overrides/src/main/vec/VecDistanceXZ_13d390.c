/* rg-override: replaces game/src/main/vec/VecDistanceXZ_13d390.c sha256 30de2ae0f149054255daeb82b72afbe91b9ebcef5dacd7af7140c23c1c7b4d7c
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

f32 VecDistanceXZ_13d390(const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(2, (char *)(a)); /* lqc2       $vf2, 0x0($4) */
    rg_vu0_lqc2(3, (char *)(b)); /* lqc2       $vf3, 0x0($5) */
    rg_vu0_fmac(RG_VSUB, RG_XYZ, 4, 3, 2, RG_BC_NONE); /* vsub.xyz   $vf4, $vf3, $vf2 */
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
