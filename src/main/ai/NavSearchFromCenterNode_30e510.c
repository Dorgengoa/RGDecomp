#include "types.h"

/* Sibling of NavSearchFromNode_30e810; same loop body, extra head guards and a
   success counter distinct from the loop counter. */

typedef struct A {
    u8  pad0[0x10E];
    s16 h10e;
    u8  pad110;
    s8  f111;
} A;

extern s32 NavGraphIsValid_311140(void);
extern f32 NavGraphGetSearchLimit_310e50(A *a);
extern void NavGraphSetActiveLimitMaybe_310d90(A *a, f32 v);
extern void NavGraphSetLimitFromCharas_3109a0(A *a);
extern s32 NavGraphHasReachableCenterNode_30fa00(A *a);
extern void *NavGraphGetNode_310cd0(A *a, s32 id);
extern s32 NavSearchBeginMaybe_30ea60(A *a, void *p, s32 mode);
extern s16 *NavNodeGetEdgeList_311940(void *p);
extern s32 NavNodeGetEdgeCount_311930(void *p);
extern void *NavGraphGetEdge_310c20(A *a, s16 id);
extern f32 NavEdgeGetCost_3116e0(void *o);
extern void NavGraphSetSearchLimit_310da0(A *a, f32 v);
extern s32 NavNodeGetId_3119c0(void *p);
extern s32 NavEdgeGetOtherNode_3116b0(void *o, s32 v);
extern s32 NavNodeGetFlags_3119a0(void *p);
extern s32 NavEdgeGetNodeA_311700(void *o);
extern s32 NavEdgeGetFlags_311710(void *o);
extern void NavNodeSetReachable_311950(void *n, s32 v);
extern void NavNodeSetPrev_311860(void *n, s32 v);
extern void NavNodeSetDist_311850(void *n, f32 v);
extern s32 NavDijkstraCenter_30dac0(A *a, s32 b);

s32 NavSearchFromCenterNode_30e510(A *a, s32 b)
{
    void *p;
    s16 *q;
    void *o;
    void *n;
    s32 hit;
    s32 i;
    s32 t;
    s32 u;
    s8 r;
    f32 lim;

    if (NavGraphIsValid_311140() == 0) {
        return 0;
    }
    NavGraphSetActiveLimitMaybe_310d90(a, NavGraphGetSearchLimit_310e50(a));
    NavGraphSetLimitFromCharas_3109a0(a);
    if (a->f111 == 0) {
        if ((NavGraphHasReachableCenterNode_30fa00(a) & 0xFF) == 0) {
            NavGraphSetSearchLimit_310da0(a, -1.0f);
        }
    }
    p = NavGraphGetNode_310cd0(a, b);
    if (p == 0) {
        return 0;
    }
    if ((NavNodeGetFlags_3119a0(p) & 1) == 0) {
        return 0;
    }
    t = NavSearchBeginMaybe_30ea60(a, p, 1);
    r = t;
    if (r != 1) {
        if (r == 0) {
            return 0;
        }
        if (a->f111 == 1) {
            return 1;
        }
    }
    u = NavSearchBeginMaybe_30ea60(a, p, 0);
    if (u == 0) {
        if (a->f111 == 1) {
            return 1;
        }
    }
    q = NavNodeGetEdgeList_311940(p);
    if (q == 0) {
        return 0;
    }
    hit = 0;
    for (i = 0; i < NavNodeGetEdgeCount_311930(p); i++, q++) {
        o = NavGraphGetEdge_310c20(a, *q);
        if (NavGraphGetSearchLimit_310e50(a) >= 0.0f) {
            lim = NavGraphGetSearchLimit_310e50(a);
            if (lim < NavEdgeGetCost_3116e0(o)) {
                NavGraphSetSearchLimit_310da0(a, NavEdgeGetCost_3116e0(o));
            }
        }
        n = NavGraphGetNode_310cd0(a, NavEdgeGetOtherNode_3116b0(o, NavNodeGetId_3119c0(p)));
        if ((NavNodeGetFlags_3119a0(n) & 1) == 0) {
            continue;
        }
        if (NavEdgeGetNodeA_311700(o) == NavNodeGetId_3119c0(p)) {
            if ((NavEdgeGetFlags_311710(o) & 0x20000) != 0) {
                continue;
            }
        } else {
            if ((NavEdgeGetFlags_311710(o) & 0x10000) != 0) {
                continue;
            }
        }
        NavNodeSetReachable_311950(n, 1);
        NavNodeSetPrev_311860(n, b);
        NavNodeSetDist_311850(n, NavEdgeGetCost_3116e0(o));
        hit++;
    }
    if (hit == 0) {
        return 0;
    }
    a->h10e = b;
    a->f111 = 1;
    return NavDijkstraCenter_30dac0(a, b);
}
