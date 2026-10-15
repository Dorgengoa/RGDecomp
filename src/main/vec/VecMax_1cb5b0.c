#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 v12_1cb5b0 asm("vf12");
extern u128 v13_1cb5b0 asm("vf13");
extern u128 v18_1cb5b0 asm("vf18");

void VecMax_1cb5b0(u128 *d, u128 *a, u128 *b)
{
    v12_1cb5b0 = *a;
    v13_1cb5b0 = *b;
    v18_1cb5b0 = _vmax(v18_1cb5b0, 0xF, v12_1cb5b0, v13_1cb5b0);
    *d = v18_1cb5b0;
}
