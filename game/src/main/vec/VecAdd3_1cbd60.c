/* rgp:protos */
#define RGP_SELF_VecAdd3_1cbd60 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbd60_t; /* rg:vu0bind vf4 */
#define v4_1cbd60 RG_VU0_BIND_VF(4, rgvb_v4_1cbd60_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbd60_t; /* rg:vu0bind vf5 */
#define v5_1cbd60 RG_VU0_BIND_VF(5, rgvb_v5_1cbd60_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbd60_t; /* rg:vu0bind vf6 */
#define v6_1cbd60 RG_VU0_BIND_VF(6, rgvb_v6_1cbd60_t)


void VecAdd3_1cbd60(u128 *d, u128 *a, u128 *b, u128 *c)
{ RG_VU0_FRAME;
    v4_1cbd60 = *a;
    v5_1cbd60 = *b;
    v6_1cbd60 = *c;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbd60 = _vadd(v4_1cbd60, 0xF, v4_1cbd60, v5_1cbd60);
    v4_1cbd60 = _vadd(v4_1cbd60, 0xF, v4_1cbd60, v6_1cbd60);
    *d = v4_1cbd60;
}
