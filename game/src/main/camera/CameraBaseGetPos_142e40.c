/* rgp:protos */
#define RGP_SELF_CameraBaseGetPos_142e40 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz142e40_t; /* rg:vu0bind vf0 */
#define vz142e40 RG_VU0_BIND_VF(0, rgvb_vz142e40_t)

typedef u128 __attribute__((aligned(4))) rgvb_v1_142e40_t; /* rg:vu0bind vf1 */
#define v1_142e40 RG_VU0_BIND_VF(1, rgvb_v1_142e40_t)

typedef u128 __attribute__((aligned(4))) rgvb_v2_142e40_t; /* rg:vu0bind vf2 */
#define v2_142e40 RG_VU0_BIND_VF(2, rgvb_v2_142e40_t)


/* xyz of obj+0x40 -> *dst, keeping dst's w. */
void CameraBaseGetPos_142e40(u8 *obj, u128 *dst)
{ RG_VU0_FRAME;
    v1_142e40 = *(volatile u128 *)dst;
    v2_142e40 = *(volatile u128 *)(obj + 0x40);
    v1_142e40 = _vaddbc(v1_142e40, 0xE, v2_142e40, vz142e40, 8);
    *dst = v1_142e40;
}
