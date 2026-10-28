/* rgp:protos */
#define RGP_SELF_NavGraphSetLimitFromCharas_3109a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
#pragma opt_loop_invariants off

typedef struct G18 {
    u8 pad0[0x18E];
    s16 x18E;
} G18;

typedef struct G {
    u8 pad0[0x18];
    G18 *x18;
} G;

typedef struct Ch {
    u8 pad0[0x94];
    s32 x94;
} Ch;

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
/*rgp*/
/*rgp*/
extern f32 D_0045B080[4];

void NavGraphSetLimitFromCharas_3109a0(s32 arg0) {
    u8 spA0[16] __attribute__((aligned(16)));
    u8 sp90[16] __attribute__((aligned(16)));
    s32 list;
    G *g;
    f32 best;
    f32 d;
    f32 lim;
    s32 id;
    s32 it;
    s32 cur;
    Ch *ch;
    s32 kind;
    s32 r;

    if (NavGraphGetSearchLimit_310e50(arg0) < 0.0f) {
        return;
    }
    list = DListGetHead_42ea60(((s32)ActionMgrGetCharaList_233b40(((s32)GetActionMgr_1fdb50()))));
    g = ((G *)GetGameData_1fede0());
    best = 0.0f;
    lim = (f32)1000000 * D_0045B080[0];
    while (list != 0) {
        it = list + 0x10;
        list = DListGetNext_42eb30(list);
        cur = g->x18->x18E;
        { s32 v = ((short)CharaGetId_214a80(it)); if (v == cur) continue; }
        if (0) {
            continue;
        }
        id = ((s32)CharaGetAi_214a10(it));
        ch = ((Ch *)AiGetNavPath_2c10a0(id));
        kind = ch->x94;
        d = 0.0f;
        if (kind == NavGraphGetId_310e90(arg0)) {
            CharaGetPos_2388a0(it, spA0);
            NavXformPointToLocal_310d50(arg0, spA0, spA0);
            r = ((s32)NavFindNearestEdgePoint_310380(arg0, sp90, spA0, 1));
            if (r == 0) {
                continue;
            }
            AiSetNavEdgeId_2c0ea0(id, ((short)NavEdgeGetId_311720(r)));
            r = NavEdgeNearestNode_30f940(arg0, spA0, r, 1);
            if (r == 0) {
                continue;
            }
            if (((short)NavNodeGetReachable_311960(r)) != 0) {
                d = NavNodeGetDist_311910(r);
            } else {
                d = lim;
            }
        } else {
            if (((short)NavGraphGetGoalNodeId_310e70(arg0)) < 0) {
                continue;
            }
            r = NavMgrFindGraphById_30cae0(((s32)GetNavMgr_2d1950()), ch->x94);
            if (r != 0) {
                r = NavFindNodeByLinkName_3108d0(arg0, ((s32)NavGraphGetName_310eb0(r)));
                if (r != 0) {
                    d = NavNodeGetDist_311910(r);
                }
            }
        }
        if (!(d < lim)) {
            best = -1.0f;
            break;
        }
        if (best < 400.0f + d) {
            best = 400.0f + d;
        }
    }
    NavGraphSetSearchLimit_310da0(arg0, best);
}
