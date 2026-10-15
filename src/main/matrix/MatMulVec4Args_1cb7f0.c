#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb7f0 asm("vf4");
extern u128 v5_1cb7f0 asm("vf5");
extern u128 v6_1cb7f0 asm("vf6");
extern u128 v7_1cb7f0 asm("vf7");
extern u128 v8_1cb7f0 asm("vf8");
extern u128 v9_1cb7f0 asm("vf9");
extern u128 acc_1cb7f0 asm("ACC");

void MatMulVec4Args_1cb7f0(u128 *d, u128 *m, f32 x, f32 y, f32 z, f32 w)
{
    f32 v[4] __attribute__((aligned(16))) = {0};
    u128 *p;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
    p = (u128 *)(s32)v;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cb7f0 = *p;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cb7f0 = m[0];
    v5_1cb7f0 = m[1];
    v6_1cb7f0 = m[2];
    v7_1cb7f0 = m[3];
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf8);
    v9_1cb7f0 = _vmaddbc(v9_1cb7f0, 0xF, acc_1cb7f0, v7_1cb7f0, v8_1cb7f0, 1);
    *d = v9_1cb7f0;
}
