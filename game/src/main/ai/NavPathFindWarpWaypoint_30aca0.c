/* rgp:protos */
#define RGP_SELF_NavPathFindWarpWaypoint_30aca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec { f32 x, y, z, w; } Vec;
typedef struct Par { u8 b[0x30]; } Par;
typedef struct Act { u8 pad0[0x90]; u8 unk90; u8 unk91; } Act;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NavPathFindWarpWaypoint_30aca0(s32 arg0, Act *arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5) {
    Par spF0 __attribute__((aligned(16)));
    Vec spE0 __attribute__((aligned(16)));
    Par spB0 __attribute__((aligned(16)));
    Vec spA0 __attribute__((aligned(16)));
    s32 prev;
    s32 n;
    s32 found;
    s32 cur;
    s32 e;
    s32 m;

    cur = arg3;
    if ((((unsigned char)IsInBattle_288420()) & 0xFF) || NavNodeGetDist_311910(cur) < 700.0f) {
        return 0;
    }
    prev = 0;
    found = 0;
    if (NavGraphGetGoalEdge_310e00(arg2) != 0 && (NavEdgeGetFlags_311710(NavGraphGetGoalEdge_310e00(arg2)) & 0x200000) &&
        ((short)NavNodeGetId_3119c0(cur)) != ((short)NavGraphGetGoalNodeId_310e70(arg2)) &&
        ((short)NavNodeGetPrev_311920(cur)) != ((short)NavEdgeGetNodeA_311700(NavGraphGetGoalEdge_310e00(arg2))) &&
        ((short)NavNodeGetPrev_311920(cur)) != ((short)NavEdgeGetNodeB_3116f0(NavGraphGetGoalEdge_310e00(arg2)))) {
        arg1->unk90 = 0;
        arg1->unk91 = 0;
        m = ((s32)NavGraphGetNode_310cd0(arg2, ((short)NavGraphGetGoalNodeId_310e70(arg2))));
        if (m != 0) {
            NavGraphGetGoalPos_310e30(arg2, &spE0);
            spE0.y += 60.0f;
            NavNodeSetId_3118c0(&spF0, -((short)NavEdgeGetId_311720(NavGraphGetGoalEdge_310e00(arg2))) - 1);
            NavNodeSetPosVec_311890(&spF0, &spE0);
            NavNodeSetFlags_3118a0(&spF0, NavNodeGetFlags_3119a0(m) | 0x20);
            NavNodeSetDist_311850(&spF0, NavNodeGetDist_311910(m));
            NavNodeSetPrev_311860(&spF0, ((short)NavNodeGetPrev_311920(m)));
            NavPathAppendNode_30b020(arg0, arg2, arg1, &spF0, NavEdgeGetFlags_311710(NavGraphGetGoalEdge_310e00(arg2)), arg5);
            return 1;
        }
        return 0;
    }
    n = 0;
    while (cur != 0) {
        if (n >= 2 && (NavNodeGetFlags_3119a0(cur) & 0x10)) {
            e = NavGraphFindEdge_3106e0(arg2, ((short)NavNodeGetId_3119c0(prev)), ((short)NavNodeGetId_3119c0(cur)));
            if (e != 0 && (NavEdgeGetFlags_311710(e) & 0x100000)) {
                found = cur;
            }
        }
        n++;
        prev = cur;
        cur = NavNodeGetPrevNode_310c60(arg2, ((short)NavNodeGetId_3119c0(cur)));
    }
    if (found != 0) {
        arg1->unk90 = 0;
        arg1->unk91 = 0;
        Vec3ToVec4W1_311970(found, &spA0);
        spA0.y += 60.0f;
        NavNodeSetId_3118c0(&spB0, ((short)NavNodeGetId_3119c0(found)));
        NavNodeSetPosVec_311890(&spB0, &spA0);
        NavNodeSetFlags_3118a0(&spB0, NavNodeGetFlags_3119a0(found) | 0x20);
        NavNodeSetDist_311850(&spB0, NavNodeGetDist_311910(found));
        NavNodeSetPrev_311860(&spB0, ((short)NavNodeGetPrev_311920(found)));
        NavPathAppendNode_30b020(arg0, arg2, arg1, &spB0, NavEdgeGetFlags_311710(arg4), arg5);
        return 1;
    }
    return 0;
}
