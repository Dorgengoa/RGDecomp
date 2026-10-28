/* rgp:protos */
#define RGP_SELF_VecLength_1cb4c0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vf4_1cb4c0_t; /* rg:vu0bind vf4 */
#define vf4_1cb4c0 RG_VU0_BIND_VF(4, rgvb_vf4_1cb4c0_t)


/* |v.xyz| */
f32 VecLength_1cb4c0(void *v)
{ RG_VU0_FRAME;
    f32 r;
    vf4_1cb4c0 = *(u128 *)v;
    vf4_1cb4c0 = _vmul(vf4_1cb4c0, 0xE, vf4_1cb4c0, vf4_1cb4c0);
    vf4_1cb4c0 = _vaddbc(vf4_1cb4c0, 0x8, vf4_1cb4c0, vf4_1cb4c0, 4);
    vf4_1cb4c0 = _vaddbc(vf4_1cb4c0, 0x8, vf4_1cb4c0, vf4_1cb4c0, 2);
    Vu0Length(r, x);
    return r;
}
