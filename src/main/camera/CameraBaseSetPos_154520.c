#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz154520 asm("vf0");
extern u128 v1_154520 asm("vf1");
extern u128 v2_154520 asm("vf2");

/* xyz of *src -> obj+0x40, keeping its w. */
void CameraBaseSetPos_154520(u8 *obj, u128 *src)
{
    v1_154520 = *(volatile u128 *)(obj + 0x40);
    v2_154520 = *(volatile u128 *)src;
    v1_154520 = _vaddbc(v1_154520, 0xE, v2_154520, vz154520, 8);
    *(u128 *)(obj + 0x40) = v1_154520;
}
