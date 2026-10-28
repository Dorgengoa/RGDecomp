/* rgp:protos */
#define RGP_SELF_VecNegate_1cb9a0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cb9a0_t; /* rg:vu0bind vf0 */
#define vz_1cb9a0 RG_VU0_BIND_VF(0, rgvb_vz_1cb9a0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb9a0_t; /* rg:vu0bind vf6 */
#define v6_1cb9a0 RG_VU0_BIND_VF(6, rgvb_v6_1cb9a0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cb9a0_t; /* rg:vu0bind vf7 */
#define v7_1cb9a0 RG_VU0_BIND_VF(7, rgvb_v7_1cb9a0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cb9a0_t; /* rg:vu0bind vf8 */
#define v8_1cb9a0 RG_VU0_BIND_VF(8, rgvb_v8_1cb9a0_t)


void VecNegate_1cb9a0(u128 *d, u128 *s)
{ RG_VU0_FRAME;
    v7_1cb9a0 = *s;
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cb9a0 = _vsub(v6_1cb9a0, 0xF, vz_1cb9a0, vz_1cb9a0);
    v8_1cb9a0 = _vsub(v8_1cb9a0, 0xF, v6_1cb9a0, v7_1cb9a0);
    *d = v8_1cb9a0;
}
