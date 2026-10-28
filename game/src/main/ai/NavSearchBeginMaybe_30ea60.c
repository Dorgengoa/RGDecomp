/* rgp:protos */
#define RGP_SELF_NavSearchBeginMaybe_30ea60 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[];

s32 NavSearchBeginMaybe_30ea60(void *g, char *node, s32 opt) {
    s32 full;
    f32 lim;
    char *p;
    u32 cnt;
    u32 i;
    char *q;
    s32 changed;
    u32 j;
    s16 *e;
    s32 k;
    u32 j2;
    s16 *e2;
    s32 k2;
    char *edge1;
    char *q1;
    char *p1;
    char *edge2;
    char *q2;
    char *p2;


    if (node == 0) {
        NavSearchReset_30f0a0(g);
        return 0;
    }
    full = 1;
    lim = NavGraphGetSearchLimit_310e50(g);
    if (!(NavGraphGetSearchLimit_310e50(g) < 0.0f) && (NavNodeGetReachable_311960(node) || NavNodeRelaxBestEdge_30f170(g, node))) {
        full = 0;
        if (((short)NavGraphGetGoalNodeId_310e70(g)) != ((short)NavNodeGetId_3119c0(node))) {
            lim += NavNodeGetDist_311910(node);
        }
        if (lim < 700.0f) {
            lim = 700.0f;
        }
        NavGraphSetSearchLimit_310da0(g, lim);
    } else if (((short)NavGraphGetGoalNodeId_310e70(g)) < 0) {
        NavNodeSetDist_311850(node, 0.0f);
        NavNodeSetReachable_311950(node, 1);
        lim = 700.0f;
        NavGraphSetSearchLimit_310da0(g, lim);
        full = 0;
    } else {
        NavGraphSetSearchLimit_310da0(g, -1.0f);
        lim = (f32)1000000 * D_0045B080[0];
    }
    p = ((char *)NavGraphGetNodes_310cc0(g));
    if (p == 0) {
        return 0;
    }
    cnt = 0;
    for (i = 0; i < ((unsigned short)NavGraphGetNodeCount_310cb0(g)); i++, p += 0x24) {
        if (full == 0) {
            if (!NavNodeGetReachable_311960(p)) {
                goto off;
            }
            if (!(NavNodeGetDist_311910(p) <= lim)) {
                goto off;
            }
        }
        if ((u8)opt != 0 && (NavNodeGetFlags_3119a0(p) & 1) == 0) {
            goto off;
        }
        NavNodeSetReachable_311950(p, 1);
        if (opt != 0 && ((short)NavNodeGetPrev_311920(p)) >= 0) {
            q = ((char *)NavGraphGetNode_310cd0(g, ((short)NavNodeGetPrev_311920(p))));
            if (q != 0 && ((NavNodeGetFlags_3119a0(q) & 1) == 0 || NavNodeGetReachable_311960(q) == 0)) {
                NavNodeSetReachable_311950(p, 0);
            }
        }
        cnt++;
        continue;
    off:
        NavNodeSetReachable_311950(p, 0);
    }
    if (cnt < ((unsigned short)NavGraphGetNodeCount_310cb0(g))) {
        changed = 0;
        for (p1 = ((char *)NavGraphGetNodes_310cc0(g)), j = 0; j < ((unsigned short)NavGraphGetNodeCount_310cb0(g)); j++, p1 += 0x24) {
            if (NavNodeGetReachable_311960(p1) == 0) {
                continue;
            }
            if (opt != 0 && (NavNodeGetFlags_3119a0(p1) & 1) == 0) {
                continue;
            }
            e = ((s16 *)NavNodeGetEdgeList_311940(p1));
            for (k = 0; k < ((short)NavNodeGetEdgeCount_311930(p1)); k++, e++) {
                edge1 = ((char *)NavGraphGetEdge_310c20(g, *e));
                if (edge1 == 0) {
                    continue;
                }
                if (!(NavNodeGetDist_311910(p1) + NavEdgeGetCost_3116e0(edge1) <= lim)) {
                    continue;
                }
                q1 = ((char *)NavGraphGetNode_310cd0(g, NavEdgeGetOtherNode_3116b0(edge1, ((short)NavNodeGetId_3119c0(p1)))));
                if (q1 == 0) {
                    continue;
                }
                if (NavNodeGetReachable_311960(q1) == 1) {
                    continue;
                }
                if (opt != 0 && (NavNodeGetFlags_3119a0(q1) & 1) == 0) {
                    continue;
                }
                NavNodeSetReachable_311950(q1, 2);
                changed++;
                if (!(NavNodeGetDist_311910(q1) <= NavNodeGetDist_311910(p1) + NavEdgeGetCost_3116e0(edge1))) {
                    NavNodeSetDist_311850(q1, NavNodeGetDist_311910(p1) + NavEdgeGetCost_3116e0(edge1));
                }
            }
        }
        if (((short)NavGraphGetGoalNodeId_310e70(g)) == ((short)NavNodeGetId_3119c0(node)) && changed == 0) {
            return 2;
        }
        if (changed != 0) {
            for (p2 = ((char *)NavGraphGetNodes_310cc0(g)), j2 = 0; j2 < ((unsigned short)NavGraphGetNodeCount_310cb0(g)); j2++, p2 += 0x24) {
                if (NavNodeGetReachable_311960(p2) != 2) {
                    continue;
                }
                e2 = ((s16 *)NavNodeGetEdgeList_311940(p2));
                for (k2 = 0; k2 < ((short)NavNodeGetEdgeCount_311930(p2)); k2++, e2++) {
                    edge2 = ((char *)NavGraphGetEdge_310c20(g, *e2));
                    if (edge2 == 0) {
                        continue;
                    }
                    if (!(NavNodeGetDist_311910(p2) + NavEdgeGetCost_3116e0(edge2) <= lim)) {
                        continue;
                    }
                    q2 = ((char *)NavGraphGetNode_310cd0(g, NavEdgeGetOtherNode_3116b0(edge2, ((short)NavNodeGetId_3119c0(p2)))));
                    if (q2 == 0) {
                        continue;
                    }
                    if (NavNodeGetReachable_311960(q2) == 1) {
                        continue;
                    }
                    if (opt != 0 && (NavNodeGetFlags_3119a0(q2) & 1) == 0) {
                        continue;
                    }
                    NavNodeSetReachable_311950(q2, 2);
                    if (!(NavNodeGetDist_311910(q2) <= NavNodeGetDist_311910(p2) + NavEdgeGetCost_3116e0(edge2))) {
                        NavNodeSetDist_311850(q2, NavNodeGetDist_311910(p2) + NavEdgeGetCost_3116e0(edge2));
                    }
                }
            }
        }
    }
    NavSearchReset_30f0a0(g);
    NavNodeSetDist_311850(node, 0.0f);
    return 1;
}
