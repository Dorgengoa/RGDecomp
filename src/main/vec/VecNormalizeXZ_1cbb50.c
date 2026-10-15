#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz_1cbb50 asm("vf0");
extern u128 v4_1cbb50 asm("vf4");
extern u128 v5_1cbb50 asm("vf5");
extern u128 v6_1cbb50 asm("vf6");
extern float q_1cbb50 asm("Q");

void VecNormalizeXZ_1cbb50(u128 *d, u128 *a)
{
    v4_1cbb50 = *a;
    v5_1cbb50 = _vmul(v5_1cbb50, 0xE, v4_1cbb50, v4_1cbb50);
    v5_1cbb50 = _vaddbc(v5_1cbb50, 0x2, v5_1cbb50, v5_1cbb50, 8);
    q_1cbb50 = _vsqrt(q_1cbb50, v5_1cbb50, 2);
    v5_1cbb50 = _vaddf(v5_1cbb50, 0x8, vz_1cbb50, q_1cbb50);
    v6_1cbb50 = _vsub(v6_1cbb50, 0x5, vz_1cbb50, vz_1cbb50);
    q_1cbb50 = _vdiv(q_1cbb50, vz_1cbb50, 1, v5_1cbb50, 8);
    v6_1cbb50 = _vmulf(v6_1cbb50, 0xA, v4_1cbb50, q_1cbb50);
    *d = v6_1cbb50;
}
