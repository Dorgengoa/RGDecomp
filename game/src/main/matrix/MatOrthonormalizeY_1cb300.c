/* rgp:protos */
#define RGP_SELF_MatOrthonormalizeY_1cb300 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cb300_t; /* rg:vu0bind vf0 */
#define vz_1cb300 RG_VU0_BIND_VF(0, rgvb_vz_1cb300_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb300_t; /* rg:vu0bind vf4 */
#define v4_1cb300 RG_VU0_BIND_VF(4, rgvb_v4_1cb300_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb300_t; /* rg:vu0bind vf5 */
#define v5_1cb300 RG_VU0_BIND_VF(5, rgvb_v5_1cb300_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb300_t; /* rg:vu0bind vf6 */
#define v6_1cb300 RG_VU0_BIND_VF(6, rgvb_v6_1cb300_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cb300_t; /* rg:vu0bind vf7 */
#define v7_1cb300 RG_VU0_BIND_VF(7, rgvb_v7_1cb300_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cb300_t; /* rg:vu0bind vf8 */
#define v8_1cb300 RG_VU0_BIND_VF(8, rgvb_v8_1cb300_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb300_t; /* rg:vu0bind ACC */
#define acc_1cb300 RG_VU0_BIND_ACC(rgvb_acc_1cb300_t)

typedef float __attribute__((aligned(4))) rgvb_q_1cb300_t; /* rg:vu0bind Q */
#define q_1cb300 RG_VU0_BIND_Q(rgvb_q_1cb300_t)


void MatOrthonormalizeY_1cb300(u128 *d, u128 *m)
{ RG_VU0_FRAME;
    v5_1cb300 = m[1];
    v6_1cb300 = m[2];
    v7_1cb300 = m[3];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cb300 = _vmul(v8_1cb300, 0xE, v5_1cb300, v5_1cb300);
    v8_1cb300 = _vaddbc(v8_1cb300, 0x8, v8_1cb300, v8_1cb300, 4);
    v8_1cb300 = _vaddbc(v8_1cb300, 0x8, v8_1cb300, v8_1cb300, 2);
    Vu0OrthoNormalSqrt(vf4);
    v8_1cb300 = _vaddf(v8_1cb300, 0x8, vz_1cb300, q_1cb300);
    v5_1cb300 = _vsub(v5_1cb300, 0x1, vz_1cb300, vz_1cb300);
    q_1cb300 = _vdiv(q_1cb300, vz_1cb300, 1, v8_1cb300, 8);
    v5_1cb300 = _vmulf(v5_1cb300, 0xE, v5_1cb300, q_1cb300);
    Vu0OuterProductAcc(vf5, vf6);
    v4_1cb300 = _vopmsub(v4_1cb300, acc_1cb300, v6_1cb300, v5_1cb300);
    v8_1cb300 = _vmul(v8_1cb300, 0xE, v4_1cb300, v4_1cb300);
    v8_1cb300 = _vaddbc(v8_1cb300, 0x8, v8_1cb300, v8_1cb300, 4);
    v8_1cb300 = _vaddbc(v8_1cb300, 0x8, v8_1cb300, v8_1cb300, 2);
    Vu0OrthoNormalSqrt(vf6);
    v8_1cb300 = _vaddf(v8_1cb300, 0x8, vz_1cb300, q_1cb300);
    v7_1cb300 = _vmul(v7_1cb300, 0x1, vz_1cb300, vz_1cb300);
    q_1cb300 = _vdiv(q_1cb300, vz_1cb300, 1, v8_1cb300, 8);
    v4_1cb300 = _vmulf(v4_1cb300, 0xE, v4_1cb300, q_1cb300);
    Vu0OuterProductAcc(vf4, vf5);
    v6_1cb300 = _vopmsub(v6_1cb300, acc_1cb300, v5_1cb300, v4_1cb300);
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    d[0] = v4_1cb300;
    d[1] = v5_1cb300;
    d[2] = v6_1cb300;
    d[3] = v7_1cb300;
}
