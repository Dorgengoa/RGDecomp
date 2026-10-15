#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbac0 asm("vf0");
extern u128 v4_1cbac0 asm("vf4");
extern u128 v5_1cbac0 asm("vf5");
extern u128 v6_1cbac0 asm("vf6");
extern u128 v7_1cbac0 asm("vf7");
extern u128 v8_1cbac0 asm("vf8");
extern u128 v9_1cbac0 asm("vf9");
extern u128 acc_1cbac0 asm("ACC");

void VecLerpPoint_1cbac0(u128 *d, u128 *a, u128 *b, f32 t)
{
    v4_1cbac0 = *a;
    v5_1cbac0 = *b;
    Vu0ScaleF(a1, t, vf6);
    v7_1cbac0 = _vaddbc(v7_1cbac0, 0x8, vz_1cbac0, vz_1cbac0, 1);
    v8_1cbac0 = _vsub(v8_1cbac0, 0x8, v7_1cbac0, v6_1cbac0);
    Vu0MulAccX(xyz, vf4, vf6);
    v9_1cbac0 = _vmaddbc(v9_1cbac0, 0xE, acc_1cbac0, v5_1cbac0, v8_1cbac0, 8);
    v9_1cbac0 = _vmul(v9_1cbac0, 0x1, vz_1cbac0, vz_1cbac0);
    *d = v9_1cbac0;
}
