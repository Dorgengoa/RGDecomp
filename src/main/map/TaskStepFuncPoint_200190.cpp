#include "types.h"
typedef unsigned __int128 u128;

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct Mtx30 {
    u8 pad[0x30];
} Mtx30;

typedef struct Buf40 {
    u8 pad[0x40];
} Buf40;

typedef struct Wk30 {
    u8 pad[0x30];
} Wk30;

typedef struct Ent {
    s16 x0;
    u8 pad2[0x20 - 2];
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    u8 pad30[0x10];
    s32 x40;
} Ent;

typedef struct Obj {
    u8 pad0[0x180];
    Vec4 x180;
    u8 pad190[0x1F0 - 0x190];
    u8 x1F0[4];
} Obj;

typedef struct Pl {
    u8 pad0[0x3D8];
    s32 x3D8;
} Pl;

typedef struct Sub18 {
    u8 pad0[6];
    s16 x6;
    u8 pad8[2];
    s16 xA;
    u8 padC[0x30 - 0xC];
    s16 x30;
    u8 pad32[0x18E - 0x32];
    s16 x18E;
} Sub18;

typedef struct Sub14 {
    u8 pad0[8];
    s32 x8;
} Sub14;

typedef struct Gm {
    u8 pad0[0x14];
    Sub14 *x14;
    Sub18 *x18;
} Gm;

typedef struct It {
    u8 pad0[0x60];
    s32 x60;
    u8 pad64[4];
    s32 x68;
} It;

class Chr {
public:
    virtual s32 v0(s32);
    virtual s32 v1(s32);
    virtual s32 v2(s32);
    virtual s32 v3(s32);
    virtual s32 v4(s32);
    virtual s32 v5(s32);
    virtual s32 v6(s32);
    virtual s32 v7(s32);
    virtual s32 v8(s32);
    virtual s32 v9(s32);
    virtual s32 v10(s32);
    virtual s32 v11(s32);
    virtual s32 v12(s32);
    virtual s32 v13(s32);
    virtual s32 v14(s32);
    virtual s32 v15(s32);
    virtual s32 v16(s32);
    virtual s32 v17(s32);
    virtual s32 v18(s32);
    virtual s32 v19(s32);
    virtual s32 v20(s32);
    virtual s32 v21(s32);
    virtual s32 v22(s32);
    virtual s32 v23(s32);
    virtual s32 v24(s32);
    virtual s32 v25(s32);
    virtual s32 v26(s32);
    virtual s32 v27(s32);
    virtual s32 v28(s32);
    virtual s32 v29(s32);
    virtual s32 v30(s32);
    virtual s32 v31(s32);
    virtual s32 v32(s32);
    virtual s32 v33(s32);
    virtual s32 v34(s32);
    virtual s32 v35(s32);
    virtual s32 v36(s32);
    virtual s32 v37(s32);
    virtual s32 v38(s32);
    virtual s32 v39(s32);
    virtual s32 v40(s32);
    virtual s32 v41(s32);
    virtual s32 v42(s32);
    virtual s32 v43(s32);
    virtual s32 v44(s32);
    virtual s32 v45(s32);
    virtual s32 v46(s32);
    virtual s32 v47(s32);
    virtual s32 v48(s32);
    virtual s32 v49(s32);
    virtual s32 v50(s32);
    virtual s32 v51(s32);
    virtual s32 v52(s32);
    virtual s32 v53(s32);
    virtual s32 v54(s32);
    virtual s32 v55(s32);
    virtual s32 v56(s32);
    virtual s32 v57(s32);
    virtual s32 v58();
    virtual s32 v59(s32);
    virtual s32 v60(s32);
    virtual s32 v61(s32);
    virtual s32 v62(s32);
    virtual s32 v63(s32);
    virtual s32 v64(s32);
    virtual s32 v65();
    virtual s32 v66(s32);
    virtual s32 v67(s32);
    virtual s32 v68(s32);
    virtual s32 v69(s32);
    virtual s32 v70(s32);
    virtual s32 v71(s32);
    virtual s32 v72(s32);
    virtual s32 v73(s32);
    virtual s32 v74(s32);
};

extern "C" {
Gm *GetGameData_1fede0(void);
s32 GetMapMgr_201a90(void);
s32 GetActionMgr_1fdb50(void);
Pl *ActionMgrFindById_233b50(s32, s32);
void CharaGetPos_2388a0(Pl *, Vec4 *);
s32 MapSlotsFindBlockById_1e49b0(s32, s16, s32);
s16 MapDataGetParentId_1e7bb0(s32);
s32 MapFindAreaSlotById_1e4cb0(s32, s16);
s32 IsInBattle_288420(void);
s32 GetGameMode_1f59c0(void);
s32 MapBlockGetEntries_1dfd30(s32);
s32 MapBlockGetEntryCount_1dfd20(s32);
Ent *MapEntryGetRec_1e1240(s32);
Obj *MapEntryAsObjRelated_1e1230(s32);
f32 VecDistSq_1cb3c0(Vec4 *, Vec4 *);
f64 FabsDouble_1283a0(f64);
void MotionListResetAll_171e00(u8 *);
void ModelObjPlayMotionByName_1867a0(Obj *, u8 *, s32);
s32 PartyCountMembers_3c2010(Sub18 *, s32, s32);
s32 PartyGetMemberId_3c2490(Sub18 *, s32);
Chr *PoolGetUsedElem_36acb0(s32, s32);
void EffectPlayHeal_2d80e0(s32);
s32 GetCurrentScene_1f5be0(void);
s32 GameSceneSoundSlot1GetHandle_1d07b0(s32);
s32 SoundNextPlayHandle_1b81c0(void);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
void SavePointActivate_426480(Ent *);
u8 SavePointAreaCompleteCheckMaybe_3ec7e0(Gm *);
s32 SceneSoundGetSlot0HandleCur_207df0(void);
void MatRotY_1cb200(Mtx30 *, f32);
s32 MapDataIsJasterOnly_1e7a90(s32);
s32 PartyCountExcludingLeader_3c2610(Sub18 *, s32, s32);
s32 PartyGetNonLeaderId_3c2750(Sub18 *, s32);
void MatMulPoint_1cb8e0(Vec4 *, Mtx30 *, Vec4 *);
f32 Atan2f_1291a8(f32, f32);
void CharaPlaceAt_2f3a40(s32, Vec4 *, s32, f32);
s32 CharaIsStandOrWalkMaybe_20fe90(Pl *);
void MesShowMsgByIndex_278fd0(s32, s32);
void MinimapSetCurAllExplored_32b6c0(s32);
void GameReqPushWarp_285ea0(s32, s32, s16, s32);
void FuncPointDeactivate_2000e0(s32, s32);
void PartySetNearestFuncPoint_3c9790(Sub18 *, s32, f32);
s32 MapDataGetModel_1e7810(s32);
void FuncDataTableIterBegin_1908e0(u8 *, s32);
It *FuncDataTableIterNext_1908b0(u8 *);
void NodeCalcWorldMatrix_186130(It *, Buf40 *);
s32 PointInOrientedBox_1c8430(Vec4 *, Buf40 *);
void ActionPacketReset_3e3d00(Wk30 *);
void ActionPacketInitFuncPointEnter_3e3930(Wk30 *, s32, s32);
void EventFireTriggers_3e2660(Wk30 *, s32);
f32 sqrtf(f32);
extern f32 D_0045B080[];
extern u8 D_0045BFF8[];
extern u8 D_0045C000[];
extern f32 D_0047D85C;
typedef struct {f32 f0;f32 f1;f32 f2;f32 f3;} PrivateConstants0;
extern volatile PrivateConstants0 D_0047E580 __attribute__((section(".sdata")));



extern s32 D_00481B2C;
extern u8 D_00481B30;
extern u8 D_00481B34;
void TaskStepFuncPoint_200190(void);
}

static inline f32 *WriteNext(f32 *p,f32 v){*p=v;return p+1;}
extern "C" void TaskStepFuncPoint_200190(void)
{
    Vec4 pos;
    Vec4 v;
    Vec4 q;
    Mtx30 m;
    Vec4 pos2;
    Vec4 c;
    Buf40 buf;
    Wk30 wk;
    s32 ctx;
    bool nearby;
    bool hit;
    u32 n;
    s32 id;
    u32 n2;
    s32 id2;
    f32 d;
    f32 bestd;
    f32 k10;
    f32 r2;
    f32 k100;
    f32 k2;
    f32 k;
    f32 kd;
    f32 kn;
    f32 h;
    Gm *gm;
    s32 a;
    Pl *pl;
    s32 t;
    s32 best;
    s32 p;
    s32 cnt;
    s32 i;
    Ent *e;
    Obj *o;
    s32 j;
    s32 w;
    Chr *ch;
    s32 g;
    Pl *pl2;
    s32 x;
    u8 *lst;
    It *it;
    bool ok;

    gm = GetGameData_1fede0();
    a = GetMapMgr_201a90();
    ctx = GetActionMgr_1fdb50();
    pl = ActionMgrFindById_233b50(ctx, gm->x18->x18E);
    if (pl == 0) {
        return;
    }
    CharaGetPos_2388a0(pl, &pos);
    t = MapSlotsFindBlockById_1e49b0(a, gm->x18->x30, 0);
    if (t == 0) {
        return;
    }
    if (MapFindAreaSlotById_1e4cb0(a, MapDataGetParentId_1e7bb0(t)) == 0) {
        return;
    }
    if (IsInBattle_288420() == 0 && GetGameMode_1f59c0() != 7) {
        best = -1;
        bestd = -1.0f;
        nearby = false;
        if (pl->x3D8 & 1) {
            p = MapBlockGetEntries_1dfd30(t);
            cnt = MapBlockGetEntryCount_1dfd20(t);
            i = 0;
            k = D_0045B080[0];
            k10 = 10.0f * k;
            r2 = 0.75f * k;
            r2 = r2 * r2;
            k2 = 2.0f * k;
            kn = -1.0f * k;
            k100 = k10 * k10;
            kd = D_0047D85C * k;
            for (; i < cnt; i++, p += 0x7A0) {
                e = MapEntryGetRec_1e1240(p);
                if (e == 0) {
                    continue;
                }
                if (!(e->x40 & 1)) {
                    continue;
                }
                o = MapEntryAsObjRelated_1e1230(p);
                *(u128 *)&v = *(u128 *)&o->x180;
                d = VecDistSq_1cb3c0(&pos, &v);
                h = (f32)FabsDouble_1283a0((f64)(pos.y - v.y));
                if (best < 0 || (!(bestd <= d) && h < k10)) {
                    best = e->x0;
                    bestd = d;
                }
                w = 0;
                if (d <= r2) {
                    nearby = true;
                    if (D_00481B2C != e->x0) {
                        MotionListResetAll_171e00(o->x1F0);
                        ModelObjPlayMotionByName_1867a0(o, D_0045BFF8, 6);
                        hit = false;
                        n = PartyCountMembers_3c2010(gm->x18, 1, 1);
                        for (j = 0; (s32)j < (s32)n; j++) {
                            id = PartyGetMemberId_3c2490(gm->x18, j);
                            ch = PoolGetUsedElem_36acb0(gm->x14->x8, id);
                            if (ch == 0) {
                                continue;
                            }
                            if (ch->v58() < ch->v72(1) || ch->v65() < ch->v74(1)) {
                                EffectPlayHeal_2d80e0(id);
                                hit = true;
                            }
                        }
                        if (hit) {
                            g = GameSceneSoundSlot1GetHandle_1d07b0(GetCurrentScene_1f5be0());
                            SoundPlayScaledVolume_1b9520(g, 0x4A, SoundNextPlayHandle_1b81c0(), 1.0f);
                        }
                        SavePointActivate_426480(e);
                        D_00481B2C = e->x0;
                        D_00481B34 = 1;
                        w = (u8)SavePointAreaCompleteCheckMaybe_3ec7e0(gm);
                        if (w == 0) {
                            g = SceneSoundGetSlot0HandleCur_207df0();
                            SoundPlayScaledVolume_1b9520(g, 0x17, SoundNextPlayHandle_1b81c0(), 1.0f);
                        }
                        MatRotY_1cb200(&m, e->x2C);
                        q.x = e->x20;
                        q.y = e->x24;
                        q.z = e->x28;
                        q.w = 1.0f;
                        if (IsInBattle_288420() == 0 && MapDataIsJasterOnly_1e7a90(t) == 0) {
                            n2 = PartyCountExcludingLeader_3c2610(gm->x18, 1, 1);
                            for (j = 0; (s32)j < (s32)n2; j++) {
                                id2 = PartyGetNonLeaderId_3c2750(gm->x18, j);
                                pl2 = ActionMgrFindById_233b50(ctx, id2);
                                if (pl2 == 0) {
                                    continue;
                                }
                                CharaGetPos_2388a0(pl2, &pos2);
                                if (VecDistSq_1cb3c0(&q, &pos2) <= k100) {
                                    continue;
                                }
{f32 *writer=(f32 *)&c;writer=WriteNext(writer,D_0047E580.f0);writer=WriteNext(writer,D_0047E580.f1);writer=WriteNext(writer,D_0047E580.f2);writer=WriteNext(writer,D_0047E580.f3);}
                                c.z = k2;
                                if (n2 == 2) {
                                    if (j == 0) {
                                        c.x = k;
                                        c.y = 0.0f;
                                        c.w = 1.0f;
                                        c.z = kd;
                                    } else {
                                        c.x = kn;
                                        c.y = 0.0f;
                                        c.w = 1.0f;
                                        c.z = kd;
                                    }
                                }
                                MatMulPoint_1cb8e0(&pos2, &m, &c);
                                CharaPlaceAt_2f3a40(id2, &pos2, 0xF, Atan2f_1291a8(e->x20 - pos2.x, e->x28 - pos2.z));
                            }
                        }
                    } else if (D_00481B34 == 0) {
                        MotionListResetAll_171e00(o->x1F0);
                        ModelObjPlayMotionByName_1867a0(o, D_0045C000, 4);
                        D_00481B34 = 1;
                    }
                    if (D_00481B30 == 0 && w == 0 && GetGameMode_1f59c0() == 6 && CharaIsStandOrWalkMaybe_20fe90(pl) != 0) {
                        MesShowMsgByIndex_278fd0(0, -1);
                        D_00481B30 = 1;
                    }
                    if (w != 0) {
                        MinimapSetCurAllExplored_32b6c0(1);
                        GameReqPushWarp_285ea0(-1, 0x352, gm->x18->x6, 0);
                    }
                } else if (D_00481B2C == e->x0) {
                    FuncPointDeactivate_2000e0(1, 0);
                }
            }
        }
        if (!nearby && D_00481B2C >= 0) {
            FuncPointDeactivate_2000e0(1, 0);
        }
        PartySetNearestFuncPoint_3c9790(gm->x18, best, sqrtf(bestd));
    }
    x = MapFindAreaSlotById_1e4cb0(GetMapMgr_201a90(), gm->x18->xA);
    if (x == 0) {
        return;
    }
    x = MapDataGetModel_1e7810(x);
    if (x == 0) {
        return;
    }
    lst = (u8 *)x + 0x1664;
    FuncDataTableIterBegin_1908e0(lst, 6);
    while ((it = FuncDataTableIterNext_1908b0(lst)) != 0) {
        NodeCalcWorldMatrix_186130(it, &buf);
        if (PointInOrientedBox_1c8430(&pos, &buf) == 0) {
            continue;
        }
        ok = false;
        id = -1;
        if (it->x60 == 0) {
            id = it->x68;
            ok = true;
        } else if (it->x60 == 1) {
            id = it->x68;
            ok = true;
        }
        if (ok) {
            g = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(&wk);
            ActionPacketInitFuncPointEnter_3e3930(&wk, g, id);
            EventFireTriggers_3e2660(&wk, 0);
        }
    }
}
