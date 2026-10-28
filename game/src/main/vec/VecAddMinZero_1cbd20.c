/* rgp:protos */
#define RGP_SELF_VecAddMinZero_1cbd20 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbd20_t; /* rg:vu0bind vf0 */
#define vz_1cbd20 RG_VU0_BIND_VF(0, rgvb_vz_1cbd20_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbd20_t; /* rg:vu0bind vf4 */
#define v4_1cbd20 RG_VU0_BIND_VF(4, rgvb_v4_1cbd20_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbd20_t; /* rg:vu0bind vf5 */
#define v5_1cbd20 RG_VU0_BIND_VF(5, rgvb_v5_1cbd20_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbd20_t; /* rg:vu0bind vf6 */
#define v6_1cbd20 RG_VU0_BIND_VF(6, rgvb_v6_1cbd20_t)


void VecAddMinZero_1cbd20(u128 *d, u128 *a, u128 *b)
{ RG_VU0_FRAME;
    v5_1cbd20 = *b;
    v4_1cbd20 = *a;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cbd20 = _vsub(v6_1cbd20, 0xF, vz_1cbd20, vz_1cbd20);
    v5_1cbd20 = _vmini(v5_1cbd20, 0xF, v5_1cbd20, v6_1cbd20);
    v4_1cbd20 = _vadd(v4_1cbd20, 0xF, v4_1cbd20, v5_1cbd20);
    *d = v4_1cbd20;
}
