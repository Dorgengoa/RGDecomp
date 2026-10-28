/* rgp:protos */
#define RGP_SELF_NavSetGoalPos_30bd80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4;

typedef struct {
    u8 pad[0x90];
    s8 x90;
    s8 x91;
    s16 x92;
    s32 x94;
} Ent;

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

s32 NavSetGoalPos_30bd80(s32 arg0, s32 arg1, s32 arg2)
{
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    s32 h;
    s32 r;
    s32 p;
    s32 q;
    Ent *e;
    s32 id;

    id = arg2;
    if (arg2 < 10000) {
        h = MapFindBlockAtPos_1e3a00(((s32)GetMapMgr_201a90()), arg1, 0.0f);
        if (h != 0) {
            id = MapBlockGetNavGraphId_1e0050(h);
        }
    }
    NavMgrSetCurrent_30ca70(arg0, NavMgrFindGraphById_30cae0(arg0, id));
    if (NavMgrGetCurrent_30cab0(arg0) != 0) {
        NavXformPointToLocal_310d50(NavMgrGetCurrent_30cab0(arg0), &a, arg1);
        h = NavMgrGetCurrent_30cab0(arg0);
        NavGraphSetGoalEdge_3115f0(h, ((s32)NavFindNearestEdgePoint_310380(NavMgrGetCurrent_30cab0(arg0), &b, &a, 1)));
        if (NavGraphGetGoalEdge_310e00(NavMgrGetCurrent_30cab0(arg0)) != 0) {
            NavXformPointToWorld_310d10(NavMgrGetCurrent_30cab0(arg0), &b, &b);
            NavGraphSetGoalPos_311630(NavMgrGetCurrent_30cab0(arg0), &b);
            h = NavMgrGetCurrent_30cab0(arg0);
            r = NavEdgeNearestNode_30f940(h, &a, NavGraphGetGoalEdge_310e00(NavMgrGetCurrent_30cab0(arg0)), 1);
            if (r != 0) {
                h = NavMgrGetCurrent_30cab0(arg0);
                NavSearchFromNode_30e810(h, ((short)NavNodeGetId_3119c0(r)));
            }
        }
    } else {
        p = DListGetHead_42ea60(((s32)ActionMgrGetCharaList_233b40(((s32)GetActionMgr_1fdb50()))));
        while (p != 0) {
            q = p + 0x10;
            p = DListGetNext_42eb30(p);
            e = ((Ent *)AiGetNavPath_2c10a0(((s32)CharaGetAi_214a10(q))));
            e->x90 = 0;
            e->x91 = 0;
            e->x94 = -1;
            e->x92 = -1;
        }
    }
    return NavMgrGetCurrent_30cab0(arg0);
}
