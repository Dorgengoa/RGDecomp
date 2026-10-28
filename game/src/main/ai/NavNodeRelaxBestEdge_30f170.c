/* rgp:protos */
#define RGP_SELF_NavNodeRelaxBestEdge_30f170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
extern f32 D_0045B080[4];

s32 NavNodeRelaxBestEdge_30f170(s32 arg0, s32 arg1)
{
    s32 t;
    s16 *ids;
    s32 best;
    s32 bestb;
    s32 i;
    f32 min;
    s32 a;
    s32 b;

    if (arg1 == 0 || ((s16 *)NavNodeGetEdgeList_311940(arg1)) == NULL) {
        return 0;
    }
    if (((short)NavNodeGetReachable_311960(arg1)) != 0 && ((short)NavNodeGetPrev_311920(arg1)) >= 0) {
        t = ((short)NavNodeGetId_3119c0(arg1));
        return NavGraphFindEdge_3106e0(arg0, t, ((short)NavNodeGetId_3119c0(((s32)NavGraphGetNode_310cd0(arg0, ((short)NavNodeGetPrev_311920(arg1)))))));
    }
    ids = ((s16 *)NavNodeGetEdgeList_311940(arg1));
    best = 0;
    bestb = 0;
    min = (f32)1000000 * D_0045B080[0];
    i = 0;
    for (; i < ((short)NavNodeGetEdgeCount_311930(arg1)); i++, ids++) {
        a = ((s32)NavGraphGetEdge_310c20(arg0, *ids));
        if (a == 0) {
            return 0;
        }
        b = ((s32)NavGraphGetNode_310cd0(arg0, NavEdgeGetOtherNode_3116b0(a, ((short)NavNodeGetId_3119c0(arg1)))));
        if (b != 0 && ((short)NavNodeGetReachable_311960(b)) != 0) {
            if (!(min <= NavNodeGetDist_311910(b) + NavEdgeGetCost_3116e0(a))) {
                min = NavNodeGetDist_311910(b) + NavEdgeGetCost_3116e0(a);
                best = a;
                bestb = b;
            }
        }
    }
    if (best != 0) {
        NavNodeSetReachable_311950(arg1, 1);
        NavNodeSetDist_311850(arg1, min);
        NavNodeSetPrev_311860(arg1, ((short)NavNodeGetId_3119c0(bestb)));
    }
    return best;
}
