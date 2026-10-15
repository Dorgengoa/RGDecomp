#include "types.h"
#pragma opt_propagation off


void MemStackReturnToOwnerMaybe_14dad0(s32);
s8 *MemStackHeapAlloc_14db10(s32, s32, s32, s32);
void MemStackHeapFree_14dcb0(s32, s8 *);
char *GetCurrentScene_1f5be0(void);
char *NavGraphFindEdge_3106e0(void *, u32, s32);
char *NavGraphGetEdge_310c20(void *, s32);
u32 NavGraphGetNodeCount_310cb0(void *);
char *NavGraphGetNodes_310cc0(void *);
char *NavGraphGetNode_310cd0(void *, u32);
void NavGraphSetActiveLimitMaybe_310d90(void *, f32);
void NavGraphSetSearchLimit_310da0(void *, f32);
f32 NavGraphGetSearchLimit_310e50(void *);
void NavEdgeSetDirFlag_3115a0(char *, u32, s32, s32);
u32 NavEdgeGetOtherNode_3116b0(char *, u32);
f32 NavEdgeGetCost_3116e0(char *);
u32 NavEdgeGetNodeA_311700(char *);
u32 NavEdgeGetFlags_311710(char *);
void NavNodeSetDist_311850(char *, f32);
void NavNodeSetPrev_311860(char *, u32);
f32 NavNodeGetDist_311910(char *);
s32 NavNodeGetPrev_311920(char *);
s32 NavNodeGetEdgeCount_311930(char *);
s16 *NavNodeGetEdgeList_311940(char *);
void NavNodeSetReachable_311950(char *, s32);
s16 NavNodeGetReachable_311960(char *);
u32 NavNodeGetId_3119c0(char *);
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




    heap = *(s32 *)(GetCurrentScene_1f5be0() + 0x180C);
    if (heap == 0) {
        return 0;
    }
    done = MemStackHeapAlloc_14db10(heap, 2, 0, 0x40);
    if (done == 0) {
        return 0;
    }
    MemStackReturnToOwnerMaybe_14dad0(heap);
    MemStackHeapFree_14dcb0(heap, done);
    memset(done, 0, NavGraphGetNodeCount_310cb0(g));
    done[start] = 1;
    limit = NavGraphGetSearchLimit_310e50(g);
    if (limit < 0.0f) {
        limit = MULF(1000000, D_0045B080[0]);
        NavGraphSetSearchLimit_310da0(g, limit);
    }
    n = NavGraphGetNodes_310cc0(g);
    if (n == 0) {
        return 0;
    }
    k = 0;
    inf = MULF(1000000, D_0045B080[0]);
    infi = inf;
    for (; k < NavGraphGetNodeCount_310cb0(g); k++, n += 0x24) {
        if (NavNodeGetReachable_311960(n) == 0) {
            continue;
        }
        best = infi;
        for (p = NavGraphGetNodes_310cc0(g), i = 0; i < NavGraphGetNodeCount_310cb0(g); i++, p += 0x24) {
            if (NavNodeGetReachable_311960(p) != 0 && done[i] == 0 && NavNodeGetDist_311910(p) < (f32)best) {
                best = NavNodeGetDist_311910(p);
                sel = i;
            }
        }
        done[sel] = 1;
        for (q = NavGraphGetNodes_310cc0(g), j = 0; j < NavGraphGetNodeCount_310cb0(g); j++, q += 0x24) {
            if (NavNodeGetReachable_311960(q) == 0) {
                continue;
            }
            if (done[j] != 0) {
                continue;
            }
            e = NavNodeGetEdgeList_311940(q);
            d = inf;
            for (m = 0; m < NavNodeGetEdgeCount_311930(q); m++, e++) {
                edge = NavGraphGetEdge_310c20(g, *e);
                if (sel != NavEdgeGetOtherNode_3116b0(edge, NavNodeGetId_3119c0(q))) {
                    continue;
                }
                t = NavEdgeGetNodeA_311700(edge);
                if (t == NavNodeGetId_3119c0(q)) {
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
                if (!(NavNodeGetDist_311910(q) <= d + NavNodeGetDist_311910(NavGraphGetNode_310cd0(g, sel)))) {
                    NavNodeSetDist_311850(q, d + NavNodeGetDist_311910(NavGraphGetNode_310cd0(g, sel)));
                    NavNodeSetPrev_311860(q, sel);
                }
            }
        }
    }
    for (pp = NavGraphGetNodes_310cc0(g), ii = 0; ii < NavGraphGetNodeCount_310cb0(g); ii++, pp += 0x24) {
        if (ii == start) {
            continue;
        }
        if (NavNodeGetReachable_311960(pp) == 0) {
            continue;
        }
        if (NavNodeGetPrev_311920(pp) >= 0) {
            r = NavGraphFindEdge_3106e0(g, ii, NavNodeGetPrev_311920(pp));
            NavEdgeSetDirFlag_3115a0(r, ii, NavNodeGetPrev_311920(pp), 0);
            if (!(NavNodeGetDist_311910(pp) <= limit)) {
                if (NavNodeGetDist_311910(NavGraphGetNode_310cd0(g, NavEdgeGetOtherNode_3116b0(r, ii))) > limit) {
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
