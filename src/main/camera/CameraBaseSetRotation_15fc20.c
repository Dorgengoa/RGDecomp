#include "types.h"

/* s88m de-asm: d[1..3].xyz = s[0..2].xyz (w of d kept), via vaddx.xyz with vf0.
 * Volatile loads keep retail's d-then-s lqc2 order in the third group. */
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz15fc20 asm("vf0");
extern u128 va15fc20 asm("vf1");
extern u128 vb15fc20 asm("vf2");

void CameraBaseSetRotation_15fc20(u128 *d, u128 *s)
{
    va15fc20 = *(volatile u128 *)&d[1];
    vb15fc20 = *(volatile u128 *)&s[0];
    va15fc20 = _vaddbc(va15fc20, 0xE, vb15fc20, vz15fc20, 8);
    d[1] = va15fc20;
    va15fc20 = *(volatile u128 *)&d[2];
    vb15fc20 = *(volatile u128 *)&s[1];
    va15fc20 = _vaddbc(va15fc20, 0xE, vb15fc20, vz15fc20, 8);
    d[2] = va15fc20;
    va15fc20 = *(volatile u128 *)&d[3];
    vb15fc20 = *(volatile u128 *)&s[2];
    va15fc20 = _vaddbc(va15fc20, 0xE, vb15fc20, vz15fc20, 8);
    d[3] = va15fc20;
}
