/* rgp:protos */
#define RGP_SELF_VecMax_1cb5b0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v12_1cb5b0_t; /* rg:vu0bind vf12 */
#define v12_1cb5b0 RG_VU0_BIND_VF(12, rgvb_v12_1cb5b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v13_1cb5b0_t; /* rg:vu0bind vf13 */
#define v13_1cb5b0 RG_VU0_BIND_VF(13, rgvb_v13_1cb5b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v18_1cb5b0_t; /* rg:vu0bind vf18 */
#define v18_1cb5b0 RG_VU0_BIND_VF(18, rgvb_v18_1cb5b0_t)


void VecMax_1cb5b0(u128 *d, u128 *a, u128 *b)
{ RG_VU0_FRAME;
    v12_1cb5b0 = *a;
    v13_1cb5b0 = *b;
    v18_1cb5b0 = _vmax(v18_1cb5b0, 0xF, v12_1cb5b0, v13_1cb5b0);
    *d = v18_1cb5b0;
}
