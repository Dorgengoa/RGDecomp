#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 v12_1cb540 asm("vf12");
extern u128 v13_1cb540 asm("vf13");
extern u128 v14_1cb540 asm("vf14");
extern u128 v17_1cb540 asm("vf17");
extern u128 v18_1cb540 asm("vf18");

void TriCalcBounds_1cb540(u128 *mx, u128 *mn, u128 *a, u128 *b, u128 *c)
{
    v12_1cb540 = *a;
    v13_1cb540 = *b;
    v14_1cb540 = *c;
    if (mx) {
        mx = (u128 *)(s32)(u32)mx;
    }
    v17_1cb540 = _vmax(v17_1cb540, 0xF, v12_1cb540, v13_1cb540);
    v17_1cb540 = _vmax(v17_1cb540, 0xF, v17_1cb540, v14_1cb540);
    if (mx) {
        mx = (u128 *)(s32)(u32)mx;
    }
    v18_1cb540 = _vmini(v18_1cb540, 0xF, v12_1cb540, v13_1cb540);
    v18_1cb540 = _vmini(v18_1cb540, 0xF, v18_1cb540, v14_1cb540);
    if (mx) {
        mx = (u128 *)(s32)(u32)mx;
    }
    *mx = v17_1cb540;
    *mn = v18_1cb540;
}
