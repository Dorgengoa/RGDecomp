/* rg-override: replaces game/src/main/vec/VecAddScaled_13bdd0.c sha256 0a68fffec0c054681389760a6aabb26071e2b6c85b22ba3b3e04a5c357ac458a
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecAddScaled_13bdd0(void *d, const void *s, f32 t)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(3, (char *)(d)); /* lqc2       $vf3, 0x0($4) */
    rg_vu0_lqc2(4, (char *)(s)); /* lqc2       $vf4, 0x0($5) */
    rg_vu0_mfc1(8, (t)); /* mfc1       $8, $f12 */
    /* nop */
    rg_vu0_qmtc2(8, 5); /* qmtc2.ni   $8, $vf5 */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 3, 0, RG_BC_W); /* vmulaw.xyzw $ACC, $vf3, $vf0w */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 6, 4, 5, RG_BC_X); /* vmaddx.xyzw $vf6, $vf4, $vf5x */
    rg_vu0_sqc2(6, (char *)(d)); /* sqc2      $vf6, 0x0($4) */
}
