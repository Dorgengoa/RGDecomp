/* rgp:protos */
#define RGP_SELF_VecSinCos_1cbfb0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbfb0_t; /* rg:vu0bind vf0 */
#define vz_1cbfb0 RG_VU0_BIND_VF(0, rgvb_vz_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbfb0_t; /* rg:vu0bind vf4 */
#define v4_1cbfb0 RG_VU0_BIND_VF(4, rgvb_v4_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbfb0_t; /* rg:vu0bind vf5 */
#define v5_1cbfb0 RG_VU0_BIND_VF(5, rgvb_v5_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbfb0_t; /* rg:vu0bind vf6 */
#define v6_1cbfb0 RG_VU0_BIND_VF(6, rgvb_v6_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cbfb0_t; /* rg:vu0bind vf7 */
#define v7_1cbfb0 RG_VU0_BIND_VF(7, rgvb_v7_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cbfb0_t; /* rg:vu0bind vf8 */
#define v8_1cbfb0 RG_VU0_BIND_VF(8, rgvb_v8_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cbfb0_t; /* rg:vu0bind vf9 */
#define v9_1cbfb0 RG_VU0_BIND_VF(9, rgvb_v9_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v10_1cbfb0_t; /* rg:vu0bind vf10 */
#define v10_1cbfb0 RG_VU0_BIND_VF(10, rgvb_v10_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v11_1cbfb0_t; /* rg:vu0bind vf11 */
#define v11_1cbfb0 RG_VU0_BIND_VF(11, rgvb_v11_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v12_1cbfb0_t; /* rg:vu0bind vf12 */
#define v12_1cbfb0 RG_VU0_BIND_VF(12, rgvb_v12_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v13_1cbfb0_t; /* rg:vu0bind vf13 */
#define v13_1cbfb0 RG_VU0_BIND_VF(13, rgvb_v13_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v14_1cbfb0_t; /* rg:vu0bind vf14 */
#define v14_1cbfb0 RG_VU0_BIND_VF(14, rgvb_v14_1cbfb0_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cbfb0_t; /* rg:vu0bind ACC */
#define acc_1cbfb0 RG_VU0_BIND_ACC(rgvb_acc_1cbfb0_t)

extern u128 D_0044B2C0[3];

void VecSinCos_1cbfb0(u128 *d, u128 *s)
{ RG_VU0_FRAME;
    u128 *k;

    k = (u128 *)(s32)D_0044B2C0;

    if (k) {
        k = (u128 *)(s32)(u32)k;
    }
    v4_1cbfb0 = *s;
    v5_1cbfb0 = k[0];
    v6_1cbfb0 = k[1];
    v7_1cbfb0 = k[2];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbfb0 = _vmulbc(v4_1cbfb0, 0x1, vz_1cbfb0, v4_1cbfb0, 2);
    v4_1cbfb0 = _vaddbc(v4_1cbfb0, 0x4, vz_1cbfb0, v4_1cbfb0, 8);
    v4_1cbfb0 = _vsubbc(v4_1cbfb0, 0xA, v4_1cbfb0, v5_1cbfb0, 8);
    v4_1cbfb0 = _vabs(v4_1cbfb0, 0xF, v4_1cbfb0);
    v8_1cbfb0 = _vmaxbc(v8_1cbfb0, 0xF, vz_1cbfb0, vz_1cbfb0, 1);
    Vu0SinCosAccR();
    v4_1cbfb0 = _vmsubbc(v4_1cbfb0, 0xF, acc_1cbfb0, v8_1cbfb0, v6_1cbfb0, 8);
    v4_1cbfb0 = _vabs(v4_1cbfb0, 0xF, v4_1cbfb0);
    v4_1cbfb0 = _vsubbc(v4_1cbfb0, 0xF, v4_1cbfb0, v6_1cbfb0, 4);
    v12_1cbfb0 = _vmul(v12_1cbfb0, 0xF, v4_1cbfb0, v4_1cbfb0);
    v11_1cbfb0 = _vmulbc(v11_1cbfb0, 0xF, v4_1cbfb0, v7_1cbfb0, 8);
    v9_1cbfb0 = _vmulbc(v9_1cbfb0, 0xF, v4_1cbfb0, v7_1cbfb0, 4);
    v10_1cbfb0 = _vmulbc(v10_1cbfb0, 0xF, v4_1cbfb0, v7_1cbfb0, 2);
    v13_1cbfb0 = _vmul(v13_1cbfb0, 0xF, v12_1cbfb0, v12_1cbfb0);
    v11_1cbfb0 = _vmul(v11_1cbfb0, 0xF, v11_1cbfb0, v12_1cbfb0);
    Vu0SinCosAccP0();
    v9_1cbfb0 = _vmulbc(v9_1cbfb0, 0xF, v4_1cbfb0, v7_1cbfb0, 1);
    v14_1cbfb0 = _vmul(v14_1cbfb0, 0xF, v13_1cbfb0, v13_1cbfb0);
    Vu0SinCosAccP1();
    v4_1cbfb0 = _vmadd(v4_1cbfb0, 0xF, acc_1cbfb0, v9_1cbfb0, v14_1cbfb0);
    *d = v4_1cbfb0;
}
