#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 v12_1cb570 asm("vf12");
extern u128 v13_1cb570 asm("vf13");
extern u128 v17_1cb570 asm("vf17");
extern u128 v18_1cb570 asm("vf18");

void VecMinMax_1cb570(u128 *mx, u128 *mn, u128 *a, u128 *b)
{
    v12_1cb570 = *a;
    v13_1cb570 = *b;
    v17_1cb570 = _vmax(v17_1cb570, 0xF, v12_1cb570, v13_1cb570);
    v18_1cb570 = _vmini(v18_1cb570, 0xF, v12_1cb570, v13_1cb570);
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (mx) {
        mx = (u128 *)(s32)(u32)mx;
    }
    *mx = v17_1cb570;
    *mn = v18_1cb570;
}
