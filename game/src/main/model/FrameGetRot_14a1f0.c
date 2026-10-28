/* rgp:protos */
#define RGP_SELF_FrameGetRot_14a1f0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz14a1f0_t; /* rg:vu0bind vf0 */
#define vz14a1f0 RG_VU0_BIND_VF(0, rgvb_vz14a1f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v1_14a1f0_t; /* rg:vu0bind vf1 */
#define v1_14a1f0 RG_VU0_BIND_VF(1, rgvb_v1_14a1f0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v2_14a1f0_t; /* rg:vu0bind vf2 */
#define v2_14a1f0 RG_VU0_BIND_VF(2, rgvb_v2_14a1f0_t)


/* dst.xyz = obj->+0x18 vector's xyz (dst.w kept), or clear dst when null. */
void FrameGetRot_14a1f0(u8 *obj, u128 *dst)
{ RG_VU0_FRAME;
    u128 *src = *(u128 **)(obj + 0x18);
    if (src != 0) {
        v1_14a1f0 = *(volatile u128 *)dst;
        v2_14a1f0 = *(volatile u128 *)src;
        v1_14a1f0 = _vaddbc(v1_14a1f0, 0xE, v2_14a1f0, vz14a1f0, 8);
        *dst = v1_14a1f0;
    } else {
        *dst = 0;
    }
}
