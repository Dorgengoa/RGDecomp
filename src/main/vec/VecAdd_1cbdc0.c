#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 v4_1cbdc0 asm("vf4");
extern u128 v5_1cbdc0 asm("vf5");

void VecAdd_1cbdc0(u128 *pd, u128 *pa, u128 *pb)
{
    v5_1cbdc0 = *pb;
    v4_1cbdc0 = *pa;
    v4_1cbdc0 = _vadd(v4_1cbdc0, 0xF, v4_1cbdc0, v5_1cbdc0);
    *pd = v4_1cbdc0;
}
