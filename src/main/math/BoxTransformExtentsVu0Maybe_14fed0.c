#include "types.h"
#include "libvu0.h"

/* VU0 leaf: rotate the three axis vectors the caller left in vf10..vf12 by
 * the 3x3 part of m (lqc2 vf1..vf4), sum their absolute values (box extent)
 * into *e, and transform the point in vf7 by m into *d.
 * mwcc intrinsics on file-scope register bindings; only the ACC-destination
 * ops and the vf26 result are SDK macros (Vu0ApplyMatrix3Acc, Vu0AddAcc,
 * Vu0MulMatrixAcc, Vu0StoreAccW26 in libvu0.h). */

#pragma vu0_mmi_reg_binding on

typedef unsigned __int128 u128_14fed0;

extern u128_14fed0 vz_14fed0 asm("vf0");
extern u128_14fed0 v1_14fed0 asm("vf1");
extern u128_14fed0 v2_14fed0 asm("vf2");
extern u128_14fed0 v3_14fed0 asm("vf3");
extern u128_14fed0 v4_14fed0 asm("vf4");
extern u128_14fed0 v10_14fed0 asm("vf10");
extern u128_14fed0 v11_14fed0 asm("vf11");
extern u128_14fed0 v12_14fed0 asm("vf12");
extern u128_14fed0 v20_14fed0 asm("vf20");
extern u128_14fed0 v21_14fed0 asm("vf21");
extern u128_14fed0 v22_14fed0 asm("vf22");
extern u128_14fed0 v25_14fed0 asm("vf25");
extern u128_14fed0 acc_14fed0 asm("ACC");

void BoxTransformExtentsVu0Maybe_14fed0(u128_14fed0 *e, u128_14fed0 *d, u128_14fed0 *m)
{
    v1_14fed0 = m[0];
    v2_14fed0 = m[1];
    v3_14fed0 = m[2];
    v4_14fed0 = m[3];
    Vu0ApplyMatrix3Acc(xyzw, vf1, vf2, vf10);
    v20_14fed0 = _vmaddbc(v20_14fed0, 0xF, acc_14fed0, v3_14fed0, v10_14fed0, 2);
    Vu0ApplyMatrix3Acc(xyzw, vf1, vf2, vf11);
    v21_14fed0 = _vmaddbc(v21_14fed0, 0xF, acc_14fed0, v3_14fed0, v11_14fed0, 2);
    Vu0ApplyMatrix3Acc(xyzw, vf1, vf2, vf12);
    v22_14fed0 = _vmaddbc(v22_14fed0, 0xF, acc_14fed0, v3_14fed0, v12_14fed0, 2);
    v20_14fed0 = _vabs(v20_14fed0, 0xF, v20_14fed0);
    v21_14fed0 = _vabs(v21_14fed0, 0xF, v21_14fed0);
    v22_14fed0 = _vabs(v22_14fed0, 0xF, v22_14fed0);
    Vu0AddAcc(vf20, vf21);
    v25_14fed0 = _vmaddbc(v25_14fed0, 0xF, acc_14fed0, v22_14fed0, vz_14fed0, 1);
    Vu0MulMatrixAcc(xyzw, vf1, vf2, vf3, vf7);
    Vu0StoreAccW26(d);
    *e = v25_14fed0;
}
