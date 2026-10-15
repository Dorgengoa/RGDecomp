#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbbf0 asm("vf0");
extern u128 v4_1cbbf0 asm("vf4");
extern u128 v5_1cbbf0 asm("vf5");
extern u128 v6_1cbbf0 asm("vf6");
extern float q_1cbbf0 asm("Q");

/* d = a / s */
void VecDivScalar_1cbbf0(u128 *d, u128 *a, f32 s)
{
    Vu0ScaleF(a1, s, vf5);
    v4_1cbbf0 = *a;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    q_1cbbf0 = _vdiv(q_1cbbf0, vz_1cbbf0, 1, v5_1cbbf0, 8);
    v6_1cbbf0 = _vmulf(v6_1cbbf0, 0xF, v4_1cbbf0, q_1cbbf0);
    *d = v6_1cbbf0;
}

