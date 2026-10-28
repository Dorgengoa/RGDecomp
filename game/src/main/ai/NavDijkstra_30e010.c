/* rgp:protos */
#define RGP_SELF_MULF 1
#define RGP_SELF_NavDijkstra_30e010 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off


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
/*rgp*/
/*rgp*/
void memset(void *, s32, u32);
extern f32 D_0045B080[];
static inline f32 MULF(s32 n, f32 u) { f32 c = (f32)n; f32 r = c * u; return r; }

s32 NavDijkstra_30e010(void *g, u32 start) {
    u32 t;
    f32 limit;
    s8 *done;
    u32 sel;
    char *n;
    s32 heap;
    s32 best;
    u32 ii;
    char *p;
    u32 j;
    s16 *e;
    char *pp;
    u32 i;
    char *r;
    char *edge;
    f32 d;
    u32 k;
    char *q;
    s32 infi;
    s32 m;
    f32 inf;




    heap = *(s32 *)(((char *)GetCurrentScene_1f5be0()) + 0x180C);
    if (heap == 0) {
        return 0;
    }
    done = ((s8 *)MemStackHeapAlloc_14db10(heap, 2, 0, 0x40));
    if (done == 0) {
        return 0;
    }
    MemStackReturnToOwnerMaybe_14dad0(heap);
    MemStackHeapFree_14dcb0(heap, done);
    memset(done, 0, ((unsigned short)NavGraphGetNodeCount_310cb0(g)));
    done[start] = 1;
    limit = NavGraphGetSearchLimit_310e50(g);
    if (limit < 0.0f) {
        limit = MULF(1000000, D_0045B080[0]);
        NavGraphSetSearchLimit_310da0(g, limit);
    }
    n = ((char *)NavGraphGetNodes_310cc0(g));
    if (n == 0) {
        return 0;
    }
    k = 0;
    inf = MULF(1000000, D_0045B080[0]);
    infi = inf;
    for (; k < ((unsigned short)NavGraphGetNodeCount_310cb0(g)); k++, n += 0x24) {
        if (NavNodeGetReachable_311960(n) == 0) {
            continue;
        }
        best = infi;
        for (p = ((char *)NavGraphGetNodes_310cc0(g)), i = 0; i < ((unsigned short)NavGraphGetNodeCount_310cb0(g)); i++, p += 0x24) {
            if (NavNodeGetReachable_311960(p) != 0 && done[i] == 0 && NavNodeGetDist_311910(p) < (f32)best) {
                best = NavNodeGetDist_311910(p);
                sel = i;
            }
        }
        done[sel] = 1;
        for (q = ((char *)NavGraphGetNodes_310cc0(g)), j = 0; j < ((unsigned short)NavGraphGetNodeCount_310cb0(g)); j++, q += 0x24) {
            if (NavNodeGetReachable_311960(q) == 0) {
                continue;
            }
            if (done[j] != 0) {
                continue;
            }
            e = ((s16 *)NavNodeGetEdgeList_311940(q));
            d = inf;
            for (m = 0; m < ((short)NavNodeGetEdgeCount_311930(q)); m++, e++) {
                edge = ((char *)NavGraphGetEdge_310c20(g, *e));
                if (sel != NavEdgeGetOtherNode_3116b0(edge, ((short)NavNodeGetId_3119c0(q)))) {
                    continue;
                }
                t = ((short)NavEdgeGetNodeA_311700(edge));
                if (t == ((short)NavNodeGetId_3119c0(q))) {
                    if (NavEdgeGetFlags_311710(edge) & 0x10000) {
                        break;
                    }
                } else {
                    if (NavEdgeGetFlags_311710(edge) & 0x20000) {
                        break;
                    }
                }
                d = NavEdgeGetCost_3116e0(edge);
                break;
            }
            if (d < inf) {
                if (!(NavNodeGetDist_311910(q) <= d + NavNodeGetDist_311910(((char *)NavGraphGetNode_310cd0(g, sel))))) {
                    NavNodeSetDist_311850(q, d + NavNodeGetDist_311910(((char *)NavGraphGetNode_310cd0(g, sel))));
                    NavNodeSetPrev_311860(q, sel);
                }
            }
        }
    }
    for (pp = ((char *)NavGraphGetNodes_310cc0(g)), ii = 0; ii < ((unsigned short)NavGraphGetNodeCount_310cb0(g)); ii++, pp += 0x24) {
        if (ii == start) {
            continue;
        }
        if (NavNodeGetReachable_311960(pp) == 0) {
            continue;
        }
        if (((short)NavNodeGetPrev_311920(pp)) >= 0) {
            r = ((char *)NavGraphFindEdge_3106e0(g, ii, ((short)NavNodeGetPrev_311920(pp))));
            NavEdgeSetDirFlag_3115a0(r, ii, ((short)NavNodeGetPrev_311920(pp)), 0);
            if (!(NavNodeGetDist_311910(pp) <= limit)) {
                if (NavNodeGetDist_311910(((char *)NavGraphGetNode_310cd0(g, NavEdgeGetOtherNode_3116b0(r, ii)))) > limit) {
                    NavNodeSetReachable_311950(pp, 0);
                } else {
                    NavNodeSetReachable_311950(pp, 1);
                }
            }
        } else {
            NavNodeSetReachable_311950(pp, 0);
        }
    }
    NavGraphSetActiveLimitMaybe_310d90(g, limit);
    return 1;
}
