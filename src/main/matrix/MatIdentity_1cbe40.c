#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz1cbe40 asm("vf0");
extern u128 v1_1cbe40 asm("vf1");
extern u128 v2_1cbe40 asm("vf2");
extern u128 v3_1cbe40 asm("vf3");

/* Unit matrix: rotate vf0 (0,0,0,1) through vf1..vf3, store rows 3..0. */
void MatIdentity_1cbe40(u128 *m)
{
    v1_1cbe40 = _vmr32(v1_1cbe40, 0xF, vz1cbe40);
    v2_1cbe40 = _vmr32(v2_1cbe40, 0xF, v1_1cbe40);
    v3_1cbe40 = _vmr32(v3_1cbe40, 0xF, v2_1cbe40);
    if (m) {
        m = (u128 *)(s32)(u32)m;
    }
    m[3] = vz1cbe40;
    m[2] = v1_1cbe40;
    m[1] = v2_1cbe40;
    m[0] = v3_1cbe40;
}
