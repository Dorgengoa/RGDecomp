/* rgp:protos */
#define RGP_SELF_MatScaleRows_1cbc20 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbc20_t; /* rg:vu0bind vf4 */
#define v4_1cbc20 RG_VU0_BIND_VF(4, rgvb_v4_1cbc20_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbc20_t; /* rg:vu0bind vf5 */
#define v5_1cbc20 RG_VU0_BIND_VF(5, rgvb_v5_1cbc20_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbc20_t; /* rg:vu0bind vf6 */
#define v6_1cbc20 RG_VU0_BIND_VF(6, rgvb_v6_1cbc20_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cbc20_t; /* rg:vu0bind vf7 */
#define v7_1cbc20 RG_VU0_BIND_VF(7, rgvb_v7_1cbc20_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cbc20_t; /* rg:vu0bind vf8 */
#define v8_1cbc20 RG_VU0_BIND_VF(8, rgvb_v8_1cbc20_t)


void MatScaleRows_1cbc20(u128 *d, u128 *m, u128 *v)
{ RG_VU0_FRAME;
    v4_1cbc20 = m[0];
    v5_1cbc20 = m[1];
    v6_1cbc20 = m[2];
    v7_1cbc20 = m[3];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cbc20 = *v;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cbc20 = _vmulbc(v4_1cbc20, 0xF, v4_1cbc20, v8_1cbc20, 8);
    v5_1cbc20 = _vmulbc(v5_1cbc20, 0xF, v5_1cbc20, v8_1cbc20, 4);
    v6_1cbc20 = _vmulbc(v6_1cbc20, 0xF, v6_1cbc20, v8_1cbc20, 2);
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    d[0] = v4_1cbc20;
    d[1] = v5_1cbc20;
    d[2] = v6_1cbc20;
    d[3] = v7_1cbc20;
}
