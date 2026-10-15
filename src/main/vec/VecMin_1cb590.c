#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 v12_1cb590 asm("vf12");
extern u128 v13_1cb590 asm("vf13");
extern u128 v18_1cb590 asm("vf18");

void VecMin_1cb590(u128 *d, u128 *a, u128 *b)
{
    v12_1cb590 = *a;
    v13_1cb590 = *b;
    v18_1cb590 = _vmini(v18_1cb590, 0xF, v12_1cb590, v13_1cb590);
    *d = v18_1cb590;
}
