#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vf4_1cb4c0 asm("vf4");

/* |v.xyz| */
f32 VecLength_1cb4c0(void *v)
{
    f32 r;
    vf4_1cb4c0 = *(u128 *)v;
    vf4_1cb4c0 = _vmul(vf4_1cb4c0, 0xE, vf4_1cb4c0, vf4_1cb4c0);
    vf4_1cb4c0 = _vaddbc(vf4_1cb4c0, 0x8, vf4_1cb4c0, vf4_1cb4c0, 4);
    vf4_1cb4c0 = _vaddbc(vf4_1cb4c0, 0x8, vf4_1cb4c0, vf4_1cb4c0, 2);
    Vu0Length(r, x);
    return r;
}
