#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb8e0 asm("vf4");
extern u128 v5_1cb8e0 asm("vf5");
extern u128 v6_1cb8e0 asm("vf6");
extern u128 v7_1cb8e0 asm("vf7");
extern u128 v8_1cb8e0 asm("vf8");
extern u128 v9_1cb8e0 asm("vf9");
extern u128 vz_1cb8e0 asm("vf0");
extern u128 acc_1cb8e0 asm("ACC");

void MatMulPoint_1cb8e0(u128 *d, u128 *m, u128 *v)
{
    v8_1cb8e0 = *v;
    v4_1cb8e0 = m[0];
    v5_1cb8e0 = m[1];
    v6_1cb8e0 = m[2];
    v7_1cb8e0 = m[3];
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf8);
    v9_1cb8e0 = _vmaddbc(v9_1cb8e0, 0xF, acc_1cb8e0, v7_1cb8e0, vz_1cb8e0, 1);
    *d = v9_1cb8e0;
}
