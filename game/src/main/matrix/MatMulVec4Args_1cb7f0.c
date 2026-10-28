/* rgp:protos */
#define RGP_SELF_MatMulVec4Args_1cb7f0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb7f0_t; /* rg:vu0bind vf4 */
#define v4_1cb7f0 RG_VU0_BIND_VF(4, rgvb_v4_1cb7f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb7f0_t; /* rg:vu0bind vf5 */
#define v5_1cb7f0 RG_VU0_BIND_VF(5, rgvb_v5_1cb7f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb7f0_t; /* rg:vu0bind vf6 */
#define v6_1cb7f0 RG_VU0_BIND_VF(6, rgvb_v6_1cb7f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cb7f0_t; /* rg:vu0bind vf7 */
#define v7_1cb7f0 RG_VU0_BIND_VF(7, rgvb_v7_1cb7f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cb7f0_t; /* rg:vu0bind vf8 */
#define v8_1cb7f0 RG_VU0_BIND_VF(8, rgvb_v8_1cb7f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cb7f0_t; /* rg:vu0bind vf9 */
#define v9_1cb7f0 RG_VU0_BIND_VF(9, rgvb_v9_1cb7f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb7f0_t; /* rg:vu0bind ACC */
#define acc_1cb7f0 RG_VU0_BIND_ACC(rgvb_acc_1cb7f0_t)


void MatMulVec4Args_1cb7f0(u128 *d, u128 *m, f32 x, f32 y, f32 z, f32 w)
{ RG_VU0_FRAME;
    f32 v[4] __attribute__((aligned(16))) = {0};
    u128 *p;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
    p = (u128 *)(s32)v;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cb7f0 = *p;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cb7f0 = m[0];
    v5_1cb7f0 = m[1];
    v6_1cb7f0 = m[2];
    v7_1cb7f0 = m[3];
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf8);
    v9_1cb7f0 = _vmaddbc(v9_1cb7f0, 0xF, acc_1cb7f0, v7_1cb7f0, v8_1cb7f0, 1);
    *d = v9_1cb7f0;
}
