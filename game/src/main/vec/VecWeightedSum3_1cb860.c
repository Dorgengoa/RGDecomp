/* rgp:protos */
#define RGP_SELF_VecWeightedSum3_1cb860 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb860_t; /* rg:vu0bind vf4 */
#define v4_1cb860 RG_VU0_BIND_VF(4, rgvb_v4_1cb860_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb860_t; /* rg:vu0bind vf5 */
#define v5_1cb860 RG_VU0_BIND_VF(5, rgvb_v5_1cb860_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb860_t; /* rg:vu0bind vf6 */
#define v6_1cb860 RG_VU0_BIND_VF(6, rgvb_v6_1cb860_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cb860_t; /* rg:vu0bind vf9 */
#define v9_1cb860 RG_VU0_BIND_VF(9, rgvb_v9_1cb860_t)

typedef u128 __attribute__((aligned(4))) rgvb_v10_1cb860_t; /* rg:vu0bind vf10 */
#define v10_1cb860 RG_VU0_BIND_VF(10, rgvb_v10_1cb860_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb860_t; /* rg:vu0bind ACC */
#define acc_1cb860 RG_VU0_BIND_ACC(rgvb_acc_1cb860_t)


void VecWeightedSum3_1cb860(u128 *d, u128 *a, u128 *b, u128 *c, f32 wa, f32 wb, f32 wc)
{ RG_VU0_FRAME;
    Vu0BlendVector3F(wa, wb, wc);
    v4_1cb860 = *a;
    v5_1cb860 = *b;
    v6_1cb860 = *c;
    Vu0BlendVector3Acc();
    v9_1cb860 = _vmaddbc(v9_1cb860, 0xF, acc_1cb860, v6_1cb860, v10_1cb860, 8);
    *d = v9_1cb860;
}
