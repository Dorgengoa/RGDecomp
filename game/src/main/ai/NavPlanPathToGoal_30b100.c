/* rgp:protos */
#define RGP_SELF_NavPlanPathToGoal_30b100 1
#include "port/game_protos.h"
#line 1
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

typedef struct Slot {
    u8 pad0[0x10];
    s32 x10;
    s32 x14;
    f32 x18;
    u8 pad1C[0x4];
} Slot;

typedef struct Path {
    Slot slot[4];
    s32 x80[4];
    s8 x90;
    s8 x91;
    s16 x92;
    s32 x94;
} Path;

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
extern s32 strcmp(s32, s32);
extern f32 D_0047F1F0;
extern f32 D_0047F1F4;
extern f32 D_0047F1F8;
extern f32 D_0047F1FC;

s32 NavPlanPathToGoal_30b100(s32 arg0, V4 *pos, s32 id, Path *path) {
    s32 pr[2];
    V4 v1F0 __attribute__((aligned(16)));
    V4 v1E0 __attribute__((aligned(16)));
    V4 v1D0 __attribute__((aligned(16)));
    V4 v1C0 __attribute__((aligned(16)));
    V4 v1B0 __attribute__((aligned(16)));
    V4 v1A0 __attribute__((aligned(16)));
    M44 mtx __attribute__((aligned(16)));
    V4 v150 __attribute__((aligned(16)));
    f32 tbl[4] __attribute__((aligned(16)));
    V4 v130 __attribute__((aligned(16)));
    V4 v120 __attribute__((aligned(16)));
    V4 v110 __attribute__((aligned(16)));
    s32 best;
    s32 ctx;
    s32 e;
    f32 off;
    s32 m;
    u32 cnt;
    u32 j;
    f32 da;
    s32 a;
    s32 q;
    s32 n;
    f32 d;
    f32 lim;
    s32 c;
    f32 r2;
    s8 f;
    s32 nn;
    f32 lim2;
    f32 d2;

    if (NavMgrGetCurrent_30cab0(arg0) == 0 || path == 0) {
        return 0;
    }
    best = 0;
    ctx = NavMgrGetCurrent_30cab0(arg0);
    if (id < 10000) {
        e = MapFindBlockAtPos_1e3a00(((s32)GetMapMgr_201a90()), pos, 0.0f);
        if (e != 0) {
            id = MapBlockGetNavGraphId_1e0050(e);
        }
    }
    off = 0.0f;
    if (id != NavGraphGetId_310e90(ctx)) {
        m = NavMgrFindGraphById_30cae0(arg0, id);
        if (m != 0) {
            cnt = ((unsigned short)NavGraphGetNodeCount_310cb0(ctx));
            e = NavGraphGetNodes_310cc0(ctx);
            for (j = 0; j < cnt; j++, e += 0x24) {
                if (NavNodeGetLinkName_3119b0(e) == 0) {
                    continue;
                }
                if (strcmp(NavNodeGetLinkName_3119b0(e), ((s32)NavGraphGetName_310eb0(m))) != 0) {
                    continue;
                }
                if (best == 0) {
                    best = e;
                } else if ((s16)((short)NavNodeGetReachable_311960(e)) == (s16)((short)NavNodeGetReachable_311960(best))) {
                    Vec3ToVec4W1_311970(best, &v1F0);
                    Vec3ToVec4W1_311970(e, &v1E0);
                    da = (f32)FabsDouble_1283a0((f64)(v1F0.y - pos->y));
                    if ((f32)FabsDouble_1283a0((f64)(v1E0.y - pos->y)) < da) {
                        best = e;
                    }
                } else if ((s16)((short)NavNodeGetReachable_311960(e)) != 0) {
                    best = e;
                }
            }
            if (best == 0) {
                return 0;
            }
            if (((short)NavNodeGetReachable_311960(best)) != 0) {
                off = NavNodeGetDist_311910(best);
                a = ((short)NavNodeGetId_3119c0(best));
                q = NavGraphFindEdge_3106e0(ctx, a, ((short)NavNodeGetPrev_311920(best)));
                if (q != 0) {
                    off -= NavEdgeGetCost_3116e0(q);
                }
            }
            ctx = m;
            cnt = ((unsigned short)NavGraphGetNodeCount_310cb0(m));
            e = NavGraphGetNodes_310cc0(m);
            best = 0;
            for (j = 0; j < cnt; j++, e += 0x24) {
                if (NavNodeGetLinkName_3119b0(e) == 0) {
                    continue;
                }
                if (strcmp(NavNodeGetLinkName_3119b0(e), ((s32)NavGraphGetName_310eb0(NavMgrGetCurrent_30cab0(arg0)))) != 0) {
                    continue;
                }
                if (best == 0) {
                    best = e;
                } else if ((s16)((short)NavNodeGetReachable_311960(e)) == (s16)((short)NavNodeGetReachable_311960(best))) {
                    Vec3ToVec4W1_311970(best, &v1D0);
                    Vec3ToVec4W1_311970(e, &v1C0);
                    da = (f32)FabsDouble_1283a0((f64)(v1D0.y - pos->y));
                    if ((f32)FabsDouble_1283a0((f64)(v1C0.y - pos->y)) < da) {
                        best = e;
                    }
                } else if ((s16)((short)NavNodeGetReachable_311960(e)) != 0) {
                    best = e;
                }
            }
            if (best == 0) {
                return 0;
            }
            Vec3ToVec4W1_311970(best, &v1B0);
            NavGraphSetGoalPos_311630(m, &v1B0);
            if (((short)NavGraphGetGoalNodeId_310e70(m)) != ((short)NavNodeGetId_3119c0(best))) {
                NavSearchFromNode_30e810(m, ((short)NavNodeGetId_3119c0(best)));
            }
        }
    }
    NavXformPointToLocal_310d50(ctx, &v1A0, pos);
    NavGraphGetXform_310e40(ctx, &mtx);
    path->x92 = ((short)NavGraphGetGoalNodeId_310e70(ctx));
    path->x90 = 0;
    path->x91 = 0;
    path->x94 = id;
    n = ((s32)NavFindNearestEdgePoint_310380(ctx, &v150, &v1A0, 1));
    if (n == 0) {
        return 0;
    }
    d = VecDistSqXZ_1cb390(&v150, &v1A0);
    tbl[0] = D_0047F1F0;
    tbl[1] = D_0047F1F4;
    tbl[2] = D_0047F1F8;
    tbl[3] = D_0047F1FC;
    lim = tbl[NavEdgeGetFlags_311710(n) & 0xFF];
    best = 0;
    if ((NavEdgeGetFlags_311710(n) & 0xFF00) >> 8 == 2 || (NavEdgeGetFlags_311710(n) & 0xFF00) >> 8 == 3) {
        a = ((short)NavEdgeGetNodeA_311700(n));
        if (NavEdgeGetDirFlag_311660(n, a, ((short)NavEdgeGetNodeB_3116f0(n))) == 0) {
            best = ((s32)NavGraphGetNode_310cd0(ctx, ((short)NavEdgeGetNodeA_311700(n))));
            c = ((s32)NavGraphGetNode_310cd0(ctx, ((short)NavEdgeGetNodeB_3116f0(n))));
            Vec3ToVec4W1_311970(c, &v130);
            r2 = (NavEdgeGetCost_3116e0(n) / 3.5f) * (NavEdgeGetCost_3116e0(n) / 3.5f);
            if (VecDistSq_1cb3c0(&v130, &v1A0) < r2) {
                best = c;
            }
        } else {
            a = ((short)NavEdgeGetNodeB_3116f0(n));
            if (NavEdgeGetDirFlag_311660(n, a, ((short)NavEdgeGetNodeA_311700(n))) == 0) {
                best = ((s32)NavGraphGetNode_310cd0(ctx, ((short)NavEdgeGetNodeB_3116f0(n))));
                c = ((s32)NavGraphGetNode_310cd0(ctx, ((short)NavEdgeGetNodeA_311700(n))));
                Vec3ToVec4W1_311970(c, &v120);
                r2 = (NavEdgeGetCost_3116e0(n) / 3.5f) * (NavEdgeGetCost_3116e0(n) / 3.5f);
                if (VecDistSq_1cb3c0(&v120, &v1A0) < r2) {
                    best = c;
                }
            }
        }
        if (best != 0) {
            if (NavPathFindWarpWaypoint_30aca0(arg0, path, ctx, best, n, off) != 0) {
                return 1;
            }
            NavPathAppendNode_30b020(arg0, ctx, path, best, NavEdgeGetFlags_311710(n), off);
            best = NavNodeGetPrevNode_310c60(ctx, ((short)NavNodeGetId_3119c0(best)));
            if (best == 0) {
                return 1;
            }
        }
    } else if (!(d <= lim)) {
        {
            u8 *p_ = (u8 *)pr;
            u32 n_ = 8;
            if (p_ != 0) {
                while (n_ != 0) {
                    *p_ = 0;
                    n_--;
                    p_++;
                }
            }
        }
        pr[0] = ((s32)NavGraphGetNode_310cd0(ctx, ((short)NavEdgeGetNodeA_311700(n))));
        pr[1] = ((s32)NavGraphGetNode_310cd0(ctx, ((short)NavEdgeGetNodeB_3116f0(n))));
        da = NavNodeGetDist_311910(pr[0]);
        if (NavPathFindWarpWaypoint_30aca0(arg0, path, ctx, (da < NavNodeGetDist_311910(pr[1])) ? pr[0] : pr[1], n, off) != 0) {
            return 1;
        }
        NavXformPointToWorld_310d10(ctx, &path->slot[path->x90], &v150);
        path->slot[path->x90].x10 = NavNodeGetFlags_3119a0(pr[0]) & NavNodeGetFlags_3119a0(pr[1]);
        path->slot[path->x90].x14 = -((short)NavEdgeGetId_311720(n)) - 1;
        path->x80[path->x90] = NavEdgeGetFlags_311710(n);
        path->slot[path->x90].x18 = off + NavNodeGetDist_311910(pr[0]);
        if (off + NavNodeGetDist_311910(pr[1]) < path->slot[path->x90].x18) {
            path->slot[path->x90].x18 = off + NavNodeGetDist_311910(pr[1]);
        }
        path->x90++;
    }
    if (best == 0) {
        a = ((short)NavEdgeGetNodeA_311700(n));
        if (NavEdgeGetDirFlag_311660(n, a, ((short)NavEdgeGetNodeB_3116f0(n))) == 0) {
            best = ((s32)NavGraphGetNode_310cd0(ctx, ((short)NavEdgeGetNodeB_3116f0(n))));
        } else {
            a = ((short)NavEdgeGetNodeB_3116f0(n));
            if (NavEdgeGetDirFlag_311660(n, a, ((short)NavEdgeGetNodeA_311700(n))) == 0) {
                best = ((s32)NavGraphGetNode_310cd0(ctx, ((short)NavEdgeGetNodeA_311700(n))));
            } else {
                f = 0;
                if (!(NavEdgeGetFlags_311710(n) & 0x10000)) {
                    f |= 1;
                }
                if (!(NavEdgeGetFlags_311710(n) & 0x20000)) {
                    f |= 2;
                }
                if (f >= 1 && f <= 2) {
                    if (f == 1) {
                        best = ((s32)NavGraphGetNode_310cd0(ctx, ((short)NavEdgeGetNodeB_3116f0(n))));
                    } else {
                        best = ((s32)NavGraphGetNode_310cd0(ctx, ((short)NavEdgeGetNodeA_311700(n))));
                    }
                } else {
                    best = NavFindNearestNode_310820(ctx, &v1A0, 1);
                }
            }
        }
        if (best != 0 && NavPathFindWarpWaypoint_30aca0(arg0, path, ctx, best, n, off) != 0) {
            return 1;
        }
    }
    if (best == 0) {
        return 0;
    }
    Vec3ToVec4W1_311970(best, &v110);
    d2 = VecDistSqXZ_1cb390(&v1A0, &v110);
    lim2 = tbl[1];
    nn = NavNodeGetPrevNode_310c60(ctx, ((short)NavNodeGetId_3119c0(best)));
    if (nn != 0) {
        q = NavGraphFindEdge_3106e0(ctx, ((short)NavNodeGetId_3119c0(best)), ((short)NavNodeGetId_3119c0(nn)));
        if (q != 0) {
            lim2 = tbl[NavEdgeGetFlags_311710(q) & 0xFF];
        }
    } else if (path->x90 > 0 && path->slot[path->x90 - 1].x14 == ((short)NavGraphGetGoalNodeId_310e70(ctx))) {
        return 1;
    }
    if (nn == 0 || !(d2 <= lim2) || !(v110.y - v1A0.y <= 95.0f) || (NavNodeGetFlags_3119a0(best) & 4) ||
        (NavEdgeGetFlags_311710(n) & 0xFF00) >> 8 == 2 || (NavEdgeGetFlags_311710(n) & 0xFF00) >> 8 == 3) {
        NavPathAppendNode_30b020(arg0, ctx, path, best, NavEdgeGetFlags_311710(n), off);
    }
    while (path->x90 < 4) {
        nn = NavNodeGetPrevNode_310c60(ctx, ((short)NavNodeGetId_3119c0(best)));
        if (nn == 0) {
            return 1;
        }
        q = NavGraphFindEdge_3106e0(ctx, ((short)NavNodeGetId_3119c0(best)), ((short)NavNodeGetId_3119c0(nn)));
        if (q == 0) {
            return 1;
        }
        NavPathAppendNode_30b020(arg0, ctx, path, nn, NavEdgeGetFlags_311710(q), off);
        best = nn;
    }
    return 1;
}
