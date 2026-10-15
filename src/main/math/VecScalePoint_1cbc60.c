#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbc60 asm("vf0");
extern u128 v4_1cbc60 asm("vf4");
extern u128 v5_1cbc60 asm("vf5");
extern u128 v6_1cbc60 asm("vf6");

/* d.xyz = a.xyz * s, d.w = 1 */
void VecScalePoint_1cbc60(u128 *d, u128 *a, f32 s)
{
    Vu0ScaleF(t0, s, vf5);
    v4_1cbc60 = *a;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cbc60 = _vmul(v6_1cbc60, 0x1, vz_1cbc60, vz_1cbc60);
    v6_1cbc60 = _vmulbc(v6_1cbc60, 0xE, v4_1cbc60, v5_1cbc60, 8);
    *d = v6_1cbc60;
}
