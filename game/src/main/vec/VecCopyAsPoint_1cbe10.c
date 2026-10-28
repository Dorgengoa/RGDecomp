/* rgp:protos */
#define RGP_SELF_VecCopyAsPoint_1cbe10 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbe10_t; /* rg:vu0bind vf0 */
#define vz_1cbe10 RG_VU0_BIND_VF(0, rgvb_vz_1cbe10_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbe10_t; /* rg:vu0bind vf4 */
#define v4_1cbe10 RG_VU0_BIND_VF(4, rgvb_v4_1cbe10_t)


void VecCopyAsPoint_1cbe10(u128 *d, u128 *s)
{ RG_VU0_FRAME;
    v4_1cbe10 = *s;
    v4_1cbe10 = _vmul(v4_1cbe10, 0x1, vz_1cbe10, vz_1cbe10);
    *d = v4_1cbe10;
}
