/* rgp:protos */
#define RGP_SELF_VecScaleDir_1cbc80 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbc80_t; /* rg:vu0bind vf0 */
#define vz_1cbc80 RG_VU0_BIND_VF(0, rgvb_vz_1cbc80_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbc80_t; /* rg:vu0bind vf4 */
#define v4_1cbc80 RG_VU0_BIND_VF(4, rgvb_v4_1cbc80_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbc80_t; /* rg:vu0bind vf5 */
#define v5_1cbc80 RG_VU0_BIND_VF(5, rgvb_v5_1cbc80_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbc80_t; /* rg:vu0bind vf6 */
#define v6_1cbc80 RG_VU0_BIND_VF(6, rgvb_v6_1cbc80_t)


/* d.xyz = a.xyz * s, d.w = 0 */
void VecScaleDir_1cbc80(u128 *d, u128 *a, f32 s)
{ RG_VU0_FRAME;
    Vu0ScaleF(t0, s, vf5);
    v4_1cbc80 = *a;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cbc80 = _vsub(v6_1cbc80, 0x1, vz_1cbc80, vz_1cbc80);
    v6_1cbc80 = _vmulbc(v6_1cbc80, 0xE, v4_1cbc80, v5_1cbc80, 8);
    *d = v6_1cbc80;
}
