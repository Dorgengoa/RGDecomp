/* rgp:protos */
#define RGP_SELF_VecNormalize_1cbb80 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbb80_t; /* rg:vu0bind vf0 */
#define vz_1cbb80 RG_VU0_BIND_VF(0, rgvb_vz_1cbb80_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbb80_t; /* rg:vu0bind vf4 */
#define v4_1cbb80 RG_VU0_BIND_VF(4, rgvb_v4_1cbb80_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbb80_t; /* rg:vu0bind vf5 */
#define v5_1cbb80 RG_VU0_BIND_VF(5, rgvb_v5_1cbb80_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbb80_t; /* rg:vu0bind vf6 */
#define v6_1cbb80 RG_VU0_BIND_VF(6, rgvb_v6_1cbb80_t)

typedef float __attribute__((aligned(4))) rgvb_q_1cbb80_t; /* rg:vu0bind Q */
#define q_1cbb80 RG_VU0_BIND_Q(rgvb_q_1cbb80_t)


void VecNormalize_1cbb80(u128 *d, u128 *a)
{ RG_VU0_FRAME;
    v4_1cbb80 = *a;
    v5_1cbb80 = _vmul(v5_1cbb80, 0xE, v4_1cbb80, v4_1cbb80);
    v5_1cbb80 = _vaddbc(v5_1cbb80, 0x8, v5_1cbb80, v5_1cbb80, 4);
    v5_1cbb80 = _vaddbc(v5_1cbb80, 0x8, v5_1cbb80, v5_1cbb80, 2);
    q_1cbb80 = _vsqrt(q_1cbb80, v5_1cbb80, 8);
    v5_1cbb80 = _vaddf(v5_1cbb80, 0x8, vz_1cbb80, q_1cbb80);
    v6_1cbb80 = _vsub(v6_1cbb80, 0x1, vz_1cbb80, vz_1cbb80);
    q_1cbb80 = _vdiv(q_1cbb80, vz_1cbb80, 1, v5_1cbb80, 8);
    v6_1cbb80 = _vmulf(v6_1cbb80, 0xE, v4_1cbb80, q_1cbb80);
    *d = v6_1cbb80;
}
