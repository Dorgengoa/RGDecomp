#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz142e40 asm("vf0");
extern u128 v1_142e40 asm("vf1");
extern u128 v2_142e40 asm("vf2");

/* xyz of obj+0x40 -> *dst, keeping dst's w. */
void CameraBaseGetPos_142e40(u8 *obj, u128 *dst)
{
    v1_142e40 = *(volatile u128 *)dst;
    v2_142e40 = *(volatile u128 *)(obj + 0x40);
    v1_142e40 = _vaddbc(v1_142e40, 0xE, v2_142e40, vz142e40, 8);
    *dst = v1_142e40;
}
