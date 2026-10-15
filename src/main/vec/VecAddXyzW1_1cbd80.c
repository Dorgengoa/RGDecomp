#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbd80 asm("vf0");
extern u128 v4_1cbd80 asm("vf4");
extern u128 v5_1cbd80 asm("vf5");

void VecAddXyzW1_1cbd80(u128 *d, u128 *a, u128 *b)
{
    v4_1cbd80 = *a;
    v5_1cbd80 = *b;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbd80 = _vmul(v4_1cbd80, 0x1, vz_1cbd80, vz_1cbd80);
    v4_1cbd80 = _vadd(v4_1cbd80, 0xE, v4_1cbd80, v5_1cbd80);
    *d = v4_1cbd80;
}
