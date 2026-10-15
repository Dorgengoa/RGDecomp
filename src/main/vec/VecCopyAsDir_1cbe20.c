#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz1cbe20 asm("vf0");
extern u128 v4_1cbe20 asm("vf4");

/* Copy a vector with w forced to 0.0f (vf0.w - vf0.w). */
void VecCopyAsDir_1cbe20(u128 *dst, u128 *src)
{
    v4_1cbe20 = *src;
    v4_1cbe20 = _vsub(v4_1cbe20, 0x1, vz1cbe20, vz1cbe20);
    *dst = v4_1cbe20;
}
