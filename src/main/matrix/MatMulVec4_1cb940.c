#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb940 asm("vf4");
extern u128 v5_1cb940 asm("vf5");
extern u128 v6_1cb940 asm("vf6");
extern u128 v7_1cb940 asm("vf7");
extern u128 v8_1cb940 asm("vf8");
extern u128 v9_1cb940 asm("vf9");
extern u128 acc_1cb940 asm("ACC");

void MatMulVec4_1cb940(u128 *d, u128 *m, u128 *v)
{
    v8_1cb940 = *v;
    v4_1cb940 = m[0];
    v5_1cb940 = m[1];
    v6_1cb940 = m[2];
    v7_1cb940 = m[3];
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf8);
    v9_1cb940 = _vmaddbc(v9_1cb940, 0xF, acc_1cb940, v7_1cb940, v8_1cb940, 1);
    *d = v9_1cb940;
}
