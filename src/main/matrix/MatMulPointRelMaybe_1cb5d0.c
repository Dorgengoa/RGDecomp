#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb5d0 asm("vf4");
extern u128 v5_1cb5d0 asm("vf5");
extern u128 v6_1cb5d0 asm("vf6");
extern u128 v7_1cb5d0 asm("vf7");
extern u128 v8_1cb5d0 asm("vf8");
extern u128 v9_1cb5d0 asm("vf9");
extern u128 vz_1cb5d0 asm("vf0");
extern u128 acc_1cb5d0 asm("ACC");

void MatMulPointRelMaybe_1cb5d0(u128 *d, u128 *a, u128 *m, u128 *p)
{
    v8_1cb5d0 = *p;
    v4_1cb5d0 = m[0];
    v5_1cb5d0 = m[1];
    v6_1cb5d0 = m[2];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v7_1cb5d0 = a[3];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cb5d0 = _vsub(v8_1cb5d0, 0xE, v8_1cb5d0, v7_1cb5d0);
    Vu0ApplyMatrix3Acc(xyz, vf4, vf5, vf8);
    v9_1cb5d0 = _vmaddbc(v9_1cb5d0, 0xE, acc_1cb5d0, v6_1cb5d0, v8_1cb5d0, 2);
    v9_1cb5d0 = _vaddbc(v9_1cb5d0, 0x1, vz_1cb5d0, vz_1cb5d0, 8);
    *d = v9_1cb5d0;
}
