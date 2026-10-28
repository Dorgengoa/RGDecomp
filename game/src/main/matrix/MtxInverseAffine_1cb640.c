/* rgp:protos */
#define RGP_SELF_MtxInverseAffine_1cb640 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cb640_t; /* rg:vu0bind vf0 */
#define vz_1cb640 RG_VU0_BIND_VF(0, rgvb_vz_1cb640_t)

typedef u128 __attribute__((aligned(4))) rgvb_v1_1cb640_t; /* rg:vu0bind vf1 */
#define v1_1cb640 RG_VU0_BIND_VF(1, rgvb_v1_1cb640_t)

typedef u128 __attribute__((aligned(4))) rgvb_v2_1cb640_t; /* rg:vu0bind vf2 */
#define v2_1cb640 RG_VU0_BIND_VF(2, rgvb_v2_1cb640_t)

typedef u128 __attribute__((aligned(4))) rgvb_v3_1cb640_t; /* rg:vu0bind vf3 */
#define v3_1cb640 RG_VU0_BIND_VF(3, rgvb_v3_1cb640_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb640_t; /* rg:vu0bind vf4 */
#define v4_1cb640 RG_VU0_BIND_VF(4, rgvb_v4_1cb640_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb640_t; /* rg:vu0bind vf5 */
#define v5_1cb640 RG_VU0_BIND_VF(5, rgvb_v5_1cb640_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb640_t; /* rg:vu0bind vf6 */
#define v6_1cb640 RG_VU0_BIND_VF(6, rgvb_v6_1cb640_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cb640_t; /* rg:vu0bind vf7 */
#define v7_1cb640 RG_VU0_BIND_VF(7, rgvb_v7_1cb640_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cb640_t; /* rg:vu0bind vf8 */
#define v8_1cb640 RG_VU0_BIND_VF(8, rgvb_v8_1cb640_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cb640_t; /* rg:vu0bind vf9 */
#define v9_1cb640 RG_VU0_BIND_VF(9, rgvb_v9_1cb640_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb640_t; /* rg:vu0bind ACC */
#define acc_1cb640 RG_VU0_BIND_ACC(rgvb_acc_1cb640_t)

typedef float __attribute__((aligned(4))) rgvb_q_1cb640_t; /* rg:vu0bind Q */
#define q_1cb640 RG_VU0_BIND_Q(rgvb_q_1cb640_t)


f32 MtxInverseAffine_1cb640(u128 *d, u128 *m)
{ RG_VU0_FRAME;
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
