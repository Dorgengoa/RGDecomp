#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb600 asm("vf4");
extern u128 v5_1cb600 asm("vf5");
extern u128 v6_1cb600 asm("vf6");
extern u128 v7_1cb600 asm("vf7");
extern u128 v8_1cb600 asm("vf8");
extern u128 acc_1cb600 asm("ACC");

#pragma optimization_level 1
#pragma schedule on
#pragma opt_common_subs on

f32 TriNormalDot_1cb600(u128 *a, u128 *b, u128 *c, u128 *n)
{
    f32 r;

    v7_1cb600 = *(volatile u128 *)n;
    v6_1cb600 = *(volatile u128 *)c;
    v5_1cb600 = *(volatile u128 *)b;
    v4_1cb600 = *(volatile u128 *)a;
    if (c) { a = (u128 *)(s32)(u32)a; }
    _vsub(v6_1cb600, 0xF, v6_1cb600, v5_1cb600);
    _vsub(v5_1cb600, 0xF, v5_1cb600, v4_1cb600);
    Vu0OuterProductAcc(vf5, vf6);
    _vopmsub(v8_1cb600, acc_1cb600, v6_1cb600, v5_1cb600);
    _vmul(v8_1cb600, 0xE, v8_1cb600, v7_1cb600);
    _vaddbc(v8_1cb600, 0x8, v8_1cb600, v8_1cb600, 4);
    _vaddbc(v8_1cb600, 0x8, v8_1cb600, v8_1cb600, 2);
    b = *(u128 **)&v8_1cb600;
    r = *(f32 *)&v8_1cb600;
    if (a) { r = -(-r); }
    if (b) { r = -(-r); }
    return r;
}
