/* rgp:protos */
#define RGP_SELF_MtxMulDir_1cb910 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"
typedef rg_u128 u128;
#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb910_t; /* rg:vu0bind vf4 */
#define v4_1cb910 RG_VU0_BIND_VF(4, rgvb_v4_1cb910_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb910_t; /* rg:vu0bind vf5 */
#define v5_1cb910 RG_VU0_BIND_VF(5, rgvb_v5_1cb910_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb910_t; /* rg:vu0bind vf6 */
#define v6_1cb910 RG_VU0_BIND_VF(6, rgvb_v6_1cb910_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cb910_t; /* rg:vu0bind vf8 */
#define v8_1cb910 RG_VU0_BIND_VF(8, rgvb_v8_1cb910_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cb910_t; /* rg:vu0bind vf9 */
#define v9_1cb910 RG_VU0_BIND_VF(9, rgvb_v9_1cb910_t)

typedef u128 __attribute__((aligned(4))) rgvb_acc_1cb910_t; /* rg:vu0bind ACC */
#define acc_1cb910 RG_VU0_BIND_ACC(rgvb_acc_1cb910_t)


void MtxMulDir_1cb910(u128 *d, u128 *m, u128 *v)
{ RG_VU0_FRAME;
    v8_1cb910 = *v;
    v4_1cb910 = m[0];
    v5_1cb910 = m[1];
    v6_1cb910 = m[2];
    Vu0ApplyMatrix3Acc(xyzw, vf4, vf5, vf8);
    v9_1cb910 = _vmaddbc(v9_1cb910, 0xF, acc_1cb910, v6_1cb910, v8_1cb910, 2);
    *d = v9_1cb910;
}
