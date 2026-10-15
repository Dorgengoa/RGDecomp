#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb780 asm("vf4");
extern u128 v5_1cb780 asm("vf5");
extern u128 v6_1cb780 asm("vf6");
extern u128 v7_1cb780 asm("vf7");
extern u128 v8_1cb780 asm("vf8");
extern u128 v9_1cb780 asm("vf9");
extern u128 vz_1cb780 asm("vf0");
extern u128 acc_1cb780 asm("ACC");

void MatMulPointXyz_1cb780(u128 *d, u128 *m, f32 x, f32 y, f32 z)
{
    f32 v[4] = {x, y, z, 1.0f};
    u128 *p;
    p = (u128 *)(s32)v;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cb780 = *p;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cb780 = m[0];
    v5_1cb780 = m[1];
    v6_1cb780 = m[2];
    v7_1cb780 = m[3];
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf8);
    v9_1cb780 = _vmaddbc(v9_1cb780, 0xF, acc_1cb780, v7_1cb780, vz_1cb780, 1);
    *d = v9_1cb780;
}
