#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbda0 asm("vf0");
extern u128 v4_1cbda0 asm("vf4");
extern u128 v5_1cbda0 asm("vf5");

void VecAddXyzW0_1cbda0(u128 *d, u128 *a, u128 *b)
{
    v4_1cbda0 = *a;
    v5_1cbda0 = *b;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbda0 = _vsub(v4_1cbda0, 0x1, vz_1cbda0, vz_1cbda0);
    v4_1cbda0 = _vadd(v4_1cbda0, 0xE, v4_1cbda0, v5_1cbda0);
    *d = v4_1cbda0;
}
