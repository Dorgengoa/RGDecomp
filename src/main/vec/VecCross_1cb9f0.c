#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb9f0 asm("vf4");
extern u128 v5_1cb9f0 asm("vf5");
extern u128 v6_1cb9f0 asm("vf6");
extern u128 acc_1cb9f0 asm("ACC");

void VecCross_1cb9f0(u128 *d, u128 *a, u128 *b)
{
    v4_1cb9f0 = *a;
    v5_1cb9f0 = *b;
    Vu0OuterProductAcc(vf4, vf5);
    v6_1cb9f0 = _vopmsub(v6_1cb9f0, acc_1cb9f0, v5_1cb9f0, v4_1cb9f0);
    v6_1cb9f0 = _vsub(v6_1cb9f0, 0x1, v6_1cb9f0, v6_1cb9f0);
    *d = v6_1cb9f0;
}
