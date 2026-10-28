/* rgp:protos */
#define RGP_SELF_ClosestPointOnTriWithNormal_1c9ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ClosestPointOnTriWithNormal_1c9ce0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    u8 sp80[0x10] __attribute__((aligned(16)));
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
    VecScale_1cbca0(sp80, arg4, f / VecLengthSq_1cb470(arg4, 0));
    VecSubAsPoint_1cbcc0(arg0, arg5, sp80);
}
