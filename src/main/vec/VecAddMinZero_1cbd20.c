#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbd20 asm("vf0");
extern u128 v4_1cbd20 asm("vf4");
extern u128 v5_1cbd20 asm("vf5");
extern u128 v6_1cbd20 asm("vf6");

void VecAddMinZero_1cbd20(u128 *d, u128 *a, u128 *b)
{
    v5_1cbd20 = *b;
    v4_1cbd20 = *a;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cbd20 = _vsub(v6_1cbd20, 0xF, vz_1cbd20, vz_1cbd20);
    v5_1cbd20 = _vmini(v5_1cbd20, 0xF, v5_1cbd20, v6_1cbd20);
    v4_1cbd20 = _vadd(v4_1cbd20, 0xF, v4_1cbd20, v5_1cbd20);
    *d = v4_1cbd20;
}
