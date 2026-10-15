#include "types.h"

/* s88m de-asm: d[0..2] = s[1..3]; d[3] = vf0 (0,0,0,1). */
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz15fc60 asm("vf0");

void CameraBaseGetMatrix_15fc60(u128 *s, u128 *d)
{
    d[0] = s[1];
    d[1] = s[2];
    d[2] = s[3];
    d[3] = vz15fc60;
}
