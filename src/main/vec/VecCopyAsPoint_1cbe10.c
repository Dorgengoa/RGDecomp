#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbe10 asm("vf0");
extern u128 v4_1cbe10 asm("vf4");

void VecCopyAsPoint_1cbe10(u128 *d, u128 *s)
{
    v4_1cbe10 = *s;
    v4_1cbe10 = _vmul(v4_1cbe10, 0x1, vz_1cbe10, vz_1cbe10);
    *d = v4_1cbe10;
}
