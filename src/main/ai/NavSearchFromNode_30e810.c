#include "types.h"

/* Sibling of NavSearchFromCenterNode_30e510 (same TU, same loop body).
   dsll32/dsra32 ..,24 on NavSearchBeginMaybe_30ea60's result = an s8 local off an s32
   return; the raw s32 is what is returned on the a->f111 == 0 exit.
   The equal arm of the NavEdgeGetNodeA_311700 / NavNodeGetId_3119c0 compare FALLS THROUGH,
   so the 0x20000 test is the source's `if` body. */

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
extern void *NavGraphGetNode_310cd0(A *a, s32 id);
extern s32 NavSearchBeginMaybe_30ea60(A *a, void *p, s32 mode);
extern s16 *NavNodeGetEdgeList_311940(void *p);
extern s32 NavNodeGetEdgeCount_311930(void *p);
extern void *NavGraphGetEdge_310c20(A *a, s16 id);
extern f32 NavEdgeGetCost_3116e0(void *o);
extern void NavGraphSetSearchLimit_310da0(A *a, f32 v);
extern s32 NavNodeGetId_3119c0(void *p);
extern s32 NavEdgeGetOtherNode_3116b0(void *o, s32 v);
extern s32 NavEdgeGetNodeA_311700(void *o);
extern s32 NavEdgeGetFlags_311710(void *o);
extern void NavNodeSetReachable_311950(void *n, s32 v);
extern void NavNodeSetPrev_311860(void *n, s32 v);
extern void NavNodeSetDist_311850(void *n, f32 v);
extern s32 NavDijkstra_30e010(A *a, s32 b);

s32 NavSearchFromNode_30e810(A *a, s32 b)
{
    void *p;
    s16 *q;
    void *o;
    void *n;
    s32 i;
    s8 r;
    f32 lim;

    if (NavGraphIsValid_311140() == 0) {
        return 0;
    }
    NavGraphSetActiveLimitMaybe_310d90(a, NavGraphGetSearchLimit_310e50(a));
    NavGraphSetLimitFromCharas_3109a0(a);
    p = NavGraphGetNode_310cd0(a, b);
    r = NavSearchBeginMaybe_30ea60(a, p, 0);
    if (r != 1) {
        if (r == 0) {
            return 0;
        }
        if (a->f111 == 0) {
            return 1;
        }
    }
    q = NavNodeGetEdgeList_311940(p);
    if (q == 0) {
        return 0;
    }
    for (i = 0; i < NavNodeGetEdgeCount_311930(p); i++, q++) {
        o = NavGraphGetEdge_310c20(a, *q);
        if (o == 0) {
            continue;
        }
        if (NavGraphGetSearchLimit_310e50(a) >= 0.0f) {
            lim = NavGraphGetSearchLimit_310e50(a);
            if (lim < NavEdgeGetCost_3116e0(o)) {
                NavGraphSetSearchLimit_310da0(a, NavEdgeGetCost_3116e0(o));
            }
        }
        n = NavGraphGetNode_310cd0(a, NavEdgeGetOtherNode_3116b0(o, NavNodeGetId_3119c0(p)));
        if (n == 0) {
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
    }
    a->h10e = b;
    a->f111 = 0;
    return NavDijkstra_30e010(a, b);
}
