/* rgp:protos */
#define RGP_SELF_VecLengthXZ_1cb490 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vf4_1cb490_t; /* rg:vu0bind vf4 */
#define vf4_1cb490 RG_VU0_BIND_VF(4, rgvb_vf4_1cb490_t)


/* sqrt(v.x*v.x + v.z*v.z) */
f32 VecLengthXZ_1cb490(void *v)
{ RG_VU0_FRAME;
    f32 r;
    vf4_1cb490 = *(u128 *)v;
    vf4_1cb490 = _vmul(vf4_1cb490, 0xA, vf4_1cb490, vf4_1cb490);
    vf4_1cb490 = _vaddbc(vf4_1cb490, 0x2, vf4_1cb490, vf4_1cb490, 8);
    Vu0Length(r, z);
    return r;
}
