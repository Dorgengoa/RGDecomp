/* rgp:protos */
#define RGP_SELF_MatMulPointRelMaybe_1cb5d0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb5d0_t; /* rg:vu0bind vf4 */
#define v4_1cb5d0 RG_VU0_BIND_VF(4, rgvb_v4_1cb5d0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb5d0_t; /* rg:vu0bind vf5 */
#define v5_1cb5d0 RG_VU0_BIND_VF(5, rgvb_v5_1cb5d0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb5d0_t; /* rg:vu0bind vf6 */
#define v6_1cb5d0 RG_VU0_BIND_VF(6, rgvb_v6_1cb5d0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cb5d0_t; /* rg:vu0bind vf7 */
#define v7_1cb5d0 RG_VU0_BIND_VF(7, rgvb_v7_1cb5d0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cb5d0_t; /* rg:vu0bind vf8 */
#define v8_1cb5d0 RG_VU0_BIND_VF(8, rgvb_v8_1cb5d0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cb5d0_t; /* rg:vu0bind vf9 */
#define v9_1cb5d0 RG_VU0_BIND_VF(9, rgvb_v9_1cb5d0_t)

typedef u128 __attribute__((aligned(4))) rgvb_vz_1cb5d0_t; /* rg:vu0bind vf0 */
#define vz_1cb5d0 RG_VU0_BIND_VF(0, rgvb_vz_1cb5d0_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb5d0_t; /* rg:vu0bind ACC */
#define acc_1cb5d0 RG_VU0_BIND_ACC(rgvb_acc_1cb5d0_t)


void MatMulPointRelMaybe_1cb5d0(u128 *d, u128 *a, u128 *m, u128 *p)
{ RG_VU0_FRAME;
    v8_1cb5d0 = *p;
    v4_1cb5d0 = m[0];
    v5_1cb5d0 = m[1];
    v6_1cb5d0 = m[2];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v7_1cb5d0 = a[3];
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v8_1cb5d0 = _vsub(v8_1cb5d0, 0xE, v8_1cb5d0, v7_1cb5d0);
    Vu0ApplyMatrix3Acc(xyz, vf4, vf5, vf8);
    v9_1cb5d0 = _vmaddbc(v9_1cb5d0, 0xE, acc_1cb5d0, v6_1cb5d0, v8_1cb5d0, 2);
    v9_1cb5d0 = _vaddbc(v9_1cb5d0, 0x1, vz_1cb5d0, vz_1cb5d0, 8);
    *d = v9_1cb5d0;
}
