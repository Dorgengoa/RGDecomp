#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbaf0 asm("vf0");
extern u128 v4_1cbaf0 asm("vf4");
extern u128 v5_1cbaf0 asm("vf5");
extern u128 v6_1cbaf0 asm("vf6");
extern u128 v7_1cbaf0 asm("vf7");
extern u128 v8_1cbaf0 asm("vf8");
extern u128 v9_1cbaf0 asm("vf9");
extern u128 acc_1cbaf0 asm("ACC");

void VecLerpDir_1cbaf0(u128 *d, u128 *a, u128 *b, f32 t)
{
    v4_1cbaf0 = *a;
    v5_1cbaf0 = *b;
    Vu0ScaleF(a1, t, vf6);
    v7_1cbaf0 = _vaddbc(v7_1cbaf0, 0x8, vz_1cbaf0, vz_1cbaf0, 1);
    v8_1cbaf0 = _vsub(v8_1cbaf0, 0x8, v7_1cbaf0, v6_1cbaf0);
    Vu0MulAccX(xyz, vf4, vf6);
    v9_1cbaf0 = _vmaddbc(v9_1cbaf0, 0xE, acc_1cbaf0, v5_1cbaf0, v8_1cbaf0, 8);
    v9_1cbaf0 = _vsub(v9_1cbaf0, 0x1, vz_1cbaf0, vz_1cbaf0);
    *d = v9_1cbaf0;
}
