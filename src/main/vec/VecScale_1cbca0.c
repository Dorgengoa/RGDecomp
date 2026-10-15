#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 v4_1cbca0 asm("vf4");
extern u128 v5_1cbca0 asm("vf5");
extern u128 v6_1cbca0 asm("vf6");

/* d = a * s (Sony-style sceVu0ScaleVector) */
void VecScale_1cbca0(u128 *d, u128 *a, f32 s)
{
    Vu0ScaleF(t0, s, vf5);
    v4_1cbca0 = *a;
    v6_1cbca0 = _vmulbc(v6_1cbca0, 0xF, v4_1cbca0, v5_1cbca0, 8);
    *d = v6_1cbca0;
}
