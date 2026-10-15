/* PARK s17d try1: 132 words, 33 bad (same length as retail). */
#include "types.h"
#include "vec.h"

extern void ClosestPointOnSegment_1c9f60(Vec4 *, Vec4 *, Vec4 *, Vec4 *);
extern f32 VecDistSq_1cb3c0(Vec4 *, Vec4 *);
extern void VecCopy_1cbe30(Vec4 *, Vec4 *);
extern s32 PointNearSegmentAabb_310620(s32, Vec4 *, Vec4 *, Vec4 *, f32);
extern u32 NavGraphGetEdgeCount_310c00(s32);
extern s32 NavGraphGetEdges_310c10(s32);
extern s32 NavGraphGetNode_310cd0(s32, s32);
extern void NavXformPointToWorld_310d10(s32, Vec4 *, Vec4 *);
extern void NavXformPointToLocal_310d50(s32, Vec4 *, Vec4 *);
extern s32 NavEdgeGetNodeB_3116f0(s32);
extern s32 NavEdgeGetNodeA_311700(s32);
extern void Vec3ToVec4W1_311970(s32, Vec4 *);
extern s32 NavNodeGetFlags_3119a0(s32);
extern u8 D_0045B080[0x400];

s32 NavFindNearestCenterEdgePoint_30fe80(s32 arg0, Vec4 *arg1, Vec4 *arg2, s32 arg3)
{
    Vec4 spE0;
    Vec4 spD0;
    Vec4 spC0;
    Vec4 spB0;
    f32 temp_f0;
    f32 best;
    u32 n;
    s32 best_idx;
    s32 i;
    u32 idx;
    s32 mode;
    s32 a;
    s32 b;

    if (NavGraphGetEdges_310c10(arg0) == 0) {
        return 0;
    }
    mode = arg3 & 0xFF;
    if (mode == 0) {
        NavXformPointToLocal_310d50(arg0, &spE0, arg2);
    } else {
        VecCopy_1cbe30(&spE0, arg2);
    }
    best_idx = 0;
    i = NavGraphGetEdges_310c10(arg0);
    best = (f32)0xF4240 * (*(f32 *)D_0045B080);
    n = NavGraphGetEdgeCount_310c00(arg0);
    idx = 0;
    while (idx < n) {
        a = NavGraphGetNode_310cd0(arg0, NavEdgeGetNodeA_311700(i));
        if (a != 0) {
            b = NavGraphGetNode_310cd0(arg0, NavEdgeGetNodeB_3116f0(i));
            if (b != 0 && (NavNodeGetFlags_3119a0(a) & 1) && (NavNodeGetFlags_3119a0(b) & 1)) {
                Vec3ToVec4W1_311970(a, &spD0);
                Vec3ToVec4W1_311970(b, &spC0);
                if (PointNearSegmentAabb_310620(arg0, &spE0, &spD0, &spC0, best) & 0xFF) {
                    ClosestPointOnSegment_1c9f60(&spB0, &spD0, &spC0, &spE0);
                    temp_f0 = VecDistSq_1cb3c0(&spB0, &spE0);
                    if (temp_f0 < best) {
                        VecCopy_1cbe30(arg1, &spB0);
                        best = temp_f0;
                        best_idx = i;
                    }
                }
            }
        }
        idx += 1;
        i += 0x14;
    }
    if (mode == 0) {
        NavXformPointToWorld_310d10(arg0, arg1, arg1);
    }
    return best_idx;
}
