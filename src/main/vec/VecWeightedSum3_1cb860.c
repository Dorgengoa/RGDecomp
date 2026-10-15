#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb860 asm("vf4");
extern u128 v5_1cb860 asm("vf5");
extern u128 v6_1cb860 asm("vf6");
extern u128 v9_1cb860 asm("vf9");
extern u128 v10_1cb860 asm("vf10");
extern u128 acc_1cb860 asm("ACC");

void VecWeightedSum3_1cb860(u128 *d, u128 *a, u128 *b, u128 *c, f32 wa, f32 wb, f32 wc)
{
    Vu0BlendVector3F(wa, wb, wc);
    v4_1cb860 = *a;
    v5_1cb860 = *b;
    v6_1cb860 = *c;
    Vu0BlendVector3Acc();
    v9_1cb860 = _vmaddbc(v9_1cb860, 0xF, acc_1cb860, v6_1cb860, v10_1cb860, 8);
    *d = v9_1cb860;
}
