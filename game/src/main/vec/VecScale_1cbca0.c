/* rgp:protos */
#define RGP_SELF_VecScale_1cbca0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbca0_t; /* rg:vu0bind vf4 */
#define v4_1cbca0 RG_VU0_BIND_VF(4, rgvb_v4_1cbca0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbca0_t; /* rg:vu0bind vf5 */
#define v5_1cbca0 RG_VU0_BIND_VF(5, rgvb_v5_1cbca0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbca0_t; /* rg:vu0bind vf6 */
#define v6_1cbca0 RG_VU0_BIND_VF(6, rgvb_v6_1cbca0_t)


/* d = a * s (Sony-style sceVu0ScaleVector) */
void VecScale_1cbca0(u128 *d, u128 *a, f32 s)
{ RG_VU0_FRAME;
    Vu0ScaleF(t0, s, vf5);
    v4_1cbca0 = *a;
    v6_1cbca0 = _vmulbc(v6_1cbca0, 0xF, v4_1cbca0, v5_1cbca0, 8);
    *d = v6_1cbca0;
}
