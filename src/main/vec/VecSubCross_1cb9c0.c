#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb9c0 asm("vf4");
extern u128 v5_1cb9c0 asm("vf5");
extern u128 v6_1cb9c0 asm("vf6");
extern u128 v7_1cb9c0 asm("vf7");
extern u128 acc_1cb9c0 asm("ACC");

void VecSubCross_1cb9c0(u128 *d, u128 *a, u128 *b, u128 *c)
{
    v4_1cb9c0 = *a;
    v5_1cb9c0 = *b;
    v6_1cb9c0 = *c;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cb9c0 = _vsub(v4_1cb9c0, 0xF, v4_1cb9c0, v5_1cb9c0);
    Vu0OuterProductAcc(vf4, vf6);
    v7_1cb9c0 = _vopmsub(v7_1cb9c0, acc_1cb9c0, v6_1cb9c0, v4_1cb9c0);
    v7_1cb9c0 = _vsub(v7_1cb9c0, 0x1, v7_1cb9c0, v7_1cb9c0);
    *d = v7_1cb9c0;
}
