/* rgp:protos */
#define RGP_SELF_VecMinMax_1cb570 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v12_1cb570_t; /* rg:vu0bind vf12 */
#define v12_1cb570 RG_VU0_BIND_VF(12, rgvb_v12_1cb570_t)

typedef u128 __attribute__((aligned(4))) rgvb_v13_1cb570_t; /* rg:vu0bind vf13 */
#define v13_1cb570 RG_VU0_BIND_VF(13, rgvb_v13_1cb570_t)

typedef u128 __attribute__((aligned(4))) rgvb_v17_1cb570_t; /* rg:vu0bind vf17 */
#define v17_1cb570 RG_VU0_BIND_VF(17, rgvb_v17_1cb570_t)

typedef u128 __attribute__((aligned(4))) rgvb_v18_1cb570_t; /* rg:vu0bind vf18 */
#define v18_1cb570 RG_VU0_BIND_VF(18, rgvb_v18_1cb570_t)


void VecMinMax_1cb570(u128 *mx, u128 *mn, u128 *a, u128 *b)
{ RG_VU0_FRAME;
    v12_1cb570 = *a;
    v13_1cb570 = *b;
    v17_1cb570 = _vmax(v17_1cb570, 0xF, v12_1cb570, v13_1cb570);
    v18_1cb570 = _vmini(v18_1cb570, 0xF, v12_1cb570, v13_1cb570);
    /* zero-word block split on a live pointer (scheduling barrier) */
    if (mx) {
        mx = (u128 *)(s32)(u32)mx;
    }
    *mx = v17_1cb570;
    *mn = v18_1cb570;
}
