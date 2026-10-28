/* rg-override: replaces game/src/main/vec/VecSubInPlace_13e050.c sha256 540cb98c26fd3cd12eda27218a5dcab9502e342c2ac64a9f89e17151ebec91d4
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

void VecSubInPlace_13e050(void *d, const void *b)
{ RG_VU0_FRAME;
    rg_vu0_lqc2(15, (char *)(d)); /* lqc2      vf15, 0x0($4) */
    rg_vu0_lqc2(16, (char *)(b)); /* lqc2      vf16, 0x0($5) */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 15, 15, 16, RG_BC_NONE); /* vsub.xyzw vf15, vf15, vf16 */
    rg_vu0_sqc2(15, (char *)(d)); /* sqc2      vf15, 0x0($4) */
}
