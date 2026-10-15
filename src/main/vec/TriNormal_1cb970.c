#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb970 asm("vf4");
extern u128 v5_1cb970 asm("vf5");
extern u128 v6_1cb970 asm("vf6");
extern u128 v7_1cb970 asm("vf7");
extern u128 acc_1cb970 asm("ACC");

void TriNormal_1cb970(u128 *d, u128 *a, u128 *b, u128 *c)
{
    v6_1cb970 = *c;
    v5_1cb970 = *b;
    v4_1cb970 = *a;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cb970 = _vsub(v6_1cb970, 0xF, v6_1cb970, v5_1cb970);
    v5_1cb970 = _vsub(v5_1cb970, 0xF, v5_1cb970, v4_1cb970);
    Vu0OuterProductAcc(vf5, vf6);
    v7_1cb970 = _vopmsub(v7_1cb970, acc_1cb970, v6_1cb970, v5_1cb970);
    v7_1cb970 = _vsub(v7_1cb970, 0x1, v7_1cb970, v7_1cb970);
    *d = v7_1cb970;
}
