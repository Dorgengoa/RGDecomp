#include "types.h"

extern f32 TriNormalDot_1cb600(f32 *, s32, s32, s32);
extern void VecLinearCombine_1cb8b0(f32 *, s32, s32, f32, f32);
extern f32 VecDotDiff_1cba40(s32, s32, s32);
extern f32 VecDot3_1cba90(s32, s32);
extern f32 D_0047DAB8;
extern f32 D_0047DABC;

f32 RayTriIntersectT_1c8d60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    f32 sp80[4];
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
