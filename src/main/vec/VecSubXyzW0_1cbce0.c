#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbce0 asm("vf0");
extern u128 v4_1cbce0 asm("vf4");
extern u128 v5_1cbce0 asm("vf5");

void VecSubXyzW0_1cbce0(u128 *d, u128 *a, u128 *b)
{
    v5_1cbce0 = *b;
    v4_1cbce0 = *a;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbce0 = _vsub(v4_1cbce0, 0x1, vz_1cbce0, vz_1cbce0);
    v4_1cbce0 = _vsub(v4_1cbce0, 0xE, v4_1cbce0, v5_1cbce0);
    *d = v4_1cbce0;
}
