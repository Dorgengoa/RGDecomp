/* rgp:protos */
#define RGP_SELF_RayTriIntersectT_1c8d60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047DAB8;
extern f32 D_0047DABC;

f32 RayTriIntersectT_1c8d60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    f32 sp80[4] __attribute__((aligned(16)));
    f32 t;
    f32 v;

    t = VecDot3_1cba90(arg5, arg3);
    if (D_0047DAB8 < t && t < D_0047DABC) {
        return 1.0f;
    }
    v = VecDotDiff_1cba40(arg0, arg4, arg3) / t;
    if (v < 0.0f || 1.0f < v) {
        return 1.0f;
    }
    VecLinearCombine_1cb8b0(sp80, arg5, arg4, v, 1.0f);
    if (TriNormalDot_1cb600(sp80, arg0, arg1, arg3) < 0.0f) {
        return 1.0f;
    }
    if (TriNormalDot_1cb600(sp80, arg1, arg2, arg3) < 0.0f) {
        return 1.0f;
    }
    if (!(TriNormalDot_1cb600(sp80, arg2, arg0, arg3) < 0.0f)) {
        return v;
    }
    return 1.0f;
}
