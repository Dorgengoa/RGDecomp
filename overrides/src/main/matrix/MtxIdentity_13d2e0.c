/* rg-override: replaces game/src/main/matrix/MtxIdentity_13d2e0.c sha256 3b1bc34ec890aad9ceb4b94397524c519305bb8e33af1415be0f35a3a82df435
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void MtxIdentity_13d2e0(void *m)
{ RG_VU0_FRAME;
    rg_vu0_mr32(RG_XYZW, 1, 0); /* vmr32.xyzw $vf1, $vf0 */
    rg_vu0_mr32(RG_XYZW, 2, 1); /* vmr32.xyzw $vf2, $vf1 */
    rg_vu0_mr32(RG_XYZW, 3, 2); /* vmr32.xyzw $vf3, $vf2 */
    rg_vu0_sqc2(0, (char *)(m) + 0x30); /* sqc2       $vf0, 0x30($4) */
    rg_vu0_sqc2(1, (char *)(m) + 0x20); /* sqc2       $vf1, 0x20($4) */
    rg_vu0_sqc2(2, (char *)(m) + 0x10); /* sqc2       $vf2, 0x10($4) */
    rg_vu0_sqc2(3, (char *)(m)); /* sqc2      $vf3, 0x0($4) */
}
