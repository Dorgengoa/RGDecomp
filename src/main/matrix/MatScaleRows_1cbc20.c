#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 v4_1cbc20 asm("vf4");
extern u128 v5_1cbc20 asm("vf5");
extern u128 v6_1cbc20 asm("vf6");
extern u128 v7_1cbc20 asm("vf7");
extern u128 v8_1cbc20 asm("vf8");

void MatScaleRows_1cbc20(u128 *d, u128 *m, u128 *v)
{
    v4_1cbc20 = m[0];
    v5_1cbc20 = m[1];
    v6_1cbc20 = m[2];
    v7_1cbc20 = m[3];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cbc20 = *v;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbc20 = _vmulbc(v4_1cbc20, 0xF, v4_1cbc20, v8_1cbc20, 8);
    v5_1cbc20 = _vmulbc(v5_1cbc20, 0xF, v5_1cbc20, v8_1cbc20, 4);
    v6_1cbc20 = _vmulbc(v6_1cbc20, 0xF, v6_1cbc20, v8_1cbc20, 2);
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    d[0] = v4_1cbc20;
    d[1] = v5_1cbc20;
    d[2] = v6_1cbc20;
    d[3] = v7_1cbc20;
}
