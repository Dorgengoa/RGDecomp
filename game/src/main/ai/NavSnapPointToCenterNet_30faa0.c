/* rgp:protos */
#define RGP_SELF_NavSnapPointToCenterNet_30faa0 1
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
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045B080[];

#pragma opt_lifetimes off
s32 NavSnapPointToCenterNet_30faa0(s32 self, s32 arg1, s32 arg2, s32 flag, f32 dist) {
    f32 pos[4] __attribute__((aligned(16)));
    s32 pair[2];
    u8 fl;
    s32 seg;
    s32 b;
    s32 k;
    s32 a;
    s32 i;
    s32 cur;
    s16 *ids;
    s32 cnt;
    s32 e;
    s32 best;
    s32 p;
    u32 n;
    u32 j;
    f32 d;



    if (NavGraphGetNodes_310cc0(self) == 0) {
        return 0;
    }
    fl = flag;
    if (fl == 0) {
        NavXformPointToLocal_310d50(self, pos, arg2);
    } else {
        VecCopy_1cbe30(pos, arg2);
    }
    seg = NavFindNearestEdgePointYTol_310090(self, arg1, pos, 1, dist);
    if (seg == 0) {
        return 0;
    }
    a = ((s32)NavGraphGetNode_310cd0(self, ((short)NavEdgeGetNodeA_311700(seg))));
    pair[0] = a;
    if (a == 0) {
        return 0;
    }
    pair[1] = b = ((s32)NavGraphGetNode_310cd0(self, ((short)NavEdgeGetNodeB_3116f0(seg))));
    if (b == 0) {
        return 0;
    }
    a = (NavNodeGetFlags_3119a0(pair[0]) & 1) != 0;
    if (NavNodeGetFlags_3119a0(b) & 1) {
        k = 2;
    } else {
        k = 0;
    }
    k = (s32)((u32)a + k);
    if (k > 0) {
        if (k == 1) {
            Vec3ToVec4W1_311970(pair[0], arg1);
        } else if (k == 2) {
            Vec3ToVec4W1_311970(b, arg1);
        }
        if (fl == 0) {
            NavXformPointToWorld_310d10(self, arg1, arg1);
        }
        return 1;
    }
    { f32 c = *(f32 *)D_0045B080; dist = (f32)1000000 * c; }
    best = 0;
    for (p = 0; p < 2; p++) {
        cur = pair[p];
        ids = ((s16 *)NavNodeGetEdgeList_311940(cur));
        for (cnt = 0; cnt < ((short)NavNodeGetEdgeCount_311930(cur)); cnt++, ids++) {
            e = ((s32)NavGraphGetEdge_310c20(self, *ids));
            if (e == 0) {
                continue;
            }
            e = ((s32)NavGraphGetNode_310cd0(self, NavEdgeGetOtherNode_3116b0(e, ((short)NavNodeGetId_3119c0(cur)))));
            if (e == 0) {
                continue;
            }
            if (!(NavNodeGetFlags_3119a0(e) & 1)) {
                continue;
            }
            d = NavNodeDistSq_3118d0(e, pos);
            if (dist <= d) {
                continue;
            }
            dist = d;
            best = e;
        }
    }
    if (best != 0) {
        Vec3ToVec4W1_311970(best, arg1);
        if (fl == 0) {
            NavXformPointToWorld_310d10(self, arg1, arg1);
        }
        return 1;
    }
    p = NavEdgeNearestNode_30f940(self, pos, seg, 1);
    if (!(NavGraphHasReachableCenterNode_30fa00(self) & 0xFF)) {
        NavGraphSetSearchLimit_310da0(self, -1.0f);
    }
    NavSearchFromNode_30e810(self, ((short)NavNodeGetId_3119c0(p)));
    p = NavGraphGetNodes_310cc0(self);
    n = ((unsigned short)NavGraphGetNodeCount_310cb0(self));
    for (j = 0; j < n; j++, p += 0x24) {
        if (NavNodeGetReachable_311960(p) == 0) {
            continue;
        }
        if (!(NavNodeGetFlags_3119a0(p) & 1)) {
            continue;
        }
        d = NavNodeGetDist_311910(p);
        if (d <= dist) {
            dist = d;
            best = p;
        }
    }
    if (best != 0) {
        Vec3ToVec4W1_311970(best, arg1);
        if (fl == 0) {
            NavXformPointToWorld_310d10(self, arg1, arg1);
        }
        return 1;
    }
    return 0;
}
