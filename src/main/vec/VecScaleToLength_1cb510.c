#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb510 asm("vf4");
extern u128 v5_1cb510 asm("vf5");
extern u128 v6_1cb510 asm("vf6");
extern float q_1cb510 asm("Q");

/* d = a * (s / |a|)   (scale vector to length s) */
void VecScaleToLength_1cb510(u128 *d, u128 *a, f32 s)
{
    v4_1cb510 = *a;
    Vu0ScaleF(a1, s, vf5);
    v6_1cb510 = _vmul(v6_1cb510, 0xF, v4_1cb510, v4_1cb510);
    v6_1cb510 = _vaddbc(v6_1cb510, 0x8, v6_1cb510, v6_1cb510, 4);
    v6_1cb510 = _vaddbc(v6_1cb510, 0x8, v6_1cb510, v6_1cb510, 2);
    q_1cb510 = _vrsqrt(q_1cb510, v5_1cb510, 8, v6_1cb510, 8);
    v4_1cb510 = _vmulf(v4_1cb510, 0xF, v4_1cb510, q_1cb510);
    *d = v4_1cb510;
}
