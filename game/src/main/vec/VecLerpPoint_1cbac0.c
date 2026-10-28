/* rgp:protos */
#define RGP_SELF_VecLerpPoint_1cbac0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbac0_t; /* rg:vu0bind vf0 */
#define vz_1cbac0 RG_VU0_BIND_VF(0, rgvb_vz_1cbac0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbac0_t; /* rg:vu0bind vf4 */
#define v4_1cbac0 RG_VU0_BIND_VF(4, rgvb_v4_1cbac0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbac0_t; /* rg:vu0bind vf5 */
#define v5_1cbac0 RG_VU0_BIND_VF(5, rgvb_v5_1cbac0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbac0_t; /* rg:vu0bind vf6 */
#define v6_1cbac0 RG_VU0_BIND_VF(6, rgvb_v6_1cbac0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cbac0_t; /* rg:vu0bind vf7 */
#define v7_1cbac0 RG_VU0_BIND_VF(7, rgvb_v7_1cbac0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cbac0_t; /* rg:vu0bind vf8 */
#define v8_1cbac0 RG_VU0_BIND_VF(8, rgvb_v8_1cbac0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cbac0_t; /* rg:vu0bind vf9 */
#define v9_1cbac0 RG_VU0_BIND_VF(9, rgvb_v9_1cbac0_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cbac0_t; /* rg:vu0bind ACC */
#define acc_1cbac0 RG_VU0_BIND_ACC(rgvb_acc_1cbac0_t)


void VecLerpPoint_1cbac0(u128 *d, u128 *a, u128 *b, f32 t)
{ RG_VU0_FRAME;
    v4_1cbac0 = *a;
    v5_1cbac0 = *b;
    Vu0ScaleF(a1, t, vf6);
    v7_1cbac0 = _vaddbc(v7_1cbac0, 0x8, vz_1cbac0, vz_1cbac0, 1);
    v8_1cbac0 = _vsub(v8_1cbac0, 0x8, v7_1cbac0, v6_1cbac0);
    Vu0MulAccX(xyz, vf4, vf6);
    v9_1cbac0 = _vmaddbc(v9_1cbac0, 0xE, acc_1cbac0, v5_1cbac0, v8_1cbac0, 8);
    v9_1cbac0 = _vmul(v9_1cbac0, 0x1, vz_1cbac0, vz_1cbac0);
    *d = v9_1cbac0;
}
