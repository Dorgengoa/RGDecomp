/* rgp:protos */
#define RGP_SELF_CameraBaseSetPos_154520 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz154520_t; /* rg:vu0bind vf0 */
#define vz154520 RG_VU0_BIND_VF(0, rgvb_vz154520_t)

typedef u128 __attribute__((aligned(4))) rgvb_v1_154520_t; /* rg:vu0bind vf1 */
#define v1_154520 RG_VU0_BIND_VF(1, rgvb_v1_154520_t)

typedef u128 __attribute__((aligned(4))) rgvb_v2_154520_t; /* rg:vu0bind vf2 */
#define v2_154520 RG_VU0_BIND_VF(2, rgvb_v2_154520_t)


/* xyz of *src -> obj+0x40, keeping its w. */
void CameraBaseSetPos_154520(u8 *obj, u128 *src)
{ RG_VU0_FRAME;
    v1_154520 = *(volatile u128 *)(obj + 0x40);
    v2_154520 = *(volatile u128 *)src;
    v1_154520 = _vaddbc(v1_154520, 0xE, v2_154520, vz154520, 8);
    *(u128 *)(obj + 0x40) = v1_154520;
}
