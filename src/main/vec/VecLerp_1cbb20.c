#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbb20 asm("vf0");
extern u128 v4_1cbb20 asm("vf4");
extern u128 v5_1cbb20 asm("vf5");
extern u128 v6_1cbb20 asm("vf6");
extern u128 v7_1cbb20 asm("vf7");
extern u128 v8_1cbb20 asm("vf8");
extern u128 v9_1cbb20 asm("vf9");
extern u128 acc_1cbb20 asm("ACC");

void VecLerp_1cbb20(u128 *d, u128 *a, u128 *b, f32 t)
{
    v4_1cbb20 = *a;
    v5_1cbb20 = *b;
    Vu0ScaleF(a1, t, vf6);
    v7_1cbb20 = _vaddbc(v7_1cbb20, 0x8, vz_1cbb20, vz_1cbb20, 1);
    v8_1cbb20 = _vsub(v8_1cbb20, 0x8, v7_1cbb20, v6_1cbb20);
    Vu0MulAccX(xyzw, vf4, vf6);
    v9_1cbb20 = _vmaddbc(v9_1cbb20, 0xF, acc_1cbb20, v5_1cbb20, v8_1cbb20, 8);
    *d = v9_1cbb20;
}
