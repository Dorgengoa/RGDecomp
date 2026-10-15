#include "types.h"

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Unit {
    u8 pad0[0x18E];
    s16 x18E;
} Unit;

class VC_0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual struct Route *f(s32 x0);
};

class VC_1 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual s32 f();
};

typedef struct Ent {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Ent;

struct Route {
    u8 pad0[0x10];
    s16 x10;
    u8 pad12[0x2];
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    Ent ent[1];
};

typedef struct L2 {
    u8 pad0[0x8];
    VC_0 *x8;
} L2;

typedef struct L1 {
    u8 pad0[0x38];
    L2 *x38;
} L1;

typedef struct Game {
    u8 pad0[0x8];
    L1 *x8;
    u8 padC[0x4];
    s32 x10;
    u8 pad14[0x4];
    Unit *x18;
    u8 pad1C[0x4];
    s32 x20;
} Game;

typedef struct Btl {
    u8 pad0[0x4344];
    s32 x4344;
    u8 pad4348[0x156C];
    s16 x58B4;
    s16 x58B6;
} Btl;

typedef struct Mgr {
    u8 pad0[0x8];
    s16 x8;
    u8 xA;
} Mgr;

typedef struct Chr {
    u8 pad0[0x464];
    s32 x464;
    u8 x468;
} Chr;

typedef struct Ui {
    u8 pad0[0x90];
    u8 x90;
    u8 x91;
} Ui;

typedef struct Cam {
    u8 pad0[0x30];
} Cam;

extern "C" {
extern f64 Cos_128278(f64);
extern f32 Sinf_128fd0(f32);
extern void GetDrawCtx_15de80(void);
extern s32 ObjRecGetLiveObject_1c3bc0(Btl *, s32);
extern void ObjRecSetFlag2_1c3e80(Btl *, s32, s32);
extern Chr *ObjRecGetLiveObject_1c4a90(Btl *, s32);
extern s32 GetStaticScene_1c6c70(void);
extern f32 VecLengthSq_1cb470(V4 *);
extern void TriCalcBounds_1cb540(V4 *, V4 *, V4 *, V4 *, V4 *);
extern void VecScale_1cbca0(V4 *, V4 *, f32);
extern void VecCopy_1cbe30(V4 *, V4 *);
extern void StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);
extern Chr *GetLiveObjById_1ce420(s32, s32);
extern void ScreenFadeCaptureFrame_1cf550(Btl *);
extern void ScreenFadeDissolveIn_1cf720(Btl *, s32, f32);
extern void ScreenFadeOutColor_1cf730(Btl *, s32, f32, f32, f32);
extern void GameSceneSoundFadeVolume_1d0370(s32, s32, f32);
extern void GameSceneSoundSlot4FadeTo_1d0610(s32, s32, f32);
extern void GameSceneSoundSetPollHold_1d1180(Btl *, s32);
extern s32 MapBlockGetNavGraphId_1e0050(s32);
extern s32 MapBlockGetLocationId_1e0070(s32);
extern void MapSlotsRefreshBlocksEnabled_1e2b70(s32);
extern s32 MapFindBlockAtPos_1e3a00(s32, V4 *, f32);
extern s32 MapDataIsJasterOnly_1e7a90(s32);
extern s32 GetGameMode_1f59c0(void);
extern s32 GetLoaderMgr_1f59d0(void);
extern Btl *GetCurrentScene_1f5be0(void);
extern void CameraSnapReqEye_1f6d60(s32);
extern void CameraSnapReqAt_1f6d70(s32);
extern s32 GetActionMgr_1fdb50(void);
extern Game *GetGameData_1fede0(void);
extern s32 GetWorldDataMgr_1fedf0(void);
extern void PartyLeaderRebuildBlockIdList_2012e0(void);
extern void TaskUpdateMapInfo_201340(void);
extern s32 GetMapMgr_201a90(void);
extern void CharaInvokeInitBt1_212ad0(s32);
extern void CharaInvokeInitNrm_212b30(s32);
extern void CharaResetBattleStateMaybe_212f20(s32, s32);
extern void CharaSetInvincibleTime_2138a0(s32, f32);
extern void CharaSetYaw_2138f0(s32, f32);
extern void CharaSetPos_213a40(s32, V4 *);
extern s32 CharaGetAi_214a10(s32);
extern s32 CharaGetId_214a80(s32);
extern s32 CharaGetActionTable_214cd0(s32);
extern void ActCfgTableRunEvntByName_21f680(s32, s32, void *);
extern s32 ActionMgrGetCharaList_233b40(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaSavePlacedPosMaybe_238270(s32);
extern void CharaGetPos_2388a0(s32, V4 *);
extern void LetterboxSetFade_277ea0(void *, f32, f32, f32);
extern void EventObjMgrResume_27aec0(void);
extern void SetFieldControlActive_27bd30(s32);
extern void SetPendingFadeFrames_27bd50(s32);
extern s32 GetPendingFadeFrames_27bd60(void);
extern s32 HasPendingFadeFrames_27bd70(void);
extern Mgr *GameReqGetWarpArgs_285f80(void);
extern s32 IsInBattle_288420(void);
extern Ui *AiGetNavPath_2c10a0(s32);
extern void PartySnapToGroundMaybe_2f10e0(V4 *);
extern void CharaPlaceAtXyz_2f39f0(s32, s32, f32, f32, f32, f32);
extern void CharaPlaceAt_2f3a40(s32, V4 *, s32, f32);
extern void PartyRefreshMembersMaybe_2f40b0(s32);
extern u8 CharaSysStateField28ValidRelated_3a3920(s32);
extern s32 PartyCountReserve_3c1c20(Unit *, s32, s32);
extern s32 PartyCountMembers_3c2010(Unit *, s32, s32);
extern s32 PartyCountExcludingLeader_3c2610(Unit *, s32, s32);
extern s32 PartyGetNonLeaderId_3c2750(Unit *, s32);
extern s32 PartyGetSlotId_3c3120(Unit *, s32);
extern void StateFlagSet_3ccb70(s32, s32, s32, s32);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern void EventFireTriggers_3e2660(Cam *, u8 *);
extern void ActionPacketInitFieldBeginMaybe_3e3af0(Cam *, Btl *, s32, s32);
extern void ActionPacketReset_3e3d00(Cam *);
extern void InvCleanupRemovedMaybe_3e77b0(Game *, s32, s32);
extern VC_1 *ActorFindById_3eb870(Game *, s32);
extern void HandleEntriesReleaseExcept_3f0aa0(s32, s32);
extern void HandleEntriesReleaseExcept_3f0b90(s32, s32);
extern s32 DListGetHead_42ea60(s32);
extern s32 DListGetNext_42eb30(s32);
extern u8 D_00461B80[];
extern u8 D_00461B90[];
extern u8 D_00461BA0[];
extern f32 D_0047D404;
extern f32 D_0047D7F8;
extern s32 D_004821E0;
extern u8 D_004D7810[];
extern s32 D_004D782C[];
}

static inline s32 Total(Unit *q) {
    return PartyCountMembers_3c2010(q, 1, 1) + PartyCountReserve_3c1c20(q, 1, 1);
}

extern "C" s32 FieldControlBeginMaybe_2f13b0(void) {
    u8 flag;
    V4 d;
    V4 v;
    V4 v180;
    V4 v170;
    V4 v160;
    V4 v150;
    Cam cam;
    V4 v110;
    s32 cnt;
    Game *g;
    s32 w;
    Mgr *b;
    s32 k;
    Route *r;
    s32 st;
    Btl *h;
    s32 fl;
    f32 ang;
    s32 i;
    s32 id;
    s32 u;
    s32 t;
    s32 e;
    s32 a;
    s32 c;
    s32 o;
    s32 x;
    Chr *ch;
    s32 n;
    s32 cc;
    VC_1 *p;
    s32 sv;
    s32 n2;
    s32 o2;
    s32 m;
    s32 j;
    f32 *px;
    f32 *py;
    f32 *pz;

    g = GetGameData_1fede0();
    w = GetActionMgr_1fdb50();
    b = GameReqGetWarpArgs_285f80();
    k = b->x8;
    { Route *t_ = g->x8->x38->x8->f(k); r = t_; }
    if (b->xA != 0) {
        return 0;
    }
    st = GetGameMode_1f59c0();
    if (st == 3) {
        return 0;
    }
    h = GetCurrentScene_1f5be0();
    fl = (u8)StateFlagTest_3ccd70(g->x10, 0x143);
    if (fl != 0) {
        ScreenFadeOutColor_1cf730(h, 1, 0.0f, 0.0f, 0.0f);
    }
    GameSceneSoundSetPollHold_1d1180(h, 0);
    h->x58B4 = 0;
    h->x58B6 = 0;
    if (r != 0) {
        if (r->x10 >= 0) {
            u = ActionMgrFindById_233b50(w, g->x18->x18E);
            if (u == 0) {
                goto done;
            }
            v.x = r->x14;
            v.y = r->x18;
            v.z = r->x1C;
            v.w = 0.0f;
            if (VecLengthSq_1cb470(&v) != 0.0f) {
                VecCopy_1cbe30(&v180, &v);
                CharaSetPos_213a40(u, &v);
                CharaSavePlacedPosMaybe_238270(u);
                CharaSetYaw_2138f0(u, r->x20);
                VecCopy_1cbe30(&v160, &v);
                VecCopy_1cbe30(&v170, &v);
                ang = D_0047D7F8 + r->x20;
                { s32 t_ = PartyCountExcludingLeader_3c2610(g->x18, 1, 1); cnt = t_; }
                for (i = 0; i < cnt; i++) {
                    id = PartyGetNonLeaderId_3c2750(g->x18, i);
                    u = ActionMgrFindById_233b50(w, id);
                    if (u == 0) {
                        continue;
                    }
                    px = &r->ent[i].x;
                    py = &r->ent[i].y;
                    pz = &r->ent[i].z;
                    v.x = *px;
                    v.y = *py;
                    v.z = *pz;
                    v.w = 0.0f;
                    if (VecLengthSq_1cb470(&v) == 0.0f) {
                        d.x = -Sinf_128fd0(ang);
                        d.y = 0.0f;
                        d.z = (f32)-Cos_128278((f64)ang);
                        d.w = 0.0f;
                        VecScale_1cbca0(&d, &d, 30.0f);
                        d.x += r->x14;
                        d.y += r->x18;
                        d.z += r->x1C;
                        CharaPlaceAt_2f3a40(id, &d, 0, ang);
                        CharaSavePlacedPosMaybe_238270(u);
                        ang -= D_0047D404;
                    } else {
                        CharaPlaceAtXyz_2f39f0(id, 0, *px, *py, *pz, r->ent[(u32)i].w);
                        CharaSavePlacedPosMaybe_238270(u);
                    }
                    CharaGetPos_2388a0(u, &v150);
                    TriCalcBounds_1cb540(&v160, &v170, &v160, &v170, &v150);
                    AiGetNavPath_2c10a0(CharaGetAi_214a10(u))->x91 = 0;
                    AiGetNavPath_2c10a0(CharaGetAi_214a10(u))->x90 = 0;
                }
                PartySnapToGroundMaybe_2f10e0(&v160);
                if (ObjRecGetLiveObject_1c3bc0(h, h->x4344) != 0) {
                    CameraSnapReqAt_1f6d70(1);
                    CameraSnapReqEye_1f6d60(1);
                }
                t = GetWorldDataMgr_1fedf0();
                e = MapFindBlockAtPos_1e3a00(GetMapMgr_201a90(), &v180, 0.0f);
                a = -1;
                c = -1;
                if (e != 0) {
                    a = MapBlockGetLocationId_1e0070(e);
                    c = MapBlockGetNavGraphId_1e0050(e);
                }
                HandleEntriesReleaseExcept_3f0b90(t, a);
                HandleEntriesReleaseExcept_3f0aa0(t, c);
            }
        }
        if (StateFlagTest_3ccd70(g->x10, 0x7F5) == 0) {
            CameraSnapReqAt_1f6d70(1);
            CameraSnapReqEye_1f6d60(1);
        } else {
            StateFlagSet_3ccb70(g->x10, 0x7F5, 0, 1);
        }
    }
done:
    flag = 0;
    if (st != 3) {
        ActionPacketReset_3e3d00(&cam);
        ActionPacketInitFieldBeginMaybe_3e3af0(&cam, h, k, 0);
        EventFireTriggers_3e2660(&cam, &flag);
    }
    if (k > 0 && flag == 0) {
        o = GetStaticScene_1c6c70();
        if (o != 0) {
            GameSceneSoundFadeVolume_1d0370(o, 0xF, 1.0f);
            GameSceneSoundSlot4FadeTo_1d0610(o, 0xF, 1.0f);
            for (j = 0; j < Total(g->x18); j++) {
                id = PartyGetSlotId_3c3120(g->x18, j);
                u = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
                if (u != 0) {
                    if (IsInBattle_288420() != 0) {
                        CharaInvokeInitBt1_212ad0(u);
                    } else {
                        CharaInvokeInitNrm_212b30(u);
                    }
                }
            }
        }
        if (fl != 0) {
            StateFlagSet_3ccb70(g->x10, 0x7F0, 1, 1);
            PartyLeaderRebuildBlockIdList_2012e0();
        }
    }
    x = GetLoaderMgr_1f59d0();
    if (CharaSysStateField28ValidRelated_3a3920(g->x20) == 0 || fl == 0) {
        StreamSetChanVolumeFade_1cd960(x, 0, 0xF, 1.0f);
    }
    if (StateFlagTest_3ccd70(g->x10, 0x7F1) == 0) {
        for (m = 0; m < 0xE0; m++) {
            ch = ObjRecGetLiveObject_1c4a90(h, m);
            if (ch == 0) {
                continue;
            }
            ch->x464 = 0x1F;
            ch->x468 = 0;
            ch = GetLiveObjById_1ce420(m, -0xA);
            if (ch != 0) {
                ch->x464 = 0x1F;
                ch->x468 = 0;
            }
            ch = GetLiveObjById_1ce420(m, -0xB);
            if (ch != 0) {
                ch->x464 = 0x1F;
                ch->x468 = 0;
            }
            ch = GetLiveObjById_1ce420(m, -0x14);
            if (ch != 0) {
                ch->x464 = 0x1F;
                ch->x468 = 0;
            }
            ch = GetLiveObjById_1ce420(m, -0x15);
            if (ch != 0) {
                ch->x464 = 0x1F;
                ch->x468 = 0;
            }
            u = ActionMgrFindById_233b50(w, m);
            if (u == 0) {
                continue;
            }
            if (D_004821E0 == 0x321) {
                if (m <= 0 || m >= 8) {
                    CharaResetBattleStateMaybe_212f20(u, 1);
                } else {
                    CharaGetPos_2388a0(u, &v110);
                    e = MapFindBlockAtPos_1e3a00(GetMapMgr_201a90(), &v110, 0.0f);
                    if (e == 0 || MapDataIsJasterOnly_1e7a90(e) == 0) {
                        CharaResetBattleStateMaybe_212f20(u, 1);
                    }
                }
            } else {
                CharaResetBattleStateMaybe_212f20(u, 1);
            }
        }
    } else {
        for (n = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(GetActionMgr_1fdb50())); n != 0; n = DListGetNext_42eb30(n)) {
            o = n + 0x10;
            if (o == 0) {
                continue;
            }
            cc = CharaGetActionTable_214cd0(o);
            if (cc == 0) {
                continue;
            }
            if (IsInBattle_288420() == 0) {
                ActCfgTableRunEvntByName_21f680(cc, CharaGetId_214a80(o), D_00461B80);
            } else {
                p = ActorFindById_3eb870(g, CharaGetId_214a80(o));
                if (p == 0 || p->f() == 0) {
                    ActCfgTableRunEvntByName_21f680(cc, CharaGetId_214a80(o), D_00461B90);
                } else {
                    ActCfgTableRunEvntByName_21f680(cc, CharaGetId_214a80(o), D_00461BA0);
                }
            }
        }
    }
    StateFlagSet_3ccb70(g->x10, 0x7F1, 0, 1);
    EventObjMgrResume_27aec0();
    for (i = 0x80; i <= 0x9B; i++) {
        ObjRecSetFlag2_1c3e80(h, 1, i);
    }
    MapSlotsRefreshBlocksEnabled_1e2b70(GetMapMgr_201a90());
    TaskUpdateMapInfo_201340();
    PartyRefreshMembersMaybe_2f40b0(1);
    InvCleanupRemovedMaybe_3e77b0(g, k, 0);
    GetDrawCtx_15de80();
    b->xA = 1;
    SetFieldControlActive_27bd30(0);
    LetterboxSetFade_277ea0(D_004D7810, 0.0f, 10.0f, 0.0f);
    if (HasPendingFadeFrames_27bd70() != 0) {
        if (StateFlagTest_3ccd70(g->x10, 0x7F0) == 0) {
            sv = GetPendingFadeFrames_27bd60();
            D_004D782C[0] = sv;
            ScreenFadeCaptureFrame_1cf550(h);
            ScreenFadeDissolveIn_1cf720(h, sv, 1.0f);
        }
        SetPendingFadeFrames_27bd50(0);
    }
    for (n2 = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(GetActionMgr_1fdb50())); n2 != 0; n2 = DListGetNext_42eb30(n2)) {
        o2 = n2 + 0x10;
        if (o2 == 0) {
            continue;
        }
        if (CharaGetId_214a80(o2) >= 0 && CharaGetId_214a80(o2) < 12) {
            CharaSetInvincibleTime_2138a0(o2, 45.0f);
        }
    }
    return 1;
}
