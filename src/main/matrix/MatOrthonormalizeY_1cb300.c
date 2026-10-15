#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 vz_1cb300 asm("vf0");
extern u128 v4_1cb300 asm("vf4");
extern u128 v5_1cb300 asm("vf5");
extern u128 v6_1cb300 asm("vf6");
extern u128 v7_1cb300 asm("vf7");
extern u128 v8_1cb300 asm("vf8");
extern u128 acc_1cb300 asm("ACC");
extern float q_1cb300 asm("Q");

void MatOrthonormalizeY_1cb300(u128 *d, u128 *m)
{
    v5_1cb300 = m[1];
    v6_1cb300 = m[2];
    v7_1cb300 = m[3];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cb300 = _vmul(v8_1cb300, 0xE, v5_1cb300, v5_1cb300);
    v8_1cb300 = _vaddbc(v8_1cb300, 0x8, v8_1cb300, v8_1cb300, 4);
    v8_1cb300 = _vaddbc(v8_1cb300, 0x8, v8_1cb300, v8_1cb300, 2);
    Vu0OrthoNormalSqrt(vf4);
    v8_1cb300 = _vaddf(v8_1cb300, 0x8, vz_1cb300, q_1cb300);
    v5_1cb300 = _vsub(v5_1cb300, 0x1, vz_1cb300, vz_1cb300);
    q_1cb300 = _vdiv(q_1cb300, vz_1cb300, 1, v8_1cb300, 8);
    v5_1cb300 = _vmulf(v5_1cb300, 0xE, v5_1cb300, q_1cb300);
    Vu0OuterProductAcc(vf5, vf6);
    v4_1cb300 = _vopmsub(v4_1cb300, acc_1cb300, v6_1cb300, v5_1cb300);
    v8_1cb300 = _vmul(v8_1cb300, 0xE, v4_1cb300, v4_1cb300);
    v8_1cb300 = _vaddbc(v8_1cb300, 0x8, v8_1cb300, v8_1cb300, 4);
    v8_1cb300 = _vaddbc(v8_1cb300, 0x8, v8_1cb300, v8_1cb300, 2);
    Vu0OrthoNormalSqrt(vf6);
    v8_1cb300 = _vaddf(v8_1cb300, 0x8, vz_1cb300, q_1cb300);
    v7_1cb300 = _vmul(v7_1cb300, 0x1, vz_1cb300, vz_1cb300);
    q_1cb300 = _vdiv(q_1cb300, vz_1cb300, 1, v8_1cb300, 8);
    v4_1cb300 = _vmulf(v4_1cb300, 0xE, v4_1cb300, q_1cb300);
    Vu0OuterProductAcc(vf4, vf5);
    v6_1cb300 = _vopmsub(v6_1cb300, acc_1cb300, v5_1cb300, v4_1cb300);
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    d[0] = v4_1cb300;
    d[1] = v5_1cb300;
    d[2] = v6_1cb300;
    d[3] = v7_1cb300;
}
