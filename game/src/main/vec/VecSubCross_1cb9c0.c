/* rgp:protos */
#define RGP_SELF_VecSubCross_1cb9c0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb9c0_t; /* rg:vu0bind vf4 */
#define v4_1cb9c0 RG_VU0_BIND_VF(4, rgvb_v4_1cb9c0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb9c0_t; /* rg:vu0bind vf5 */
#define v5_1cb9c0 RG_VU0_BIND_VF(5, rgvb_v5_1cb9c0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb9c0_t; /* rg:vu0bind vf6 */
#define v6_1cb9c0 RG_VU0_BIND_VF(6, rgvb_v6_1cb9c0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cb9c0_t; /* rg:vu0bind vf7 */
#define v7_1cb9c0 RG_VU0_BIND_VF(7, rgvb_v7_1cb9c0_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb9c0_t; /* rg:vu0bind ACC */
#define acc_1cb9c0 RG_VU0_BIND_ACC(rgvb_acc_1cb9c0_t)


void VecSubCross_1cb9c0(u128 *d, u128 *a, u128 *b, u128 *c)
{ RG_VU0_FRAME;
    v4_1cb9c0 = *a;
    v5_1cb9c0 = *b;
    v6_1cb9c0 = *c;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cb9c0 = _vsub(v4_1cb9c0, 0xF, v4_1cb9c0, v5_1cb9c0);
    Vu0OuterProductAcc(vf4, vf6);
    v7_1cb9c0 = _vopmsub(v7_1cb9c0, acc_1cb9c0, v6_1cb9c0, v4_1cb9c0);
    v7_1cb9c0 = _vsub(v7_1cb9c0, 0x1, v7_1cb9c0, v7_1cb9c0);
    *d = v7_1cb9c0;
}
