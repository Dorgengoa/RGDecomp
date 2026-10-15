#include "types.h"
#pragma opt_propagation off

s32 MemStackReturnToOwnerMaybe_14dad0(s32);
s8 *MemStackHeapAlloc_14db10(s32, s32, s32, s32);
void MemStackHeapFree_14dcb0(s32, s8 *);
u8 *GetCurrentScene_1f5be0(void);
u8 *NavGraphFindEdge_3106e0(void *, s32, s32);
u8 *NavGraphGetEdge_310c20(void *, s16);
u32 NavGraphGetNodeCount_310cb0(void *);
u8 *NavGraphGetNodes_310cc0(void *);
u8 *NavGraphGetNode_310cd0(void *, s32);
void NavGraphSetActiveLimitMaybe_310d90(void *, f32);
void NavGraphSetSearchLimit_310da0(void *, f32);
f32 NavGraphGetSearchLimit_310e50(void *);
void NavEdgeSetDirFlag_3115a0(u8 *, s32, s32, s32);
s32 NavEdgeGetOtherNode_3116b0(u8 *, s32);
f32 NavEdgeGetCost_3116e0(u8 *);
s32 NavEdgeGetNodeA_311700(u8 *);
s32 NavEdgeGetFlags_311710(u8 *);
void NavNodeSetDist_311850(u8 *, f32);
void NavNodeSetPrev_311860(u8 *, s32);
f32 NavNodeGetDist_311910(u8 *);
s32 NavNodeGetPrev_311920(u8 *);
s32 NavNodeGetEdgeCount_311930(u8 *);
s16 *NavNodeGetEdgeList_311940(u8 *);
void NavNodeSetReachable_311950(u8 *, s32);
s16 NavNodeGetReachable_311960(u8 *);
s32 NavNodeGetFlags_3119a0(u8 *);
s32 NavNodeGetId_3119c0(u8 *);
void *memset(void *, s32, u32);
extern f32 D_0045B080[0x100];

s32 NavDijkstraCenter_30dac0(void *self, s32 idx) {
    s32 h;
    s8 *buf;
    s32 sel;
    f32 lim;
    u8 *e;
    s32 i;

    s32 ibig;
    s32 best;
    u8 *e2;
    s32 j;
    s32 n;

    s32 k;
    s16 *p;
    f32 f;
    f32 big;
    s32 m;
    u8 *o;
    s32 t;
    f32 sum;
    u8 *e4;
    u8 *e3;


    h = *(s32 *)(GetCurrentScene_1f5be0() + 0x180C);
    if (h == 0) return 0;
    buf = MemStackHeapAlloc_14db10(h, 2, 0, 0x40);
    MemStackReturnToOwnerMaybe_14dad0(h);
    MemStackHeapFree_14dcb0(h, buf);
    memset(buf, 0, NavGraphGetNodeCount_310cb0(self));
    buf[idx] = 1;
    lim = NavGraphGetSearchLimit_310e50(self);
    if (lim < 0.0f) {
        { f32 c = D_0045B080[0]; lim = (f32)1000000 * c; }
        NavGraphSetSearchLimit_310da0(self, lim);
    }
    e = NavGraphGetNodes_310cc0(self);
    if (e == 0) return 0;
    i = 0;
    { f32 c = D_0045B080[0]; big = (f32)1000000 * c; }
    ibig = big;
    for (; i < NavGraphGetNodeCount_310cb0(self); i++, e += 0x24) {
        if (NavNodeGetReachable_311960(e) == 0) continue;
        if (!(NavNodeGetFlags_3119a0(e) & 1)) continue;
        best = ibig;
        e2 = NavGraphGetNodes_310cc0(self);
        for (j = 0; j < NavGraphGetNodeCount_310cb0(self); j++, e2 += 0x24) {
            if (NavNodeGetReachable_311960(e2) == 0) continue;
            if (!(NavNodeGetFlags_3119a0(e2) & 1)) continue;
            if (buf[j] != 0) continue;
            if (!(NavNodeGetDist_311910(e2) < (f32)best)) continue;
            best = NavNodeGetDist_311910(e2);
            sel = j;
        }
        buf[sel] = 1;
        e3 = NavGraphGetNodes_310cc0(self);
        for (k = 0; k < NavGraphGetNodeCount_310cb0(self); k++, e3 += 0x24) {
            if (NavNodeGetReachable_311960(e3) == 0) continue;
            if (!(NavNodeGetFlags_3119a0(e3) & 1)) continue;
            if (buf[k] != 0) continue;
            p = NavNodeGetEdgeList_311940(e3);
            if (p == 0) continue;
            f = big;
            for (m = 0; m < NavNodeGetEdgeCount_311930(e3); m++, p++) {
                o = NavGraphGetEdge_310c20(self, *p);
                if (NavEdgeGetOtherNode_3116b0(o, NavNodeGetId_3119c0(e3)) != sel) continue;
                t = NavEdgeGetNodeA_311700(o);
                if (t == NavNodeGetId_3119c0(e3)) {
                    if (NavEdgeGetFlags_311710(o) & 0x10000) break;
                } else {
                    if (NavEdgeGetFlags_311710(o) & 0x20000) break;
                }
                f = NavEdgeGetCost_3116e0(o);
                break;
            }
            if (!(f < big)) continue;
            sum = f + NavNodeGetDist_311910(NavGraphGetNode_310cd0(self, sel));
            if (NavNodeGetDist_311910(e3) <= sum) continue;
            NavNodeSetDist_311850(e3, f + NavNodeGetDist_311910(NavGraphGetNode_310cd0(self, sel)));
            NavNodeSetPrev_311860(e3, sel);
        }
    }
    e4 = NavGraphGetNodes_310cc0(self);
    for (n = 0; n < NavGraphGetNodeCount_310cb0(self); n++, e4 += 0x24) {
        if (n == idx) continue;
        if (NavNodeGetReachable_311960(e4) == 0) continue;
        if (NavNodeGetPrev_311920(e4) >= 0) {
            o = NavGraphFindEdge_3106e0(self, n, NavNodeGetPrev_311920(e4));
            if (!(NavNodeGetDist_311910(e4) <= lim)) {
                if (!(NavNodeGetDist_311910(NavGraphGetNode_310cd0(self, NavEdgeGetOtherNode_3116b0(o, n))) <= lim)) NavNodeSetReachable_311950(e4, 0);
            }
            if ((NavNodeGetFlags_3119a0(e4) & 1) || n != idx) NavEdgeSetDirFlag_3115a0(o, n, NavNodeGetPrev_311920(e4), 0);
        } else {
            NavNodeSetReachable_311950(e4, 0);
        }
    }
    NavGraphSetActiveLimitMaybe_310d90(self, lim);
    return 1;
}
