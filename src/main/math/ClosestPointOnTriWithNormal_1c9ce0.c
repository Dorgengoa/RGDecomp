#include "types.h"

void ClosestPointOnTriEdges_1ca060(s32, s32, s32, s32, s32, s32);
f32 VecLengthSq_1cb470(s32);
f32 TriNormalDot_1cb600(s32, s32, s32, s32);
f32 VecDotDiff_1cba40(s32, s32, s32);
void VecScale_1cbca0(void *, s32, f32);
void VecSubAsPoint_1cbcc0(s32, s32, void *);

void ClosestPointOnTriWithNormal_1c9ce0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    u8 sp80[0x10];
    f32 f;
    s32 u;

    if (TriNormalDot_1cb600(arg5, arg1, arg2, arg4) < 0.0f) {
        ClosestPointOnTriEdges_1ca060(arg0, arg3, arg1, arg2, arg3, arg5);
        return;
    }
    if (TriNormalDot_1cb600(arg5, arg2, arg3, arg4) < 0.0f) {
        ClosestPointOnTriEdges_1ca060(arg0, arg1, arg2, arg3, arg1, arg5);
        return;
    }
    if (TriNormalDot_1cb600(arg5, arg3, arg1, arg4) < 0.0f) {
        ClosestPointOnTriEdges_1ca060(arg0, arg2, arg3, arg1, arg2, arg5);
        return;
    }
    f = VecDotDiff_1cba40(arg5, arg1, arg4);
    VecScale_1cbca0(sp80, arg4, f / VecLengthSq_1cb470(arg4));
    VecSubAsPoint_1cbcc0(arg0, arg5, sp80);
}
