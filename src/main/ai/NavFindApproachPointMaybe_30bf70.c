#include "types.h"

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct M44 {
    f32 m[16];
} M44;

extern f64 FabsDouble_1283a0(f64);
extern void ClosestPointOnSegment_1c9f60(V4 *, V4 *, V4 *, V4 *);
extern f32 VecDistSqXZ_1cb390(V4 *, V4 *);
extern f32 VecDistSq_1cb3c0(V4 *, V4 *);
extern void MatMulPoint_1cb8e0(V4 *, M44 *, V4 *);
extern f32 VecDotDiff_1cba40(V4 *, V4 *, V4 *);
extern void VecNormalizeXZ_1cbb50(V4 *, V4 *);
extern void VecNormalize_1cbb80(V4 *, V4 *);
extern void VecScale_1cbca0(V4 *, V4 *, f32);
extern void VecSub_1cbd00(V4 *, V4 *, V4 *);
extern void VecAdd_1cbdc0(V4 *, V4 *, V4 *);
extern void VecCopy_1cbe30(V4 *, V4 *);
extern s32 MapBlockGetNavGraphId_1e0050(s32);
extern s32 MapFindBlockAtPos_1e3a00(s32, V4 *, f32);
extern s32 GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern s32 NavMgrFindGraphById_30cae0(s32, s32);
extern u8 NavSearchFromCenterNode_30e510(s32, s32);
extern s32 NavEdgeNearestNode_30f940(s32, V4 *, s32, s32);
extern s32 NavFindNearestCenterEdgePoint_30fe80(s32, V4 *, V4 *, s32);
extern s32 NavFindNearestEdgePoint_310380(s32, V4 *, V4 *, s32);
extern s32 NavGraphGetNode_310cd0(s32, s32);
extern void NavXformPointToLocal_310d50(s32, V4 *, V4 *);
extern void NavGraphGetXform_310e40(s32, M44 *);
extern s8 NavGraphHasXform_310e60(s32);
extern s32 NavEdgeGetNodeB_3116f0(s32);
extern s32 NavEdgeGetNodeA_311700(s32);
extern s32 NavEdgeGetFlags_311710(s32);
extern f32 NavNodeGetDist_311910(s32);
extern s16 NavNodeGetReachable_311960(s32);
extern void Vec3ToVec4W1_311970(s32, V4 *);
extern s32 NavNodeGetFlags_3119a0(s32);
extern s32 NavNodeGetId_3119c0(s32);
extern f32 sqrtf(f32);
extern f32 D_0045B080[];
extern f32 D_0047D354;
extern f32 D_0047DCF4;

s32 NavFindApproachPointMaybe_30bf70(s32 arg0, V4 *out, V4 *tgt, s32 id, V4 *from, V4 *dir) {
    s32 pair[2];
    V4 v180;
    V4 v170;
    M44 mtx;
    V4 v120;
    V4 v110;
    V4 v100;
    V4 vF0;
    V4 vE0;
    V4 vD0;
    V4 vC0;
    V4 vB0;
    V4 vA0;
    s32 e;
    s32 m;
    s8 rel;
    s32 n;
    s32 fl;
    s32 a;
    s32 b;
    f32 base;
    f32 step;
    f32 best;
    s8 fl2;
    s32 i;
    s32 r;
    f32 d;
    f32 t;

    GetGameData_1fede0();
    if (id < 10000) {
        e = MapFindBlockAtPos_1e3a00(GetMapMgr_201a90(), tgt, 0.0f);
        if (e != 0) {
            id = MapBlockGetNavGraphId_1e0050(e);
        }
    }
    m = NavMgrFindGraphById_30cae0(arg0, id);
    if (m == 0) {
        return 0;
    }
    NavXformPointToLocal_310d50(m, &v180, tgt);
    NavXformPointToLocal_310d50(m, &v170, from);
    rel = NavGraphHasXform_310e60(m);
    if (rel != 0) {
        NavGraphGetXform_310e40(m, &mtx);
    }
    n = NavFindNearestEdgePoint_310380(m, &v120, &v180, 1);
    if (n == 0) {
        return 0;
    }
    fl = (NavEdgeGetFlags_311710(n) & 0x80000) != 0;
    a = (s8)(NavNodeGetFlags_3119a0(NavGraphGetNode_310cd0(m, NavEdgeGetNodeA_311700(n))) & 1);
    b = (s8)(NavNodeGetFlags_3119a0(NavGraphGetNode_310cd0(m, NavEdgeGetNodeB_3116f0(n))) & 1);
    if (a == 0 && b == 0) {
        if (rel != 0) {
            MatMulPoint_1cb8e0(out, &mtx, &v120);
        } else {
            VecCopy_1cbe30(out, &v120);
        }
        if (!(VecDistSq_1cb3c0(tgt, out) < 250000)) {
            return 0;
        }
        if (fl != 0) {
            if (!((f32)FabsDouble_1283a0((f64)(out->y - tgt->y)) <= 40.0f)) {
                return 0;
            }
        }
        return 1;
    }
    if (a != 0 && b != 0) {
        n = NavEdgeNearestNode_30f940(m, &v120, n, 1);
    } else {
        if (a != 0) {
            n = NavGraphGetNode_310cd0(m, NavEdgeGetNodeA_311700(n));
        } else {
            n = NavGraphGetNode_310cd0(m, NavEdgeGetNodeB_3116f0(n));
        }
        Vec3ToVec4W1_311970(n, &v120);
    }
    if (NavSearchFromCenterNode_30e510(m, NavNodeGetId_3119c0(n)) == 0) {
        return 0;
    }
    VecNormalizeXZ_1cbb50(&v110, dir);
    VecAdd_1cbdc0(&v100, &v170, dir);
    base = D_0045B080[0];
    step = 12.5f * base;
    VecScale_1cbca0(&v100, &v110, step);
    VecAdd_1cbdc0(&v100, &v100, &v180);
    VecCopy_1cbe30(&vF0, &v120);
    fl2 = fl;
    best = 1000000 * base;
    for (i = 0; i < 8; i++) {
        r = NavFindNearestCenterEdgePoint_30fe80(m, &vE0, &v100, 1);
        if (r == 0) {
            return 0;
        }
        {
            u8 *p_ = (u8 *)pair;
            u32 n_ = 8;
            if (p_ != 0) {
                while (n_ != 0) {
                    *p_ = 0;
                    n_--;
                    p_++;
                }
            }
        }
        pair[0] = NavGraphGetNode_310cd0(m, NavEdgeGetNodeA_311700(r));
        pair[1] = NavGraphGetNode_310cd0(m, NavEdgeGetNodeB_3116f0(r));
        d = NavNodeGetDist_311910(pair[0]);
        if (!(d <= NavNodeGetDist_311910(pair[1]))) {
            s32 tmp = pair[0];
            pair[0] = pair[1];
            pair[1] = tmp;
        }
        Vec3ToVec4W1_311970(pair[0], &vC0);
        Vec3ToVec4W1_311970(pair[1], &vD0);
        if (NavNodeGetReachable_311960(pair[0]) == 0 && NavNodeGetReachable_311960(pair[1]) == 0) {
            step *= D_0047DCF4;
            VecScale_1cbca0(&v100, &v110, step);
            VecAdd_1cbdc0(&v100, &v100, &v180);
            continue;
        }
        d = VecDistSqXZ_1cb390(&vE0, &v180);
        if (d <= 100.0f) {
            return 0;
        }
        if (d < 19600) {
            if (NavNodeGetReachable_311960(pair[1]) == 0) {
                if (rel != 0) {
                    MatMulPoint_1cb8e0(out, &mtx, &vC0);
                } else {
                    VecCopy_1cbe30(out, &vC0);
                }
                if (fl2 == 0 || (f32)FabsDouble_1283a0((f64)(out->y - tgt->y)) <= 40.0f) {
                    return 1;
                }
            }
            if (!(VecDistSqXZ_1cb390(&vD0, &v180) < 19600) && !(VecDotDiff_1cba40(&vD0, &v180, &v110) < 0.0f)) {
                ClosestPointOnSegment_1c9f60(&vB0, &vC0, &vD0, &v180);
                t = VecDistSqXZ_1cb390(&vE0, &v180);
                if (!(t < 19600)) {
                    VecCopy_1cbe30(out, &vE0);
                } else {
                    d = sqrtf(19600 - t);
                    VecSub_1cbd00(&v110, &vB0, &vE0);
                    VecNormalize_1cbb80(&v110, &v110);
                    VecScale_1cbca0(&v110, &v110, d);
                    VecAdd_1cbdc0(out, &v110, &vE0);
                }
                if (rel != 0) {
                    MatMulPoint_1cb8e0(out, &mtx, out);
                }
                if (fl2 == 0 || (f32)FabsDouble_1283a0((f64)(out->y - tgt->y)) <= 40.0f) {
                    return 1;
                }
                continue;
            }
            t = 19600 - d;
            if (!(best <= t)) {
                best = t;
                VecCopy_1cbe30(&vF0, &vE0);
            }
            step *= D_0047D354;
            VecScale_1cbca0(&v100, &v110, step);
            VecAdd_1cbdc0(&v100, &v100, tgt);
            continue;
        }
        if (!(d <= 160000)) {
            if (VecDistSqXZ_1cb390(&vC0, &v180) <= 160000) {
                ClosestPointOnSegment_1c9f60(&vA0, &vC0, &vD0, &v180);
                t = VecDistSqXZ_1cb390(&vA0, &v180);
                if (!(160000 <= t)) {
                    VecCopy_1cbe30(out, &vA0);
                } else {
                    d = sqrtf(160000 - t);
                    VecSub_1cbd00(&v110, &vE0, &vA0);
                    VecNormalize_1cbb80(&v110, &v110);
                    VecScale_1cbca0(&v110, &v110, d);
                    VecAdd_1cbdc0(out, &v110, &vA0);
                }
                if (rel != 0) {
                    MatMulPoint_1cb8e0(out, &mtx, out);
                }
                if (fl2 == 0 || (f32)FabsDouble_1283a0((f64)(out->y - tgt->y)) <= 40.0f) {
                    return 1;
                }
                continue;
            }
            t = d - 160000;
            if (!(best <= t)) {
                best = t;
                VecCopy_1cbe30(&vF0, &vE0);
            }
            step *= D_0047DCF4;
            VecScale_1cbca0(&v100, &v110, step);
            VecAdd_1cbdc0(&v100, &v100, &v180);
            continue;
        }
        if (NavNodeGetReachable_311960(pair[1]) == 0) {
            Vec3ToVec4W1_311970(pair[0], &vE0);
        }
        if (rel != 0) {
            MatMulPoint_1cb8e0(out, &mtx, &vE0);
        } else {
            VecCopy_1cbe30(out, &vE0);
        }
        if (fl2 == 0 || (f32)FabsDouble_1283a0((f64)(out->y - tgt->y)) <= 40.0f) {
            return 1;
        }
    }
    if (rel != 0) {
        MatMulPoint_1cb8e0(out, &mtx, &vF0);
    } else {
        VecCopy_1cbe30(out, &vF0);
    }
    if (!(VecDistSq_1cb3c0(tgt, out) < 1000000)) {
        return 0;
    }
    if (fl != 0) {
        if (!((f32)FabsDouble_1283a0((f64)(out->y - tgt->y)) <= 40.0f)) {
            return 0;
        }
    }
    return 1;
}
