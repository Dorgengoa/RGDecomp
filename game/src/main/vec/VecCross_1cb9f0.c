/* rgp:protos */
#define RGP_SELF_VecCross_1cb9f0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb9f0_t; /* rg:vu0bind vf4 */
#define v4_1cb9f0 RG_VU0_BIND_VF(4, rgvb_v4_1cb9f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb9f0_t; /* rg:vu0bind vf5 */
#define v5_1cb9f0 RG_VU0_BIND_VF(5, rgvb_v5_1cb9f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb9f0_t; /* rg:vu0bind vf6 */
#define v6_1cb9f0 RG_VU0_BIND_VF(6, rgvb_v6_1cb9f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb9f0_t; /* rg:vu0bind ACC */
#define acc_1cb9f0 RG_VU0_BIND_ACC(rgvb_acc_1cb9f0_t)


void VecCross_1cb9f0(u128 *d, u128 *a, u128 *b)
{ RG_VU0_FRAME;
    v4_1cb9f0 = *a;
    v5_1cb9f0 = *b;
    Vu0OuterProductAcc(vf4, vf5);
    v6_1cb9f0 = _vopmsub(v6_1cb9f0, acc_1cb9f0, v5_1cb9f0, v4_1cb9f0);
    v6_1cb9f0 = _vsub(v6_1cb9f0, 0x1, v6_1cb9f0, v6_1cb9f0);
    *d = v6_1cb9f0;
}
