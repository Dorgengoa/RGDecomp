#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb8b0 asm("vf4");
extern u128 v5_1cb8b0 asm("vf5");
extern u128 v9_1cb8b0 asm("vf9");
extern u128 acc_1cb8b0 asm("ACC");

void VecLinearCombine_1cb8b0(u128 *d, u128 *a, u128 *b, f32 s, f32 t)
{
    Vu0BlendVectorF(s, t);
    v4_1cb8b0 = *a;
    v5_1cb8b0 = *b;
    Vu0BlendVectorAcc();
    v9_1cb8b0 = _vmaddbc(v9_1cb8b0, 0xF, acc_1cb8b0, v5_1cb8b0, v9_1cb8b0, 8);
    *d = v9_1cb8b0;
}
