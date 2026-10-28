/* rgp:protos */
#define RGP_SELF_VecScaleToLength_1cb510 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb510_t; /* rg:vu0bind vf4 */
#define v4_1cb510 RG_VU0_BIND_VF(4, rgvb_v4_1cb510_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb510_t; /* rg:vu0bind vf5 */
#define v5_1cb510 RG_VU0_BIND_VF(5, rgvb_v5_1cb510_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb510_t; /* rg:vu0bind vf6 */
#define v6_1cb510 RG_VU0_BIND_VF(6, rgvb_v6_1cb510_t)

typedef float __attribute__((aligned(4))) rgvb_q_1cb510_t; /* rg:vu0bind Q */
#define q_1cb510 RG_VU0_BIND_Q(rgvb_q_1cb510_t)


/* d = a * (s / |a|)   (scale vector to length s) */
void VecScaleToLength_1cb510(u128 *d, u128 *a, f32 s)
{ RG_VU0_FRAME;
    v4_1cb510 = *a;
    Vu0ScaleF(a1, s, vf5);
    v6_1cb510 = _vmul(v6_1cb510, 0xF, v4_1cb510, v4_1cb510);
    v6_1cb510 = _vaddbc(v6_1cb510, 0x8, v6_1cb510, v6_1cb510, 4);
    v6_1cb510 = _vaddbc(v6_1cb510, 0x8, v6_1cb510, v6_1cb510, 2);
    q_1cb510 = _vrsqrt(q_1cb510, v5_1cb510, 8, v6_1cb510, 8);
    v4_1cb510 = _vmulf(v4_1cb510, 0xF, v4_1cb510, q_1cb510);
    *d = v4_1cb510;
}
