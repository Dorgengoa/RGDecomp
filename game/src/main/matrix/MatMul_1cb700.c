/* rgp:protos */
#define RGP_SELF_MatMul_1cb700 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb700_t; /* rg:vu0bind vf4 */
#define v4_1cb700 RG_VU0_BIND_VF(4, rgvb_v4_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb700_t; /* rg:vu0bind vf5 */
#define v5_1cb700 RG_VU0_BIND_VF(5, rgvb_v5_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb700_t; /* rg:vu0bind vf6 */
#define v6_1cb700 RG_VU0_BIND_VF(6, rgvb_v6_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cb700_t; /* rg:vu0bind vf7 */
#define v7_1cb700 RG_VU0_BIND_VF(7, rgvb_v7_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cb700_t; /* rg:vu0bind vf8 */
#define v8_1cb700 RG_VU0_BIND_VF(8, rgvb_v8_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cb700_t; /* rg:vu0bind vf9 */
#define v9_1cb700 RG_VU0_BIND_VF(9, rgvb_v9_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v10_1cb700_t; /* rg:vu0bind vf10 */
#define v10_1cb700 RG_VU0_BIND_VF(10, rgvb_v10_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v11_1cb700_t; /* rg:vu0bind vf11 */
#define v11_1cb700 RG_VU0_BIND_VF(11, rgvb_v11_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v12_1cb700_t; /* rg:vu0bind vf12 */
#define v12_1cb700 RG_VU0_BIND_VF(12, rgvb_v12_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v13_1cb700_t; /* rg:vu0bind vf13 */
#define v13_1cb700 RG_VU0_BIND_VF(13, rgvb_v13_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v14_1cb700_t; /* rg:vu0bind vf14 */
#define v14_1cb700 RG_VU0_BIND_VF(14, rgvb_v14_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_v15_1cb700_t; /* rg:vu0bind vf15 */
#define v15_1cb700 RG_VU0_BIND_VF(15, rgvb_v15_1cb700_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb700_t; /* rg:vu0bind ACC */
#define acc_1cb700 RG_VU0_BIND_ACC(rgvb_acc_1cb700_t)


void MatMul_1cb700(u128 *d, u128 *a, u128 *b)
{ RG_VU0_FRAME;
    v4_1cb700 = a[0];
    v5_1cb700 = a[1];
    v6_1cb700 = a[2];
    v7_1cb700 = a[3];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cb700 = b[0];
    v9_1cb700 = b[1];
    v10_1cb700 = b[2];
    v11_1cb700 = b[3];
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf8);
    v12_1cb700 = _vmaddbc(v12_1cb700, 0xF, acc_1cb700, v7_1cb700, v8_1cb700, 1);
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf9);
    v13_1cb700 = _vmaddbc(v13_1cb700, 0xF, acc_1cb700, v7_1cb700, v9_1cb700, 1);
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf10);
    v14_1cb700 = _vmaddbc(v14_1cb700, 0xF, acc_1cb700, v7_1cb700, v10_1cb700, 1);
    Vu0MulMatrixAcc(xyzw, vf4, vf5, vf6, vf11);
    v15_1cb700 = _vmaddbc(v15_1cb700, 0xF, acc_1cb700, v7_1cb700, v11_1cb700, 1);
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    d[0] = v12_1cb700;
    d[1] = v13_1cb700;
    d[2] = v14_1cb700;
    d[3] = v15_1cb700;
}
