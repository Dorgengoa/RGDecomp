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

typedef unsigned __int128 u128_185450;

extern u128_185450 v1_185450 asm("vf1");
extern u128_185450 v2_185450 asm("vf2");
extern u128_185450 v10_185450 asm("vf10");
extern u128_185450 v11_185450 asm("vf11");
extern u128_185450 v13_185450 asm("vf13");
extern u128_185450 v14_185450 asm("vf14");
extern u128_185450 v20_185450 asm("vf20");
extern u128_185450 v21_185450 asm("vf21");
extern u128_185450 v22_185450 asm("vf22");
extern float q_185450 asm("Q");

void ClothSolveDistance_185450(Vec4 *p0, Vec4 *p1, f32 a, f32 b)
{
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
