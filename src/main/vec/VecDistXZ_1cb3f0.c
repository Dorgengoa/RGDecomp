#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vf4_1cb3f0 asm("vf4");
extern u128 vf5_1cb3f0 asm("vf5");

/* xz distance |a - b| */
f32 VecDistXZ_1cb3f0(void *a, void *b)
{
    f32 r;
    vf4_1cb3f0 = *(u128 *)a;
    vf5_1cb3f0 = *(u128 *)b;
    vf4_1cb3f0 = _vsub(vf4_1cb3f0, 0xA, vf4_1cb3f0, vf5_1cb3f0);
    vf4_1cb3f0 = _vmul(vf4_1cb3f0, 0xA, vf4_1cb3f0, vf4_1cb3f0);
    vf4_1cb3f0 = _vaddbc(vf4_1cb3f0, 0x2, vf4_1cb3f0, vf4_1cb3f0, 8);
    Vu0Length(r, z);
    return r;
}
