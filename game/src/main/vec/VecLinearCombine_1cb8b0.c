/* rgp:protos */
#define RGP_SELF_VecLinearCombine_1cb8b0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb8b0_t; /* rg:vu0bind vf4 */
#define v4_1cb8b0 RG_VU0_BIND_VF(4, rgvb_v4_1cb8b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb8b0_t; /* rg:vu0bind vf5 */
#define v5_1cb8b0 RG_VU0_BIND_VF(5, rgvb_v5_1cb8b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cb8b0_t; /* rg:vu0bind vf9 */
#define v9_1cb8b0 RG_VU0_BIND_VF(9, rgvb_v9_1cb8b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb8b0_t; /* rg:vu0bind ACC */
#define acc_1cb8b0 RG_VU0_BIND_ACC(rgvb_acc_1cb8b0_t)


void VecLinearCombine_1cb8b0(u128 *d, u128 *a, u128 *b, f32 s, f32 t)
{ RG_VU0_FRAME;
    Vu0BlendVectorF(s, t);
    v4_1cb8b0 = *a;
    v5_1cb8b0 = *b;
    Vu0BlendVectorAcc();
    v9_1cb8b0 = _vmaddbc(v9_1cb8b0, 0xF, acc_1cb8b0, v5_1cb8b0, v9_1cb8b0, 8);
    *d = v9_1cb8b0;
}
