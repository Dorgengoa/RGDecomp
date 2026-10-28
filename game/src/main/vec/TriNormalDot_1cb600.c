/* rgp:protos */
#define RGP_SELF_TriNormalDot_1cb600 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb600_t; /* rg:vu0bind vf4 */
#define v4_1cb600 RG_VU0_BIND_VF(4, rgvb_v4_1cb600_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb600_t; /* rg:vu0bind vf5 */
#define v5_1cb600 RG_VU0_BIND_VF(5, rgvb_v5_1cb600_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb600_t; /* rg:vu0bind vf6 */
#define v6_1cb600 RG_VU0_BIND_VF(6, rgvb_v6_1cb600_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cb600_t; /* rg:vu0bind vf7 */
#define v7_1cb600 RG_VU0_BIND_VF(7, rgvb_v7_1cb600_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cb600_t; /* rg:vu0bind vf8 */
#define v8_1cb600 RG_VU0_BIND_VF(8, rgvb_v8_1cb600_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb600_t; /* rg:vu0bind ACC */
#define acc_1cb600 RG_VU0_BIND_ACC(rgvb_acc_1cb600_t)


#pragma optimization_level 1
#pragma schedule on
#pragma opt_common_subs on

f32 TriNormalDot_1cb600(u128 *a, u128 *b, u128 *c, u128 *n)
{ RG_VU0_FRAME;
    f32 r;

    v7_1cb600 = *(volatile u128 *)n;
    v6_1cb600 = *(volatile u128 *)c;
    v5_1cb600 = *(volatile u128 *)b;
    v4_1cb600 = *(volatile u128 *)a;
    if (c) { a = (u128 *)(s32)(u32)a; }
    _vsub(v6_1cb600, 0xF, v6_1cb600, v5_1cb600);
    _vsub(v5_1cb600, 0xF, v5_1cb600, v4_1cb600);
    Vu0OuterProductAcc(vf5, vf6);
    _vopmsub(v8_1cb600, acc_1cb600, v6_1cb600, v5_1cb600);
    _vmul(v8_1cb600, 0xE, v8_1cb600, v7_1cb600);
    _vaddbc(v8_1cb600, 0x8, v8_1cb600, v8_1cb600, 4);
    _vaddbc(v8_1cb600, 0x8, v8_1cb600, v8_1cb600, 2);
    b = *(u128 **)&v8_1cb600;
    r = *(f32 *)&v8_1cb600;
    if (a) { r = -(-r); }
    if (b) { r = -(-r); }
    return r;
}
