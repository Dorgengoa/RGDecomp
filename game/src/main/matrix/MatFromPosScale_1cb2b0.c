/* rgp:protos */
#define RGP_SELF_MatFromPosScale_1cb2b0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "libvu0.h"

typedef rg_u128 u128;

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz_1cb2b0_t; /* rg:vu0bind vf0 */
#define vz_1cb2b0 RG_VU0_BIND_VF(0, rgvb_vz_1cb2b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb2b0_t; /* rg:vu0bind vf4 */
#define v4_1cb2b0 RG_VU0_BIND_VF(4, rgvb_v4_1cb2b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb2b0_t; /* rg:vu0bind vf5 */
#define v5_1cb2b0 RG_VU0_BIND_VF(5, rgvb_v5_1cb2b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v6_1cb2b0_t; /* rg:vu0bind vf6 */
#define v6_1cb2b0 RG_VU0_BIND_VF(6, rgvb_v6_1cb2b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v7_1cb2b0_t; /* rg:vu0bind vf7 */
#define v7_1cb2b0 RG_VU0_BIND_VF(7, rgvb_v7_1cb2b0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cb2b0_t; /* rg:vu0bind vf9 */
#define v9_1cb2b0 RG_VU0_BIND_VF(9, rgvb_v9_1cb2b0_t)


/* d = scale(s) with translation row src.xyz, w = 1 */
void MatFromPosScale_1cb2b0(u128 *d, u128 *src, f32 s)
{ RG_VU0_FRAME;
    Vu0ScaleF(a1, s, vf9);
    v7_1cb2b0 = *src;
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    v4_1cb2b0 = _vsub(v4_1cb2b0, 0xF, vz_1cb2b0, vz_1cb2b0);
    v5_1cb2b0 = _vsub(v5_1cb2b0, 0xF, vz_1cb2b0, vz_1cb2b0);
    v6_1cb2b0 = _vsub(v6_1cb2b0, 0xF, vz_1cb2b0, vz_1cb2b0);
    v4_1cb2b0 = _vaddbc(v4_1cb2b0, 0x8, v4_1cb2b0, v9_1cb2b0, 8);
    v5_1cb2b0 = _vaddbc(v5_1cb2b0, 0x4, v5_1cb2b0, v9_1cb2b0, 8);
    v6_1cb2b0 = _vaddbc(v6_1cb2b0, 0x2, v6_1cb2b0, v9_1cb2b0, 8);
    v7_1cb2b0 = _vmul(v7_1cb2b0, 0x1, vz_1cb2b0, vz_1cb2b0);
    if (d) {
        d = (u128 *)(s32)(u32)d;
    }
    d[0] = v4_1cb2b0;
    d[1] = v5_1cb2b0;
    d[2] = v6_1cb2b0;
    d[3] = v7_1cb2b0;
}
