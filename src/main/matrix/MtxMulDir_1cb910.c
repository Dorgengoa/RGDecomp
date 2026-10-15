#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb910 asm("vf4");
extern u128 v5_1cb910 asm("vf5");
extern u128 v6_1cb910 asm("vf6");
extern u128 v8_1cb910 asm("vf8");
extern u128 v9_1cb910 asm("vf9");
extern u128 acc_1cb910 asm("ACC");

void MtxMulDir_1cb910(u128 *d, u128 *m, u128 *v)
{
    v8_1cb910 = *v;
    v4_1cb910 = m[0];
    v5_1cb910 = m[1];
    v6_1cb910 = m[2];
    Vu0ApplyMatrix3Acc(xyzw, vf4, vf5, vf8);
    v9_1cb910 = _vmaddbc(v9_1cb910, 0xF, acc_1cb910, v6_1cb910, v8_1cb910, 2);
    *d = v9_1cb910;
}
