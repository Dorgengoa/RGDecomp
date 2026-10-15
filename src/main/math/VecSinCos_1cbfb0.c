#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbfb0 asm("vf0");
extern u128 v4_1cbfb0 asm("vf4");
extern u128 v5_1cbfb0 asm("vf5");
extern u128 v6_1cbfb0 asm("vf6");
extern u128 v7_1cbfb0 asm("vf7");
extern u128 v8_1cbfb0 asm("vf8");
extern u128 v9_1cbfb0 asm("vf9");
extern u128 v10_1cbfb0 asm("vf10");
extern u128 v11_1cbfb0 asm("vf11");
extern u128 v12_1cbfb0 asm("vf12");
extern u128 v13_1cbfb0 asm("vf13");
extern u128 v14_1cbfb0 asm("vf14");
extern u128 acc_1cbfb0 asm("ACC");
extern u128 D_0044B2C0[3];

void VecSinCos_1cbfb0(u128 *d, u128 *s)
{
    u128 *k;

    k = (u128 *)(s32)D_0044B2C0;

    if (k) {
        k = (u128 *)(s32)(u32)k;
    }
    v4_1cbfb0 = *s;
    v5_1cbfb0 = k[0];
    v6_1cbfb0 = k[1];
    v7_1cbfb0 = k[2];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbfb0 = _vmulbc(v4_1cbfb0, 0x1, vz_1cbfb0, v4_1cbfb0, 2);
    v4_1cbfb0 = _vaddbc(v4_1cbfb0, 0x4, vz_1cbfb0, v4_1cbfb0, 8);
    v4_1cbfb0 = _vsubbc(v4_1cbfb0, 0xA, v4_1cbfb0, v5_1cbfb0, 8);
    v4_1cbfb0 = _vabs(v4_1cbfb0, 0xF, v4_1cbfb0);
    v8_1cbfb0 = _vmaxbc(v8_1cbfb0, 0xF, vz_1cbfb0, vz_1cbfb0, 1);
    Vu0SinCosAccR();
    v4_1cbfb0 = _vmsubbc(v4_1cbfb0, 0xF, acc_1cbfb0, v8_1cbfb0, v6_1cbfb0, 8);
    v4_1cbfb0 = _vabs(v4_1cbfb0, 0xF, v4_1cbfb0);
    v4_1cbfb0 = _vsubbc(v4_1cbfb0, 0xF, v4_1cbfb0, v6_1cbfb0, 4);
    v12_1cbfb0 = _vmul(v12_1cbfb0, 0xF, v4_1cbfb0, v4_1cbfb0);
    v11_1cbfb0 = _vmulbc(v11_1cbfb0, 0xF, v4_1cbfb0, v7_1cbfb0, 8);
    v9_1cbfb0 = _vmulbc(v9_1cbfb0, 0xF, v4_1cbfb0, v7_1cbfb0, 4);
    v10_1cbfb0 = _vmulbc(v10_1cbfb0, 0xF, v4_1cbfb0, v7_1cbfb0, 2);
    v13_1cbfb0 = _vmul(v13_1cbfb0, 0xF, v12_1cbfb0, v12_1cbfb0);
    v11_1cbfb0 = _vmul(v11_1cbfb0, 0xF, v11_1cbfb0, v12_1cbfb0);
    Vu0SinCosAccP0();
    v9_1cbfb0 = _vmulbc(v9_1cbfb0, 0xF, v4_1cbfb0, v7_1cbfb0, 1);
    v14_1cbfb0 = _vmul(v14_1cbfb0, 0xF, v13_1cbfb0, v13_1cbfb0);
    Vu0SinCosAccP1();
    v4_1cbfb0 = _vmadd(v4_1cbfb0, 0xF, acc_1cbfb0, v9_1cbfb0, v14_1cbfb0);
    *d = v4_1cbfb0;
}
