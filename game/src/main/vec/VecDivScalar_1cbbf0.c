/* rgp:protos */
#define RGP_SELF_VecDivScalar_1cbbf0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbbf0_t; /* rg:vu0bind vf0 */
#define vz_1cbbf0 RG_VU0_BIND_VF(0, rgvb_vz_1cbbf0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbbf0_t; /* rg:vu0bind vf4 */
#define v4_1cbbf0 RG_VU0_BIND_VF(4, rgvb_v4_1cbbf0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbbf0_t; /* rg:vu0bind vf5 */
#define v5_1cbbf0 RG_VU0_BIND_VF(5, rgvb_v5_1cbbf0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbbf0_t; /* rg:vu0bind vf6 */
#define v6_1cbbf0 RG_VU0_BIND_VF(6, rgvb_v6_1cbbf0_t)

typedef float __attribute__((aligned(4))) rgvb_q_1cbbf0_t; /* rg:vu0bind Q */
#define q_1cbbf0 RG_VU0_BIND_Q(rgvb_q_1cbbf0_t)


/* d = a / s */
void VecDivScalar_1cbbf0(u128 *d, u128 *a, f32 s)
{ RG_VU0_FRAME;
    Vu0ScaleF(a1, s, vf5);
    v4_1cbbf0 = *a;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    q_1cbbf0 = _vdiv(q_1cbbf0, vz_1cbbf0, 1, v5_1cbbf0, 8);
    v6_1cbbf0 = _vmulf(v6_1cbbf0, 0xF, v4_1cbbf0, q_1cbbf0);
    *d = v6_1cbbf0;
}

