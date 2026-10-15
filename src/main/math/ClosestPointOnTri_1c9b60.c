#include "types.h"

extern void ClosestPointOnTriEdges_1ca060(s32, s32, s32, s32, s32, s32);
extern f32 VecLengthSq_1cb470(void *);
extern f32 TriNormalDot_1cb600(s32, s32, s32, void *);
extern void TriNormal_1cb970(void *);
extern f32 VecDotDiff_1cba40(s32, s32, void *);
extern void VecScale_1cbca0(void *, void *, f32);
extern void VecSubAsPoint_1cbcc0(s32, s32, void *);

void ClosestPointOnTri_1c9b60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u8 sp80[0x10];
    u8 sp70[0x10];
    f32 temp_f20;

    TriNormal_1cb970(sp80);
    if (TriNormalDot_1cb600(arg4, arg1, arg2, sp80) < 0.0f) {
        ClosestPointOnTriEdges_1ca060(arg0, arg3, arg1, arg2, arg3, arg4);
        return;
    }
    if (TriNormalDot_1cb600(arg4, arg2, arg3, sp80) < 0.0f) {
        ClosestPointOnTriEdges_1ca060(arg0, arg1, arg2, arg3, arg1, arg4);
        return;
    }
    if (TriNormalDot_1cb600(arg4, arg3, arg1, sp80) < 0.0f) {
        ClosestPointOnTriEdges_1ca060(arg0, arg2, arg3, arg1, arg2, arg4);
        return;
    }
    temp_f20 = VecDotDiff_1cba40(arg4, arg1, sp80);
    VecScale_1cbca0(sp70, sp80, temp_f20 / VecLengthSq_1cb470(sp80));
    VecSubAsPoint_1cbcc0(arg0, arg4, sp70);
}
