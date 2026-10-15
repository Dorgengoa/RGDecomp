#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 v4_1cbd00 asm("vf4");
extern u128 v5_1cbd00 asm("vf5");

void VecSub_1cbd00(u128 *pd, u128 *pa, u128 *pb)
{
    v5_1cbd00 = *pb;
    v4_1cbd00 = *pa;
    v4_1cbd00 = _vsub(v4_1cbd00, 0xF, v4_1cbd00, v5_1cbd00);
    *pd = v4_1cbd00;
}
