/* rgp:protos */
#define RGP_SELF_VecNormalizeXZ_1cbb50 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbb50_t; /* rg:vu0bind vf0 */
#define vz_1cbb50 RG_VU0_BIND_VF(0, rgvb_vz_1cbb50_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbb50_t; /* rg:vu0bind vf4 */
#define v4_1cbb50 RG_VU0_BIND_VF(4, rgvb_v4_1cbb50_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbb50_t; /* rg:vu0bind vf5 */
#define v5_1cbb50 RG_VU0_BIND_VF(5, rgvb_v5_1cbb50_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbb50_t; /* rg:vu0bind vf6 */
#define v6_1cbb50 RG_VU0_BIND_VF(6, rgvb_v6_1cbb50_t)

typedef float __attribute__((aligned(4))) rgvb_q_1cbb50_t; /* rg:vu0bind Q */
#define q_1cbb50 RG_VU0_BIND_Q(rgvb_q_1cbb50_t)


void VecNormalizeXZ_1cbb50(u128 *d, u128 *a)
{ RG_VU0_FRAME;
    v4_1cbb50 = *a;
    v5_1cbb50 = _vmul(v5_1cbb50, 0xE, v4_1cbb50, v4_1cbb50);
    v5_1cbb50 = _vaddbc(v5_1cbb50, 0x2, v5_1cbb50, v5_1cbb50, 8);
    q_1cbb50 = _vsqrt(q_1cbb50, v5_1cbb50, 2);
    v5_1cbb50 = _vaddf(v5_1cbb50, 0x8, vz_1cbb50, q_1cbb50);
    v6_1cbb50 = _vsub(v6_1cbb50, 0x5, vz_1cbb50, vz_1cbb50);
    q_1cbb50 = _vdiv(q_1cbb50, vz_1cbb50, 1, v5_1cbb50, 8);
    v6_1cbb50 = _vmulf(v6_1cbb50, 0xA, v4_1cbb50, q_1cbb50);
    *d = v6_1cbb50;
}
