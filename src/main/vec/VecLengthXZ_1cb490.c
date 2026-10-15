#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vf4_1cb490 asm("vf4");

/* sqrt(v.x*v.x + v.z*v.z) */
f32 VecLengthXZ_1cb490(void *v)
{
    f32 r;
    vf4_1cb490 = *(u128 *)v;
    vf4_1cb490 = _vmul(vf4_1cb490, 0xA, vf4_1cb490, vf4_1cb490);
    vf4_1cb490 = _vaddbc(vf4_1cb490, 0x2, vf4_1cb490, vf4_1cb490, 8);
    Vu0Length(r, z);
    return r;
}
