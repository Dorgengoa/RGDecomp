#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cb9a0 asm("vf0");
extern u128 v6_1cb9a0 asm("vf6");
extern u128 v7_1cb9a0 asm("vf7");
extern u128 v8_1cb9a0 asm("vf8");

void VecNegate_1cb9a0(u128 *d, u128 *s)
{
    v7_1cb9a0 = *s;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cb9a0 = _vsub(v6_1cb9a0, 0xF, vz_1cb9a0, vz_1cb9a0);
    v8_1cb9a0 = _vsub(v8_1cb9a0, 0xF, v6_1cb9a0, v7_1cb9a0);
    *d = v8_1cb9a0;
}
