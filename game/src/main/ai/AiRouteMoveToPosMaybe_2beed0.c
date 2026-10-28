/* rgp:protos */
#define RGP_SELF_AiRouteMoveToPosMaybe_2beed0 1
#define RGP_SELF_Fabs 1
#define RGP_SELF_FindNode 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_dead_assignments off

typedef struct {
    f32 x, y, z, w;
} Vec;

typedef struct {
    Vec pos;
    s32 flags;
    s32 id;
    u8 pad18[8];
} Wp;

typedef struct {
    u8 pad0[0x1C0];
    Wp wp[4];           /* 0x1C0 */
    u32 info[4];        /* 0x240 */
    s8 n;               /* 0x250 */
    s8 cur;
    s16 f252;
    s32 f254;
    u8 pad258[8];
    s8 f260;
    u8 pad261[2];
    s8 f263;
} Ai;

typedef struct {
    u8 pad0[0x3D8];
    u32 f3D8;
    u8 pad3DC[0x668];
    u32 fA44;
} Chr;

typedef struct {
    Chr *me;
} Tgt;

static inline f32 Fabs(f32 x) {
    return (x < 0.0f) ? -x : x;
}

#define KIND(x) (((x) & 0xFF00) >> 8)

/*rgp*/
/*rgp*/

static inline s32 FindNode(s32 nav, s32 node, Vec *buf, Vec *pos) {
    if (node != 0 && KIND(NavEdgeGetFlags_311710(node)) == 3) return node;
    return ((s32)NavFindNearestEdgePoint_310380(nav, buf, pos, 0));
}

#define KIND_UNUSED(x) (((x) & 0xFF00) >> 8)

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

extern f32 D_0047D354;
extern f32 D_0047D5D0;
extern f32 D_0047ED50;
extern f32 D_0047ED54;
extern f32 D_0047ED58;
extern f32 D_0047ED5C;
extern f32 D_0047ED60;
extern f32 D_0047ED64;
extern f32 D_0047ED68;
extern f32 D_0047ED6C;
extern f32 D_0047ED70;
extern f32 D_0047ED74;
extern f32 D_0047ED78;
extern f32 D_0047ED7C;

void AiRouteMoveToPosMaybe_2beed0(Ai *ai, Tgt *tg, Vec *dst, Chr *en) {
    Vec pos __attribute__((aligned(16)));
    Vec v2D0 __attribute__((aligned(16)));
    Vec v2C0 __attribute__((aligned(16)));
    Vec v2B0 __attribute__((aligned(16)));
    Vec v2A0 __attribute__((aligned(16)));
    Vec v290 __attribute__((aligned(16)));
    Vec v280 __attribute__((aligned(16)));
    Vec v270 __attribute__((aligned(16)));
    Vec v260 __attribute__((aligned(16)));
    Vec v250 __attribute__((aligned(16)));
    f32 thr[4] __attribute__((aligned(16)));
    f32 thr2[4] __attribute__((aligned(16)));
    Vec v220 __attribute__((aligned(16)));
    Vec v210 __attribute__((aligned(16)));
    Vec v200 __attribute__((aligned(16)));
    f32 thr3[4] __attribute__((aligned(16)));
    Vec v1E0 __attribute__((aligned(16)));
    Vec v1D0 __attribute__((aligned(16)));
    s32 h;
    s8 fA;
    s8 fB;
    s32 cnt;
    s8 b180;
    s32 e17C;
    s8 b160;
    s8 b150;
    s8 b140;
    Chr *me;
    Chr *r;
    Wp *wp;
    s32 nav;
    s32 node;
    s32 near;
    s32 i;
    s32 j;
    s32 k;
    s8 ok;
    u32 info;
    s32 kind;
    s32 p;
    s32 q;
    s32 w;
    s32 ra;
    s32 rb;
    s32 t;
    f32 f27;
    f32 f26;
    f32 f25;
    f32 f24;
    f32 f23;
    f32 f22;
    f32 f21;
    f32 f20;
    f32 d;
    f32 len;
    f32 m;

    if (tg == 0 || tg->me == 0) return;
    h = ((s32)GetNavMgr_2d1950());
    nav = NavMgrFindGraphById_30cae0(h, ai->f254);
    GetActionMgr_1fdb50();
    me = tg->me;
    CharaGetPos_2388a0(me, &pos);
    SrtGetPosThunk_1c7430(me, &v2C0);
    node = 0;
    AiSetNavEdgeId_2c0ea0(ai, -1);
    if (nav != 0) {
        node = ((s32)NavFindNearestEdgePoint_310380(nav, &v270, &pos, 0));
        if (node != 0) AiSetNavEdgeId_2c0ea0(ai, ((short)NavEdgeGetId_311720(node)));
    }
    AiCollIgnoreTimerTick_2c10c0(ai, me);
    CharaGetForwardVec_238830(me, &v2D0);
    f27 = AiGetKeepDistanceMaybe_2c0f90(ai);
    f26 = AiGetApproachMarginMaybe_2c0fc0(ai);
    f25 = 60.0f;
    f24 = 45.0f;
    if (ai->n < 3) {
        f24 = f25;
        f25 = 90.0f;
    }
    if (en != 0) {
        SrtGetPosThunk_1c7430(en, &v290);
        p = CharaGetModelObj_2386f0(en);
        q = 0;
        if (p != 0) q = ModelGetRootFrame_1511a0(p);
        if (q != 0) {
            FrameGetWorldPos_148f30(q, &v2A0);
        } else {
            VecCopy_1cbe30(&v2A0, dst);
        }
        if (((short)CharaGetActionMode_213850(en)) == 4) {
            f25 *= 1.5f;
            f24 *= 1.5f;
        }
    } else {
        VecCopy_1cbe30(&v290, dst);
        VecCopy_1cbe30(&v2A0, dst);
    }
    VecCopy_1cbe30(&v2B0, &v2A0);
    near = 1;
    if (VecDistSq_1cb3c0(&v290, &v2A0) < 2.0f && VecDistSq_1cb3c0(&v2C0, &pos) < 6.25f) near = 0;
    if (near != 0) ai->f263 = 0;
    f23 = f27 * f27;
    f20 = AiGetKeepDistanceMaybe_2c0f90(ai) + AiGetApproachMarginMaybe_2c0fc0(ai);
    f22 = VecDistXZ_1cb3f0(&pos, &v2A0);
    f21 = f22 * f22;
    if (me->fA44 & 0x20000) {
        if (AiWarpToWaypointOffscreenMaybe_2bc6c0(ai, me, &v2A0, ai->cur) != 0) return;
    }
    if (ai->n == 0) {
        AiRouteMoveStepMaybe_2bce90(ai, tg, &v2A0, en, near, 1, f22);
        return;
    }
    info = ai->info[ai->cur];
    kind = KIND(info);
    if (kind == 5) AiCollIgnoreTimerStart_2c1140(ai, me, 5);
    fA = 0;
    if (en != 0 && ((short)CharaGetActionMode_213850(en)) == 7) fA = 1;
    i = ai->cur;
    fB = 0;
    cnt = i;
    if (kind == 4 && !(ai->wp[i].pos.y <= 30.0f + pos.y)) fB = 1;
    if (i < ai->n - 1 && ai->wp[i].id > 0 && KIND(ai->info[i + 1]) == 4 && !(ai->wp[i + 1].pos.y <= 30.0f + pos.y)) {
        fB = 1;
        cnt++;
    }
    if (ai->wp[i].id < 0) i++;
    if (ai->wp[cnt].id < 0) cnt++;
    if (!(i < ai->n)) i--;
    if (((short)CharaGetActionMode_213850(me)) == 7) {
        AiLadderPickDir_2bc330(ai, me, en, &v2A0, &v290, i);
        return;
    }
    j = ai->cur;
    if ((u8)((unsigned char)IsInBattle_288420()) == 0) {
        if (((short)CharaGetActionMode_213850(me)) != 4 && ((short)CharaGetActionMode_213850(me)) != 6) {
            if ((fA && ai->n <= 1) || fB) {
                t = AiReqLadderAtWaypoint_2bbfd0(ai, me, en, &v2A0, &v290, cnt);
                if (t == 1) return;
                if (t != 0) {
                    j++;
                    if (!(j < ai->n)) j = ai->n - 1;
                }
            }
        }
    }
    b180 = ai->f260;
    ai->f260 = (info & 0x40000) != 0;
    if (ai->f260 == 1) b180 = 1;
    ok = kind == 3;
    if (!ok) {
        ok = kind == 2;
        if (ok && ai->wp[ai->cur].pos.y < 10.0f + pos.y) ok = 0;
        if (ok == 0 && ai->cur + 1 < ai->n && KIND(ai->info[ai->cur + 1]) == 2 &&
            !(ai->wp[ai->cur + 1].pos.y <= 10.0f + pos.y)) {
            ok = 1;
        }
    }
    if (ok) {
        if (nav != 0 && ai->cur < ai->n - 1) {
            node = NavGraphFindEdge_3106e0(nav, ai->wp[ai->cur].id, ai->wp[ai->cur + 1].id);
            if (node != 0 && KIND(NavEdgeGetFlags_311710(node)) != 2 && KIND(NavEdgeGetFlags_311710(node)) != 3) ok = 0;
        } else {
            ok = 0;
        }
    } else if (nav != 0) {
        if (ai->n > 1 && node != 0 && KIND(NavEdgeGetFlags_311710(node)) == 3) {
            ok = 1;
            if (ai->n > 1) {
                for (k = 0; k < ai->n; k++) {
                    if (ai->wp[k].id == ((short)NavEdgeGetNodeA_311700(node)) || ai->wp[k].id == ((short)NavEdgeGetNodeB_3116f0(node))) {
                        ai->cur = k;
                        j = k;
                        ai->info[k] = NavEdgeGetFlags_311710(node);
                        break;
                    }
                }
            }
        } else if (ai->n == 1) {
            node = FindNode(nav, node, &v260, &v2A0);
            if (node != 0 && KIND(NavEdgeGetFlags_311710(node)) == 3) {
                e17C = NavEdgeNearestNode_30f940(nav, &v2A0, node, 0);
                if (e17C != 0) {
                    t = ((s32)NavGraphGetNode_310cd0(nav, NavEdgeGetOtherNode_3116b0(node, ((short)NavNodeGetId_3119c0(e17C)))));
                    if (t != 0 && ai->wp[0].id == ((short)NavNodeGetId_3119c0(t))) {
                        NavPathAppendNode_30b020(h, nav, &ai->wp[0], e17C, NavEdgeGetFlags_311710(node), 0.0f);
                        ai->info[0] = NavEdgeGetFlags_311710(node);
                        ok = 1;
                    }
                }
            }
        } else if (KIND(ai->info[ai->cur + 1]) == 3 && VecDistSqXZ_1cb390(&pos, &ai->wp[ai->cur]) <= 1600.0f) {
            ok = 1;
            ai->info[ai->cur] = ai->info[ai->cur + 1];
        }
    }
    if (((short)CharaGetActionMode_213850(me)) == 6 && ok == 1) {
        j++;
        ok = 0;
    }
    if ((u8)((unsigned char)IsInBattle_288420()) == 0 && ai->n > 0) {
        if ((((short)CharaGetActionMode_213850(me)) == 4 && ok) || v2A0.y - pos.y < -39.0f || (info & 0x30000)) {
            AiCollIgnoreTimerStart_2c1140(ai, me, 5);
        }
    }
    b160 = 0;
    b150 = 1;
    w = ((s32)GetMapMgr_201a90());
    ra = MapFindBlockAtPos_1e3a00(w, &v2A0, 0.0f);
    rb = MapFindBlockAtPos_1e3a00(w, &pos, 0.0f);
    if (ra != 0 && rb != 0 && MapBlockGetNavGraphId_1e0050(ra) != MapBlockGetNavGraphId_1e0050(rb)) b150 = 0;
    if (f22 <= f20 || (b180 == 1 && f22 <= 1.5f * f20)) {
        d = v2A0.y - pos.y;
        d = (d < 0.0f) ? -d : d;
        if (d < f25 && ai->n < 4 && ok == 0) {
            if (((short)CharaGetActionMode_213850(me)) != 4 || ai->n < 3 || ai->cur != 0) {
                AiSetWaitCounterMaybe_2c0e90(ai, 0);
                if (((short)CharaGetActionMode_213850(me)) == 6) {
                    CharaReqClimbOrFallByHeight_2bd140(ai, me, &v2A0);
                    return;
                }
                if (f22 <= 2500) b160 = 1;
                if (v2A0.y - pos.y < f24) {
                    if ((s8)near == 0) {
                        ai->f263++;
                        if (ai->f263 > 60) {
                            ai->f263 = 60;
                            return;
                        }
                    }
                    if (ai->f260 == 0) ai->f260 = NavEdgeAtPosIsRowLine_2bd1e0(&v2A0, me);
                    AiRouteMoveStepMaybe_2bce90(ai, tg, &v2A0, en, near, b160, f22);
                    return;
                }
            }
        }
    }
    if (ai->wp[0].flags & 0x20) {
        if (!(me->f3D8 & 1) && !(me->f3D8 & 0x10)) return;
        if (((short)AiGetWaitCounterMaybe_2c0f30(ai)) >= 60) {
            AiSetWaitCounterMaybe_2c0e90(ai, 0);
            CharaGetRot_2388b0(me, &v250);
            CharaPlaceAt_2f3a40(((short)CharaGetId_214a80(me)), &ai->wp[0], 0xF, v250.y);
            ai->n = 0;
            ai->cur = 0;
        } else {
            AiSetWaitCounterMaybe_2c0e90(ai, ((short)AiGetWaitCounterMaybe_2c0f30(ai)) + 1);
        }
        return;
    }
    if (ai->n <= 0 || !(ai->cur < ai->n)) {
        AiRouteMoveToTargetMaybe_2bcd90(ai, tg, &v2B0, en, near, 0, f22);
        return;
    }
    {
        f32 *q = (f32 *)(u32)thr;
        q[0] = D_0047ED50;
        q[1] = D_0047ED54;
        q[2] = D_0047ED58;
        q[3] = D_0047ED5C;
    }
    {
        f32 *q = (f32 *)(u32)thr2;
        q[0] = D_0047ED60;
        q[1] = D_0047ED64;
        q[2] = D_0047ED68;
        q[3] = D_0047ED6C;
    }
    if (ok == 0) {
        for (; j < ai->n; j++) {
            wp = &ai->wp[j];
            d = VecDistSqXZ_1cb390(&pos, wp);
            if (ai->wp[j].id == ai->f252 || (ai->wp[j].id < 0 && ai->wp[j + 1].id == ai->f252)) {
                if (AiWarpToWaypointOffscreenMaybe_2bc6c0(ai, me, &v2A0, j) != 0) return;
                if (!(pos.y - v2A0.y <= 100.0f)) {
                    if (((short)CharaGetActionMode_213850(me)) == 6) {
                        CharaReqClimbOrFallByHeight_2bd140(ai, me, &v2A0);
                        return;
                    }
                    AiCollIgnoreTimerStart_2c1140(ai, me, 5);
                    AiPointFromDir_2bcc10(ai, &v2B0, &v280, &pos, &v2A0);
                    AiMoveDispatch_2be5f0(ai, tg, &v2B0, &v280, 0.5f * f26);
                    return;
                }
                if (b150) {
                    b140 = 0;
                    if (d < thr[ai->info[j] & 0xFF]) {
                        b140 = 1;
                    } else if (f21 <= D_0047D354 * VecDistSqXZ_1cb390((Vec *)wp, &v2A0)) {
                        if (v2A0.y - pos.y <= f24) b140 = 1;
                    }
                    if (b140) {
                        ai->cur = j;
                        AiRouteMoveToTargetMaybe_2bcd90(ai, tg, &v2A0, en, near, 0, f22);
                        return;
                    }
                }
            }
            if (j < ai->n - 1 && KIND(ai->info[j + 1]) == 3) {
                AiPointFromDir_2bcc10(ai, &v2B0, &v280, &pos, wp);
                ai->cur = j;
                break;
            }
            if (fB || !(d <= f23 || d <= thr[ai->info[j] & 0xFF]) || !(Fabs(pos.y - ai->wp[j].pos.y) <= 40.0f)) {
                info = ai->info[j];
                if (KIND(info) == 1) {
                    if (AiDirWithinCone_2bcd10(ai, &v220, &v2D0, &pos, wp, thr2[info & 0xFF]) == 0) {
                        AiPointFromChara_2bcca0(ai, &v2B0, me, &v220);
                        ai->cur = j;
                        break;
                    }
                }
                if (j + 1 < ai->n && d <= thr[ai->info[j + 1] & 0xFF]) continue;
                if (j + 1 < ai->n) {
                    ClosestPointOnSegmentXZ_1c9e60(&v200, &ai->wp[j + 1], &pos, &ai->wp[(u32)j]);
                    f20 = VecDistXZ_1cb3f0(&v200, &ai->wp[(u32)j]);
                    thr3[0] = D_0047ED70;
                    thr3[1] = D_0047ED74;
                    thr3[2] = D_0047ED78;
                    thr3[3] = D_0047ED7C;
                    VecSub_1cbd00(&v200, &v200, &ai->wp[(u32)j]);
                    if (!(f20 <= 1.0f)) {
                        v200.x /= f20;
                        v200.y = 0.0f;
                        v200.z /= f20;
                        if (!(f20 <= thr3[ai->info[j + 1] & 0xFF])) f20 = thr3[ai->info[j + 1] & 0xFF];
                        f20 *= 0.75f;
                        VecScale_1cbca0(&v200, &v200, f20);
                        VecAdd_1cbdc0(&v210, &v200, wp);
                    } else {
                        VecCopy_1cbe30(&v210, wp);
                    }
                } else {
                    VecCopy_1cbe30(&v210, wp);
                }
                VecSub_1cbd00(&v280, &v210, &pos);
                len = VecLengthXZ_1cb490(&v280);
                if (!(len <= 1.0f)) {
                    v280.x /= len;
                    v280.y = 0.0f;
                    v280.z /= len;
                    m = 2.0f * f27;
                    if (len < m) len = m;
                    VecScale_1cbca0(&v280, &v280, len);
                    VecAdd_1cbdc0(&v2B0, &pos, &v280);
                } else {
                    VecCopy_1cbe30(&v2B0, &v210);
                }
                v2B0.y = ai->wp[j].pos.y;
                ai->cur = j;
                break;
            } else {
                if (j < ai->n - 1 && (ai->wp[j + 1].flags & 8)) {
                    if (d <= thr[ai->info[j + 1] & 0xFF]) return;
                    AiPointFromDir_2bcc10(ai, &v2B0, &v280, &pos, wp);
                    AiMoveDispatch_2be5f0(ai, tg, &v2B0, &v280, f26);
                    return;
                }
                if ((ai->wp[j].flags & 4) && d < thr[ai->info[j] & 0xFF] && j + 1 < ai->n) {
                    if (AiDirWithinCone_2bcd10(ai, &v1E0, &v2D0, &pos, &ai->wp[j + 1], thr2[ai->info[j] & 0xFF]) == 0) {
                        ai->cur = j;
                        AiPointFromChara_2bcca0(ai, &v2B0, me, &v1E0);
                        break;
                    }
                }
                if (!(d <= thr[ai->info[j] & 0xFF])) {
                    AiPointFromDir_2bcc10(ai, &v2B0, &v280, &pos, wp);
                    ai->cur = j;
                    break;
                }
                continue;
            }
        }
    }
    if (AiWarpToWaypointOffscreenMaybe_2bc6c0(ai, me, &v2A0, j) != 0) return;
    if ((me->fA44 & 0x20000) && !(j < ai->n)) return;
    if (((short)CharaGetActionMode_213850(me)) == 6) {
        CharaReqClimbOrFallByHeight_2bd140(ai, me, &v2B0);
        return;
    }
    if (!(j < ai->n)) {
        AiRouteMoveToTargetMaybe_2bcd90(ai, tg, &v2B0, en, near, 0, f22);
        return;
    }
    if (ok && ((short)CharaGetActionMode_213850(me)) != 4) {
        if (AiRouteSegmentStepMaybe_2bbd00(ai, tg, &v2D0, j) != 0) return;
    } else if (((short)CharaGetActionMode_213850(me)) == 4 && j < ai->n - 1) {
        AiPointFromDir_2bcc10(ai, &v2B0, &v280, &pos, &ai->wp[j + 1]);
        AiMoveDispatch_2be5f0(ai, tg, &v2B0, &v280, f26);
        return;
    }
    if (fB || (fA && ai->n <= 1)) f26 *= D_0047D5D0;
    if (ai->f260 != 0 && f22 < 62500 && ai->n < 3) {
        f26 *= 0.5f;
        r = ((Chr *)AiRouteCalcDirMaybe_2bd2c0(ai, me, &v2B0, &v280, f26, f21));
        if (r != en && r != 0) {
            CharaGetPos_2388a0(r, &v1D0);
            if (fB) {
                len = v1D0.y - pos.y;
                len = (len < 0.0f) ? -len : len;
                if (len < 70.0f) f26 = 0.5f * AiGetApproachMarginMaybe_2c0fc0(ai);
            }
        }
    } else {
        f26 = AiRouteAvoidCharasMaybe_2bd800(ai, tg, &v2B0, &v280, &v2B0, f26, f22);
    }
    AiClimbOrJumpWall_2be720(ai, tg, &v2B0, 0);
    AiMoveDispatch_2be5f0(ai, tg, &v2B0, &v280, f26);
}
