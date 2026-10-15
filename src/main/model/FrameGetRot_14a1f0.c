#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz14a1f0 asm("vf0");
extern u128 v1_14a1f0 asm("vf1");
extern u128 v2_14a1f0 asm("vf2");

/* dst.xyz = obj->+0x18 vector's xyz (dst.w kept), or clear dst when null. */
void FrameGetRot_14a1f0(u8 *obj, u128 *dst)
{
    u128 *src = *(u128 **)(obj + 0x18);
    if (src != 0) {
        v1_14a1f0 = *(volatile u128 *)dst;
        v2_14a1f0 = *(volatile u128 *)src;
        v1_14a1f0 = _vaddbc(v1_14a1f0, 0xE, v2_14a1f0, vz14a1f0, 8);
        *dst = v1_14a1f0;
    } else {
        *dst = 0;
    }
}
