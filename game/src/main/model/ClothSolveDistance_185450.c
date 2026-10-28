/* rgp:protos */
#define RGP_SELF_ClothSolveDistance_185450 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "vec.h"
#include "libvu0.h"

/* Separation-vector push-apart: two points p0/p1 are pushed apart along
   their difference vector until they are >= a apart (b is a secondary
   scale, e.g. an epsilon/response factor), using only the XY-plane
   (vf31 = (1,1,1,1); the vmaddz.x contribution from Z is discarded).
   VU0 macro code as mwcc intrinsics on file-scope register bindings; only
   the vf31 / ACC / bare-mfc1 pieces are the Vu0PushApart* SDK macros
   (include/libvu0.h). Same shape as VecNormalize_13bd90/QuatSlerp_13c270. */

#pragma vu0_mmi_reg_binding on

typedef rg_u128 u128_185450;

typedef u128_185450 __attribute__((aligned(4))) rgvb_v1_185450_t; /* rg:vu0bind vf1 */
#define v1_185450 RG_VU0_BIND_VF(1, rgvb_v1_185450_t)

typedef u128_185450 __attribute__((aligned(4))) rgvb_v2_185450_t; /* rg:vu0bind vf2 */
#define v2_185450 RG_VU0_BIND_VF(2, rgvb_v2_185450_t)

typedef u128_185450 __attribute__((aligned(4))) rgvb_v10_185450_t; /* rg:vu0bind vf10 */
#define v10_185450 RG_VU0_BIND_VF(10, rgvb_v10_185450_t)

typedef u128_185450 __attribute__((aligned(4))) rgvb_v11_185450_t; /* rg:vu0bind vf11 */
#define v11_185450 RG_VU0_BIND_VF(11, rgvb_v11_185450_t)

typedef u128_185450 __attribute__((aligned(4))) rgvb_v13_185450_t; /* rg:vu0bind vf13 */
#define v13_185450 RG_VU0_BIND_VF(13, rgvb_v13_185450_t)

typedef u128_185450 __attribute__((aligned(4))) rgvb_v14_185450_t; /* rg:vu0bind vf14 */
#define v14_185450 RG_VU0_BIND_VF(14, rgvb_v14_185450_t)

typedef u128_185450 __attribute__((aligned(4))) rgvb_v20_185450_t; /* rg:vu0bind vf20 */
#define v20_185450 RG_VU0_BIND_VF(20, rgvb_v20_185450_t)

typedef u128_185450 __attribute__((aligned(4))) rgvb_v21_185450_t; /* rg:vu0bind vf21 */
#define v21_185450 RG_VU0_BIND_VF(21, rgvb_v21_185450_t)

typedef u128_185450 __attribute__((aligned(4))) rgvb_v22_185450_t; /* rg:vu0bind vf22 */
#define v22_185450 RG_VU0_BIND_VF(22, rgvb_v22_185450_t)

typedef float __attribute__((aligned(4))) rgvb_q_185450_t; /* rg:vu0bind Q */
#define q_185450 RG_VU0_BIND_Q(rgvb_q_185450_t)


void ClothSolveDistance_185450(Vec4 *p0, Vec4 *p1, f32 a, f32 b)
{ RG_VU0_FRAME;
    v10_185450 = *(u128_185450 *)p0;
    v11_185450 = *(u128_185450 *)p1;
    Vu0PushApartOne();
    v1_185450 = _vsub(v1_185450, 0xF, v10_185450, v11_185450);
    v2_185450 = _vmul(v2_185450, 0xE, v1_185450, v1_185450);
    Vu0PushApartLen(a, b);
    Vu0PushApartRsqrt();
    q_185450 = _vwaitq(q_185450);
    Vu0PushApartSubQ();
    v13_185450 = _vmul(v13_185450, 8, v13_185450, v20_185450);
    v14_185450 = _vmul(v14_185450, 8, v14_185450, v20_185450);
    v21_185450 = _vmulbc(v21_185450, 0xF, v1_185450, v13_185450, 8);
    v22_185450 = _vmulbc(v22_185450, 0xF, v1_185450, v14_185450, 8);
    v10_185450 = _vsub(v10_185450, 0xF, v10_185450, v21_185450);
    v11_185450 = _vadd(v11_185450, 0xF, v11_185450, v22_185450);
    if (p0) {
        p0 = (Vec4 *)(s32)(u32)p0;
    }
    *(u128_185450 *)p0 = v10_185450;
    *(u128_185450 *)p1 = v11_185450;
}
