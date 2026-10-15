#include "types.h"
#include "libvu0.h"
typedef unsigned __int128 u128;
#pragma vu0_mmi_reg_binding on
extern u128 vz_1cb640 asm("vf0");
extern u128 v1_1cb640 asm("vf1");
extern u128 v2_1cb640 asm("vf2");
extern u128 v3_1cb640 asm("vf3");
extern u128 v4_1cb640 asm("vf4");
extern u128 v5_1cb640 asm("vf5");
extern u128 v6_1cb640 asm("vf6");
extern u128 v7_1cb640 asm("vf7");
extern u128 v8_1cb640 asm("vf8");
extern u128 v9_1cb640 asm("vf9");
extern u128 acc_1cb640 asm("ACC");
extern float q_1cb640 asm("Q");

f32 MtxInverseAffine_1cb640(u128 *d, u128 *m)
{
    f32 det;

    Vu0InversMatrixLoad(m);
    Vu0OuterProductAcc(vf2, vf3);
    v5_1cb640 = _vopmsub(v5_1cb640, acc_1cb640, v3_1cb640, v2_1cb640);
    v5_1cb640 = _vsub(v5_1cb640, 0x1, vz_1cb640, vz_1cb640);
    v9_1cb640 = _vmul(v9_1cb640, 0xE, v5_1cb640, v1_1cb640);
    v9_1cb640 = _vaddbc(v9_1cb640, 0x8, v9_1cb640, v9_1cb640, 4);
    v9_1cb640 = _vaddbc(v9_1cb640, 0x8, v9_1cb640, v9_1cb640, 2);
    Vu0InversMatrixDet(det);
    Vu0OuterProductAcc(vf3, vf1);
    v6_1cb640 = _vopmsub(v6_1cb640, acc_1cb640, v1_1cb640, v3_1cb640);
    v6_1cb640 = _vsub(v6_1cb640, 0x1, vz_1cb640, vz_1cb640);
    Vu0OuterProductAcc(vf1, vf2);
    v7_1cb640 = _vopmsub(v7_1cb640, acc_1cb640, v2_1cb640, v1_1cb640);
    v7_1cb640 = _vsub(v7_1cb640, 0x1, vz_1cb640, vz_1cb640);
    _vwaitq(q_1cb640);
    v5_1cb640 = _vmulf(v5_1cb640, 0xE, v5_1cb640, q_1cb640);
    v6_1cb640 = _vmulf(v6_1cb640, 0xE, v6_1cb640, q_1cb640);
    v7_1cb640 = _vmulf(v7_1cb640, 0xE, v7_1cb640, q_1cb640);
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v9_1cb640 = _vaddbc(v9_1cb640, 0x4, vz_1cb640, v6_1cb640, 8);
    v6_1cb640 = _vmr32(v6_1cb640, 0x8, v5_1cb640);
    v5_1cb640 = _vmove(v5_1cb640, 0x4, v9_1cb640);
    v9_1cb640 = _vaddbc(v9_1cb640, 0x2, vz_1cb640, v7_1cb640, 4);
    v7_1cb640 = _vmr32(v7_1cb640, 0x4, v6_1cb640);
    v6_1cb640 = _vmove(v6_1cb640, 0x2, v9_1cb640);
    v9_1cb640 = _vaddbc(v9_1cb640, 0x8, vz_1cb640, v5_1cb640, 2);
    v5_1cb640 = _vaddbc(v5_1cb640, 0x2, vz_1cb640, v7_1cb640, 8);
    v7_1cb640 = _vmove(v7_1cb640, 0x8, v9_1cb640);
    Vu0ApplyMatrix3Acc(xyz, vf5, vf6, vf4);
    v8_1cb640 = _vmaddbc(v8_1cb640, 0xE, acc_1cb640, v7_1cb640, v4_1cb640, 2);
    v8_1cb640 = _vsub(v8_1cb640, 0xE, vz_1cb640, v8_1cb640);
    v8_1cb640 = _vmul(v8_1cb640, 0x1, vz_1cb640, vz_1cb640);
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    d[0] = v5_1cb640;
    d[1] = v6_1cb640;
    d[2] = v7_1cb640;
    d[3] = v8_1cb640;
    return det;
}
