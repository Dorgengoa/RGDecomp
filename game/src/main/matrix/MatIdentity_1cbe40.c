/* rgp:protos */
#define RGP_SELF_MatIdentity_1cbe40 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz1cbe40_t; /* rg:vu0bind vf0 */
#define vz1cbe40 RG_VU0_BIND_VF(0, rgvb_vz1cbe40_t)

typedef u128 __attribute__((aligned(4))) rgvb_v1_1cbe40_t; /* rg:vu0bind vf1 */
#define v1_1cbe40 RG_VU0_BIND_VF(1, rgvb_v1_1cbe40_t)

typedef u128 __attribute__((aligned(4))) rgvb_v2_1cbe40_t; /* rg:vu0bind vf2 */
#define v2_1cbe40 RG_VU0_BIND_VF(2, rgvb_v2_1cbe40_t)

typedef u128 __attribute__((aligned(4))) rgvb_v3_1cbe40_t; /* rg:vu0bind vf3 */
#define v3_1cbe40 RG_VU0_BIND_VF(3, rgvb_v3_1cbe40_t)


/* Unit matrix: rotate vf0 (0,0,0,1) through vf1..vf3, store rows 3..0. */
void MatIdentity_1cbe40(u128 *m)
{ RG_VU0_FRAME;
    v1_1cbe40 = _vmr32(v1_1cbe40, 0xF, vz1cbe40);
    v2_1cbe40 = _vmr32(v2_1cbe40, 0xF, v1_1cbe40);
    v3_1cbe40 = _vmr32(v3_1cbe40, 0xF, v2_1cbe40);
    if (m) {
        m = (u128 *)(s32)(u32)m;
    }
    m[3] = vz1cbe40;
    m[2] = v1_1cbe40;
    m[1] = v2_1cbe40;
    m[0] = v3_1cbe40;
}
