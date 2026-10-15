#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbc80 asm("vf0");
extern u128 v4_1cbc80 asm("vf4");
extern u128 v5_1cbc80 asm("vf5");
extern u128 v6_1cbc80 asm("vf6");

/* d.xyz = a.xyz * s, d.w = 0 */
void VecScaleDir_1cbc80(u128 *d, u128 *a, f32 s)
{
    Vu0ScaleF(t0, s, vf5);
    v4_1cbc80 = *a;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cbc80 = _vsub(v6_1cbc80, 0x1, vz_1cbc80, vz_1cbc80);
    v6_1cbc80 = _vmulbc(v6_1cbc80, 0xE, v4_1cbc80, v5_1cbc80, 8);
    *d = v6_1cbc80;
}
