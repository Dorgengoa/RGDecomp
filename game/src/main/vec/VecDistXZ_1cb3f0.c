/* rgp:protos */
#define RGP_SELF_VecDistXZ_1cb3f0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vf4_1cb3f0_t; /* rg:vu0bind vf4 */
#define vf4_1cb3f0 RG_VU0_BIND_VF(4, rgvb_vf4_1cb3f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_vf5_1cb3f0_t; /* rg:vu0bind vf5 */
#define vf5_1cb3f0 RG_VU0_BIND_VF(5, rgvb_vf5_1cb3f0_t)


/* xz distance |a - b| */
f32 VecDistXZ_1cb3f0(void *a, void *b)
{ RG_VU0_FRAME;
    f32 r;
    vf4_1cb3f0 = *(u128 *)a;
    vf5_1cb3f0 = *(u128 *)b;
    vf4_1cb3f0 = _vsub(vf4_1cb3f0, 0xA, vf4_1cb3f0, vf5_1cb3f0);
    vf4_1cb3f0 = _vmul(vf4_1cb3f0, 0xA, vf4_1cb3f0, vf4_1cb3f0);
    vf4_1cb3f0 = _vaddbc(vf4_1cb3f0, 0x2, vf4_1cb3f0, vf4_1cb3f0, 8);
    Vu0Length(r, z);
    return r;
}
