#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbbc0 asm("vf0");
extern u128 v4_1cbbc0 asm("vf4");
extern u128 v5_1cbbc0 asm("vf5");
extern u128 v6_1cbbc0 asm("vf6");
extern float q_1cbbc0 asm("Q");

/* d.xyz = a.xyz / s, d.w = 1 */
void VecDivScalarPoint_1cbbc0(u128 *d, u128 *a, f32 s)
{
    Vu0ScaleF(a1, s, vf5);
    v4_1cbbc0 = *a;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cbbc0 = _vmul(v6_1cbbc0, 0x1, vz_1cbbc0, vz_1cbbc0);
    q_1cbbc0 = _vdiv(q_1cbbc0, vz_1cbbc0, 1, v5_1cbbc0, 8);
    v6_1cbbc0 = _vmulf(v6_1cbbc0, 0xE, v4_1cbbc0, q_1cbbc0);
    *d = v6_1cbbc0;
}
