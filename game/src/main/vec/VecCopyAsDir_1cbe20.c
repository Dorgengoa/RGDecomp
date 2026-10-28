/* rgp:protos */
#define RGP_SELF_VecCopyAsDir_1cbe20 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz1cbe20_t; /* rg:vu0bind vf0 */
#define vz1cbe20 RG_VU0_BIND_VF(0, rgvb_vz1cbe20_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbe20_t; /* rg:vu0bind vf4 */
#define v4_1cbe20 RG_VU0_BIND_VF(4, rgvb_v4_1cbe20_t)


/* Copy a vector with w forced to 0.0f (vf0.w - vf0.w). */
void VecCopyAsDir_1cbe20(u128 *dst, u128 *src)
{ RG_VU0_FRAME;
    v4_1cbe20 = *src;
    v4_1cbe20 = _vsub(v4_1cbe20, 0x1, vz1cbe20, vz1cbe20);
    *dst = v4_1cbe20;
}
