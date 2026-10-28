/* rgp:protos */
#define RGP_SELF_NavSearchFromNode_30e810 1
#include "port/game_protos.h"
#line 1
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

s32 NavSearchFromNode_30e810(A *a, s32 b)
{
    void *p;
    s16 *q;
    void *o;
    void *n;
    s32 i;
    s8 r;
    f32 lim;

    if (((unsigned char)NavGraphIsValid_311140((int)a)) == 0) {
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
    q = ((s16 *)NavNodeGetEdgeList_311940(p));
    if (q == 0) {
        return 0;
    }
    for (i = 0; i < ((short)NavNodeGetEdgeCount_311930(p)); i++, q++) {
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
        n = NavGraphGetNode_310cd0(a, NavEdgeGetOtherNode_3116b0(o, ((short)NavNodeGetId_3119c0(p))));
        if (n == 0) {
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
    }
    a->h10e = b;
    a->f111 = 0;
    return NavDijkstra_30e010(a, b);
}
