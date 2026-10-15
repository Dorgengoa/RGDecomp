#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbd40 asm("vf0");
extern u128 v4_1cbd40 asm("vf4");
extern u128 v5_1cbd40 asm("vf5");
extern u128 v6_1cbd40 asm("vf6");

void VecAddMaxZero_1cbd40(u128 *d, u128 *a, u128 *b)
{
    v5_1cbd40 = *b;
    v4_1cbd40 = *a;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cbd40 = _vsub(v6_1cbd40, 0xF, vz_1cbd40, vz_1cbd40);
    v5_1cbd40 = _vmax(v5_1cbd40, 0xF, v5_1cbd40, v6_1cbd40);
    v4_1cbd40 = _vadd(v4_1cbd40, 0xF, v4_1cbd40, v5_1cbd40);
    *d = v4_1cbd40;
}
