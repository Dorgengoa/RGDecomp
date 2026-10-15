#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cb2b0 asm("vf0");
extern u128 v4_1cb2b0 asm("vf4");
extern u128 v5_1cb2b0 asm("vf5");
extern u128 v6_1cb2b0 asm("vf6");
extern u128 v7_1cb2b0 asm("vf7");
extern u128 v9_1cb2b0 asm("vf9");

/* d = scale(s) with translation row src.xyz, w = 1 */
void MatFromPosScale_1cb2b0(u128 *d, u128 *src, f32 s)
{
    Vu0ScaleF(a1, s, vf9);
    v7_1cb2b0 = *src;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cb2b0 = _vsub(v4_1cb2b0, 0xF, vz_1cb2b0, vz_1cb2b0);
    v5_1cb2b0 = _vsub(v5_1cb2b0, 0xF, vz_1cb2b0, vz_1cb2b0);
    v6_1cb2b0 = _vsub(v6_1cb2b0, 0xF, vz_1cb2b0, vz_1cb2b0);
    v4_1cb2b0 = _vaddbc(v4_1cb2b0, 0x8, v4_1cb2b0, v9_1cb2b0, 8);
    v5_1cb2b0 = _vaddbc(v5_1cb2b0, 0x4, v5_1cb2b0, v9_1cb2b0, 8);
    v6_1cb2b0 = _vaddbc(v6_1cb2b0, 0x2, v6_1cb2b0, v9_1cb2b0, 8);
    v7_1cb2b0 = _vmul(v7_1cb2b0, 0x1, vz_1cb2b0, vz_1cb2b0);
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    d[0] = v4_1cb2b0;
    d[1] = v5_1cb2b0;
    d[2] = v6_1cb2b0;
    d[3] = v7_1cb2b0;
}
