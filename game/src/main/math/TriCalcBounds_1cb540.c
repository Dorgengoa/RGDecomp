/* rgp:protos */
#define RGP_SELF_TriCalcBounds_1cb540 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v12_1cb540_t; /* rg:vu0bind vf12 */
#define v12_1cb540 RG_VU0_BIND_VF(12, rgvb_v12_1cb540_t)

typedef u128 __attribute__((aligned(4))) rgvb_v13_1cb540_t; /* rg:vu0bind vf13 */
#define v13_1cb540 RG_VU0_BIND_VF(13, rgvb_v13_1cb540_t)

typedef u128 __attribute__((aligned(4))) rgvb_v14_1cb540_t; /* rg:vu0bind vf14 */
#define v14_1cb540 RG_VU0_BIND_VF(14, rgvb_v14_1cb540_t)

typedef u128 __attribute__((aligned(4))) rgvb_v17_1cb540_t; /* rg:vu0bind vf17 */
#define v17_1cb540 RG_VU0_BIND_VF(17, rgvb_v17_1cb540_t)

typedef u128 __attribute__((aligned(4))) rgvb_v18_1cb540_t; /* rg:vu0bind vf18 */
#define v18_1cb540 RG_VU0_BIND_VF(18, rgvb_v18_1cb540_t)


void TriCalcBounds_1cb540(u128 *mx, u128 *mn, u128 *a, u128 *b, u128 *c)
{ RG_VU0_FRAME;
    v12_1cb540 = *a;
    v13_1cb540 = *b;
    v14_1cb540 = *c;
    if (mx) {
        mx = (u128 *)(s32)(u32)mx;
    }
    v17_1cb540 = _vmax(v17_1cb540, 0xF, v12_1cb540, v13_1cb540);
    v17_1cb540 = _vmax(v17_1cb540, 0xF, v17_1cb540, v14_1cb540);
    if (mx) {
        mx = (u128 *)(s32)(u32)mx;
    }
    v18_1cb540 = _vmini(v18_1cb540, 0xF, v12_1cb540, v13_1cb540);
    v18_1cb540 = _vmini(v18_1cb540, 0xF, v18_1cb540, v14_1cb540);
    if (mx) {
        mx = (u128 *)(s32)(u32)mx;
    }
    *mx = v17_1cb540;
    *mn = v18_1cb540;
}
