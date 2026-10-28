/* rgp:protos */
#define RGP_SELF_VecSub_1cbd00 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbd00_t; /* rg:vu0bind vf4 */
#define v4_1cbd00 RG_VU0_BIND_VF(4, rgvb_v4_1cbd00_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbd00_t; /* rg:vu0bind vf5 */
#define v5_1cbd00 RG_VU0_BIND_VF(5, rgvb_v5_1cbd00_t)


void VecSub_1cbd00(u128 *pd, u128 *pa, u128 *pb)
{ RG_VU0_FRAME;
    v5_1cbd00 = *pb;
    v4_1cbd00 = *pa;
    v4_1cbd00 = _vsub(v4_1cbd00, 0xF, v4_1cbd00, v5_1cbd00);
    *pd = v4_1cbd00;
}
