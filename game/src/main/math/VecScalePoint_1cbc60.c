/* rgp:protos */
#define RGP_SELF_VecScalePoint_1cbc60 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cbc60_t; /* rg:vu0bind vf0 */
#define vz_1cbc60 RG_VU0_BIND_VF(0, rgvb_vz_1cbc60_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbc60_t; /* rg:vu0bind vf4 */
#define v4_1cbc60 RG_VU0_BIND_VF(4, rgvb_v4_1cbc60_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbc60_t; /* rg:vu0bind vf5 */
#define v5_1cbc60 RG_VU0_BIND_VF(5, rgvb_v5_1cbc60_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cbc60_t; /* rg:vu0bind vf6 */
#define v6_1cbc60 RG_VU0_BIND_VF(6, rgvb_v6_1cbc60_t)


/* d.xyz = a.xyz * s, d.w = 1 */
void VecScalePoint_1cbc60(u128 *d, u128 *a, f32 s)
{ RG_VU0_FRAME;
    Vu0ScaleF(t0, s, vf5);
    v4_1cbc60 = *a;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v6_1cbc60 = _vmul(v6_1cbc60, 0x1, vz_1cbc60, vz_1cbc60);
    v6_1cbc60 = _vmulbc(v6_1cbc60, 0xE, v4_1cbc60, v5_1cbc60, 8);
    *d = v6_1cbc60;
}
