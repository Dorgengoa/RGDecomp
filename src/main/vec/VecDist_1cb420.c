#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vf4_1cb420 asm("vf4");
extern u128 vf5_1cb420 asm("vf5");

/* xyz distance |a - b| */
f32 VecDist_1cb420(void *a, void *b)
{
    f32 r;
    vf4_1cb420 = *(u128 *)a;
    vf5_1cb420 = *(u128 *)b;
    vf4_1cb420 = _vsub(vf4_1cb420, 0xE, vf4_1cb420, vf5_1cb420);
    vf4_1cb420 = _vmul(vf4_1cb420, 0xE, vf4_1cb420, vf4_1cb420);
    vf4_1cb420 = _vaddbc(vf4_1cb420, 0x8, vf4_1cb420, vf4_1cb420, 4);
    vf4_1cb420 = _vaddbc(vf4_1cb420, 0x8, vf4_1cb420, vf4_1cb420, 2);
    Vu0Length(r, x);
    return r;
}
