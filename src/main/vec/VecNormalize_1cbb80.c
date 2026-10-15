#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbb80 asm("vf0");
extern u128 v4_1cbb80 asm("vf4");
extern u128 v5_1cbb80 asm("vf5");
extern u128 v6_1cbb80 asm("vf6");
extern float q_1cbb80 asm("Q");

void VecNormalize_1cbb80(u128 *d, u128 *a)
{
    v4_1cbb80 = *a;
    v5_1cbb80 = _vmul(v5_1cbb80, 0xE, v4_1cbb80, v4_1cbb80);
    v5_1cbb80 = _vaddbc(v5_1cbb80, 0x8, v5_1cbb80, v5_1cbb80, 4);
    v5_1cbb80 = _vaddbc(v5_1cbb80, 0x8, v5_1cbb80, v5_1cbb80, 2);
    q_1cbb80 = _vsqrt(q_1cbb80, v5_1cbb80, 8);
    v5_1cbb80 = _vaddf(v5_1cbb80, 0x8, vz_1cbb80, q_1cbb80);
    v6_1cbb80 = _vsub(v6_1cbb80, 0x1, vz_1cbb80, vz_1cbb80);
    q_1cbb80 = _vdiv(q_1cbb80, vz_1cbb80, 1, v5_1cbb80, 8);
    v6_1cbb80 = _vmulf(v6_1cbb80, 0xE, v4_1cbb80, q_1cbb80);
    *d = v6_1cbb80;
}
