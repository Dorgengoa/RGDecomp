/* rgp:protos */
#define RGP_SELF_DynColliderEllipsoidPushSegmentMaybe_166ba0 1
#include "port/game_protos.h"
#line 1
/* PARK s17d try1: length 0x208 vs retail 0x200, 8 words LONG -- closest
   miss in this batch, worth a second look (possibly outA/outB should share
   one local, or a scalar-per-axis divide differs from a Vec4-field
   divide). */
#include "types.h"
#include "libvu0.h"
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 DynColliderEllipsoidPushSegmentMaybe_166ba0(void *arg0v, Vec4 *arg1, Vec4 *arg2)
{ RG_VU0_FRAME;
    u8 *arg0 = (u8 *)arg0v;
    Vec4 vb __attribute__((aligned(16)));
    Vec4 va __attribute__((aligned(16)));
    Vec4 diff __attribute__((aligned(16)));
    Vec4 closeA __attribute__((aligned(16)));
    Vec4 closeB __attribute__((aligned(16)));
    Vec4 outB __attribute__((aligned(16)));
    Vec4 outA __attribute__((aligned(16)));
    f32 t;

    MtxMulPoint_13c890(&vb, arg0 + 0x50, arg1);
    VecSub_13be40(&vb, &vb, (Vec4 *)(arg0 + 0x120));
    vb.x /= *(f32 *)(arg0 + 0x130);
    vb.y /= *(f32 *)(arg0 + 0x134);
    vb.z /= *(f32 *)(arg0 + 0x138);

    MtxMulPoint_13c890(&va, arg0 + 0x50, arg2);
    VecSub_13be40(&va, &va, (Vec4 *)(arg0 + 0x120));
    va.x /= *(f32 *)(arg0 + 0x130);
    va.y /= *(f32 *)(arg0 + 0x134);
    va.z /= *(f32 *)(arg0 + 0x138);

    Vu0UnitVector(&closeA);
    t = PointSegmentClosest_13dcc0(&closeA, &vb, &va, &closeB);
    if (1.0f > t) {

        VecSub_13be40(&diff, &closeB, &closeA);
        VecScale_13be00(&diff, &diff, 1.0f - t);
        VecAddInPlace_13e070(&vb, &diff);
        VecAddInPlace_13e070(&va, &diff);

        outB.x = vb.x * *(f32 *)(arg0 + 0x130);
        outB.y = vb.y * *(f32 *)(arg0 + 0x134);
        outB.z = vb.z * *(f32 *)(arg0 + 0x138);
        VecAdd_13be20(&outB, &outB, (Vec4 *)(arg0 + 0x120));
        MtxMulPoint_13c890(arg1, arg0 + 0x10, &outB);

        outA.x = va.x * *(f32 *)(arg0 + 0x130);
        outA.y = va.y * *(f32 *)(arg0 + 0x134);
        outA.z = va.z * *(f32 *)(arg0 + 0x138);
        VecAdd_13be20(&outA, &outA, (Vec4 *)(arg0 + 0x120));
        MtxMulPoint_13c890(arg2, arg0 + 0x10, &outA);
        return 1;
    }
    return 0;
}
