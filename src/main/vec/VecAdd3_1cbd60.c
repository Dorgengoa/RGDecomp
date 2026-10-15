#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 v4_1cbd60 asm("vf4");
extern u128 v5_1cbd60 asm("vf5");
extern u128 v6_1cbd60 asm("vf6");

void VecAdd3_1cbd60(u128 *d, u128 *a, u128 *b, u128 *c)
{
    v4_1cbd60 = *a;
    v5_1cbd60 = *b;
    v6_1cbd60 = *c;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbd60 = _vadd(v4_1cbd60, 0xF, v4_1cbd60, v5_1cbd60);
    v4_1cbd60 = _vadd(v4_1cbd60, 0xF, v4_1cbd60, v6_1cbd60);
    *d = v4_1cbd60;
}
