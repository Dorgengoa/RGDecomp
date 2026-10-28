/* rgp:protos */
#define RGP_SELF_TriNormal_1cb970 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb970_t; /* rg:vu0bind vf4 */
#define v4_1cb970 RG_VU0_BIND_VF(4, rgvb_v4_1cb970_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb970_t; /* rg:vu0bind vf5 */
#define v5_1cb970 RG_VU0_BIND_VF(5, rgvb_v5_1cb970_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb970_t; /* rg:vu0bind vf6 */
#define v6_1cb970 RG_VU0_BIND_VF(6, rgvb_v6_1cb970_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cb970_t; /* rg:vu0bind vf7 */
#define v7_1cb970 RG_VU0_BIND_VF(7, rgvb_v7_1cb970_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb970_t; /* rg:vu0bind ACC */
#define acc_1cb970 RG_VU0_BIND_ACC(rgvb_acc_1cb970_t)


void TriNormal_1cb970(u128 *d, u128 *a, u128 *b, u128 *c)
{ RG_VU0_FRAME;
    v6_1cb970 = *c;
    v5_1cb970 = *b;
    v4_1cb970 = *a;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cb970 = _vsub(v6_1cb970, 0xF, v6_1cb970, v5_1cb970);
    v5_1cb970 = _vsub(v5_1cb970, 0xF, v5_1cb970, v4_1cb970);
    Vu0OuterProductAcc(vf5, vf6);
    v7_1cb970 = _vopmsub(v7_1cb970, acc_1cb970, v6_1cb970, v5_1cb970);
    v7_1cb970 = _vsub(v7_1cb970, 0x1, v7_1cb970, v7_1cb970);
    *d = v7_1cb970;
}
