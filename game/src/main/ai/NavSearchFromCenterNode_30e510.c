/* rgp:protos */
#define RGP_SELF_NavSearchFromCenterNode_30e510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Sibling of NavSearchFromNode_30e810; same loop body, extra head guards and a
   success counter distinct from the loop counter. */

typedef struct A {
    u8  pad0[0x10E];
    s16 h10e;
    u8  pad110;
    s8  f111;
} A;

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

    if (((unsigned char)NavGraphIsValid_311140((int)a)) == 0) {
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
    q = ((s16 *)NavNodeGetEdgeList_311940(p));
    if (q == 0) {
        return 0;
    }
    hit = 0;
    for (i = 0; i < ((short)NavNodeGetEdgeCount_311930(p)); i++, q++) {
        o = NavGraphGetEdge_310c20(a, *q);
        if (NavGraphGetSearchLimit_310e50(a) >= 0.0f) {
            lim = NavGraphGetSearchLimit_310e50(a);
            if (lim < NavEdgeGetCost_3116e0(o)) {
                NavGraphSetSearchLimit_310da0(a, NavEdgeGetCost_3116e0(o));
            }
        }
        n = NavGraphGetNode_310cd0(a, NavEdgeGetOtherNode_3116b0(o, ((short)NavNodeGetId_3119c0(p))));
        if ((NavNodeGetFlags_3119a0(n) & 1) == 0) {
            continue;
        }
        if (((short)NavEdgeGetNodeA_311700(o)) == ((short)NavNodeGetId_3119c0(p))) {
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
