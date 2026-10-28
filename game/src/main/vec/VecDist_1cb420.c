/* rgp:protos */
#define RGP_SELF_VecDist_1cb420 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vf4_1cb420_t; /* rg:vu0bind vf4 */
#define vf4_1cb420 RG_VU0_BIND_VF(4, rgvb_vf4_1cb420_t)

typedef u128 __attribute__((aligned(4))) rgvb_vf5_1cb420_t; /* rg:vu0bind vf5 */
#define vf5_1cb420 RG_VU0_BIND_VF(5, rgvb_vf5_1cb420_t)


/* xyz distance |a - b| */
f32 VecDist_1cb420(void *a, void *b)
{ RG_VU0_FRAME;
    f32 r;
    vf4_1cb420 = *(u128 *)a;
    vf5_1cb420 = *(u128 *)b;
    vf4_1cb420 = _vsub(vf4_1cb420, 0xE, vf4_1cb420, vf5_1cb420);
    vf4_1cb420 = _vmul(vf4_1cb420, 0xE, vf4_1cb420, vf4_1cb420);
    vf4_1cb420 = _vaddbc(vf4_1cb420, 0x8, vf4_1cb420, vf4_1cb420, 4);
    vf4_1cb420 = _vaddbc(vf4_1cb420, 0x8, vf4_1cb420, vf4_1cb420, 2);
    Vu0Length(r, x);
    return r;
}
