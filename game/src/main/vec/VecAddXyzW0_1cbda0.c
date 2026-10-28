/* rgp:protos */
#define RGP_SELF_VecAddXyzW0_1cbda0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbda0_t; /* rg:vu0bind vf0 */
#define vz_1cbda0 RG_VU0_BIND_VF(0, rgvb_vz_1cbda0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbda0_t; /* rg:vu0bind vf4 */
#define v4_1cbda0 RG_VU0_BIND_VF(4, rgvb_v4_1cbda0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbda0_t; /* rg:vu0bind vf5 */
#define v5_1cbda0 RG_VU0_BIND_VF(5, rgvb_v5_1cbda0_t)


void VecAddXyzW0_1cbda0(u128 *d, u128 *a, u128 *b)
{ RG_VU0_FRAME;
    v4_1cbda0 = *a;
    v5_1cbda0 = *b;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbda0 = _vsub(v4_1cbda0, 0x1, vz_1cbda0, vz_1cbda0);
    v4_1cbda0 = _vadd(v4_1cbda0, 0xE, v4_1cbda0, v5_1cbda0);
    *d = v4_1cbda0;
}
