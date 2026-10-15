#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb700 asm("vf4");
extern u128 v5_1cb700 asm("vf5");
extern u128 v6_1cb700 asm("vf6");
extern u128 v7_1cb700 asm("vf7");
extern u128 v8_1cb700 asm("vf8");
extern u128 v9_1cb700 asm("vf9");
extern u128 v10_1cb700 asm("vf10");
extern u128 v11_1cb700 asm("vf11");
extern u128 v12_1cb700 asm("vf12");
extern u128 v13_1cb700 asm("vf13");
extern u128 v14_1cb700 asm("vf14");
extern u128 v15_1cb700 asm("vf15");
extern u128 acc_1cb700 asm("ACC");

void MatMul_1cb700(u128 *d, u128 *a, u128 *b)
{
    v4_1cb700 = a[0];
    v5_1cb700 = a[1];
    v6_1cb700 = a[2];
    v7_1cb700 = a[3];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cb700 = b[0];
    v9_1cb700 = b[1];
    v10_1cb700 = b[2];
    v11_1cb700 = b[3];
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf8);
    v12_1cb700 = _vmaddbc(v12_1cb700, 0xF, acc_1cb700, v7_1cb700, v8_1cb700, 1);
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf9);
    v13_1cb700 = _vmaddbc(v13_1cb700, 0xF, acc_1cb700, v7_1cb700, v9_1cb700, 1);
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf10);
    v14_1cb700 = _vmaddbc(v14_1cb700, 0xF, acc_1cb700, v7_1cb700, v10_1cb700, 1);
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf11);
    v15_1cb700 = _vmaddbc(v15_1cb700, 0xF, acc_1cb700, v7_1cb700, v11_1cb700, 1);
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    d[0] = v12_1cb700;
    d[1] = v13_1cb700;
    d[2] = v14_1cb700;
    d[3] = v15_1cb700;
}
