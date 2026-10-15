#include "types.h"
#pragma opt_propagation off

s32 NavGraphGetEdges_310c10(s32);
u32 NavGraphGetEdgeCount_310c00(s32);
s32 NavGraphGetNode_310cd0(s32, s32);
void NavXformPointToWorld_310d10(s32, f32 *, f32 *);
void NavXformPointToLocal_310d50(s32, f32 *, f32 *);
s32 NavEdgeGetNodeB_3116f0(s32);
s32 NavEdgeGetNodeA_311700(s32);
void Vec3ToVec4W1_311970(s32, f32 *);
void ClosestPointOnSegment_1c9f60(f32 *, f32 *, f32 *, f32 *);
f32 VecDistSq_1cb3c0(f32 *, f32 *);
void VecCopy_1cbe30(f32 *, f32 *);
extern f32 D_0045B080[4];

s32 NavFindNearestEdgePointYTol_310090(s32 self, f32 *out, f32 *in, s32 flag, f32 tol) {
    f32 e[4];
    f32 d[4];
    f32 c[4];
    f32 b[4];
    s32 best;
    s32 ent;
    u32 n;
    u32 k;
    f32 bestd;
    s32 p0;
    s32 p1;
    f32 dist;
    s32 j;
    f32 *pe;
    f32 t;
    f32 hi;
    f32 lo;
    f32 *pd;
    f32 *pc;
    s32 i;
    u8 fl;
    if (NavGraphGetEdges_310c10(self) == 0) {
        return 0;
    }
    fl = flag;
    if (!fl) {
        NavXformPointToLocal_310d50(self, e, in);
    } else {
        VecCopy_1cbe30(e, in);
    }
    best = 0;
    ent = NavGraphGetEdges_310c10(self);
    bestd = (f32)1000000 * D_0045B080[0];
    n = NavGraphGetEdgeCount_310c00(self);
    for (k = 0; k < n; k++, ent += 0x14) {
        p0 = NavGraphGetNode_310cd0(self, NavEdgeGetNodeA_311700(ent));
        if (p0 == 0) {
            continue;
        }
        p1 = NavGraphGetNode_310cd0(self, NavEdgeGetNodeB_3116f0(ent));
        if (p1 == 0) {
            continue;
        }
        Vec3ToVec4W1_311970(p0, d);
        Vec3ToVec4W1_311970(p1, c);
        if (!(d[1] - e[1] <= tol)) {
            if (!(c[1] - e[1] <= tol)) {
                continue;
            }
        } else if (!(e[1] - d[1] <= tol) && !(e[1] - c[1] <= tol)) {
            continue;
        }
        for (i = 0; i < 2; i++) {
            j = i * 2;
            pc = &c[i * 2];
            pd = &d[i * 2];
            if (!(*pd <= *pc)) {
                lo = *pc;
                hi = *pd;
            } else {
                lo = *pd;
                hi = *pc;
            }
            if (!(e[i * 2] <= hi)) {
                pe = &e[j];
                t = *pe - hi;
                if (!(t * t <= bestd)) {
                    break;
                }
            } else if (e[i * 2] < lo) {
                pe = &e[j];
                t = lo - *pe;
                if (!(t * t <= bestd)) {
                    break;
                }
            }
        }
        if (i < 2) {
            continue;
        }
        ClosestPointOnSegment_1c9f60(b, d, c, e);
        dist = VecDistSq_1cb3c0(b, e);
        if (dist < bestd) {
            VecCopy_1cbe30(out, b);
            bestd = dist;
            best = ent;
        }
    }
    if (!fl) {
        NavXformPointToWorld_310d10(self, out, out);
    }
    return best;
}
