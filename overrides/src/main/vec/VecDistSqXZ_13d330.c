/* rg-override: replaces game/src/main/vec/VecDistSqXZ_13d330.c sha256 8eba9b7c1a8bfcc27370c7fdc8deb336efd4b81c64a56a98b4a6976f6bb7bf7a
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

f32 VecDistSqXZ_13d330(const void *a, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(2, (char *)(a)); /* lqc2       $vf2, 0x0($4) */
    rg_vu0_lqc2(3, (char *)(b)); /* lqc2       $vf3, 0x0($5) */
    rg_vu0_fmac(RG_VSUB, RG_XYZ, 4, 3, 2, RG_BC_NONE); /* vsub.xyz   $vf4, $vf3, $vf2 */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 4, 4, 4, RG_BC_NONE); /* vmul.xyz   $vf4, $vf4, $vf4 */
    rg_vu0_mr32(RG_XY, 5, 4); /* vmr32.xy   $vf5, $vf4 */
    rg_vu0_mr32(RG_X, 6, 5); /* vmr32.x    $vf6, $vf5 */
    rg_vu0_fmac(RG_VADD, RG_X, 7, 4, 6, RG_BC_NONE); /* vadd.x     $vf7, $vf4, $vf6 */
    /* qmfc2.ni   $2, $vf7 */
    /* mtc1       $2, $f0 */
    /* nop */
    return rg_vu0_getf(7, 0); /* qmfc2 $2, vf7; mtc1 $2, $f0 (lane x) */
}
