/* rgp:protos */
#define RGP_SELF_VecSubXyzW0_1cbce0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbce0_t; /* rg:vu0bind vf0 */
#define vz_1cbce0 RG_VU0_BIND_VF(0, rgvb_vz_1cbce0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbce0_t; /* rg:vu0bind vf4 */
#define v4_1cbce0 RG_VU0_BIND_VF(4, rgvb_v4_1cbce0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbce0_t; /* rg:vu0bind vf5 */
#define v5_1cbce0 RG_VU0_BIND_VF(5, rgvb_v5_1cbce0_t)


void VecSubXyzW0_1cbce0(u128 *d, u128 *a, u128 *b)
{ RG_VU0_FRAME;
    v5_1cbce0 = *b;
    v4_1cbce0 = *a;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbce0 = _vsub(v4_1cbce0, 0x1, vz_1cbce0, vz_1cbce0);
    v4_1cbce0 = _vsub(v4_1cbce0, 0xE, v4_1cbce0, v5_1cbce0);
    *d = v4_1cbce0;
}
