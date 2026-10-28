/* rg-override: replaces game/src/main/matrix/MatZero_13d2c0.c sha256 1c3e305de17964d26908fe4a3b36e138b78e25528f7ab2ab9a73dc4df7303ffc
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void MatZero_13d2c0(void *m)
{ RG_VU0_FRAME;
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 1, 1, 1, RG_BC_NONE); /* vsub.xyzw  $vf1, $vf1, $vf1 */
    rg_vu0_sqc2(1, (char *)(m) + 0x30); /* sqc2       $vf1, 0x30($4) */
    rg_vu0_sqc2(1, (char *)(m) + 0x20); /* sqc2       $vf1, 0x20($4) */
    rg_vu0_sqc2(1, (char *)(m) + 0x10); /* sqc2       $vf1, 0x10($4) */
    rg_vu0_sqc2(1, (char *)(m)); /* sqc2      $vf1, 0x0($4) */
}
