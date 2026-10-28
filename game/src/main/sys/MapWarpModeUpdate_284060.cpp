/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct Vec4 {
    f32 x, y, z, w;
} Vec4;

typedef struct Mtx {
    Vec4 r[4];
} Mtx;

typedef struct EvGlob {
    u8 x0;
    u8 pad1;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C[2];
    f32 x24[2];
    f32 x2C[3];
    f32 x38[3];
} EvGlob;

typedef struct Params {
    u8 pad0[4];
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    u8 padC[0x30 - 0xC];
    s16 x30;
    u8 pad32[0x18E - 0x32];
    s16 x18E;
} Params;

typedef struct Evt {
    u8 pad0[8];
    s32 x8;
    u8 padC[4];
    s32 x10;
    u8 pad14[4];
    Params *x18;
    u8 pad1C[4];
    s32 x20;
} Evt;

typedef struct Chr {
    u8 pad0[0x464];
    s32 x464;
    u8 x468;
} Chr;

typedef struct Actor {
    u8 pad0[0x60];
    u32 x60;
} Actor;

typedef struct Rec {
    u8 pad0[0xC];
    s32 xC;
    s16 x10;
    s16 x12;
} Rec;

typedef struct Rec8 {
    u8 pad0[8];
    s16 x8;
    s16 pad;
    s16 xC;
} Rec8;

typedef struct Scene {
    u8 pad0[0x4344];
    s32 x4344;
} Scene;

struct Base39 {
    u8 pad000[0xC0];
};

class Cam : public Base39 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v39(Vec4 *out) { VCM(void, (void *, Vec4 *), 0xA4, out); }
    void v40(Vec4 *out) { VCM(void, (void *, Vec4 *), 0xA8, out); }
};

typedef struct CamData {
    u8 pad0[0x50];
    u128 x50;
    u128 x60;
    u8 pad70[0xE0 - 0x70];
    u128 xE0;
    u128 xF0;
    u8 pad100[0x1C0 - 0x100];
    Vec4 x1C0;
} CamData;

extern "C" {
extern EvGlob D_004D7E00;
extern Vec4 D_0047E9E0 __attribute__((section(".sdata")));
extern Vec4 D_0047E9F0 __attribute__((section(".sdata")));
extern s32 D_004821F8;
extern char D_0045FED0[];
extern char D_004600B8[];
extern char D_004600C8[];
extern char D_004600E8[];
extern char D_004600F8[];
extern char D_00460108[];
extern char D_00460118[];
extern char D_00460148[];
extern char D_00460158[];
extern char D_00460168[];
extern char D_00460178[];
extern char D_00460188[];
extern char D_00460198[];
extern char D_004601D0[];
extern char D_004601E0[];
extern char D_00460200[];
extern char D_00460230[];
extern char D_00460250[];
extern char D_004602D8[];
extern char D_00460568[];
extern char D_004605C0[];
extern char D_00460C88[];

Evt *GetGameData_1fede0(void);
s32 GetWorldDataMgr_1fedf0(void);
s32 GetGameReqQueue_1f5bc0(void);
Scene *GetCurrentScene_1f5be0(void);
s32 GetMapMgr_201a90(void);
s32 GetActionMgr_1fdb50(void);
void GameReqQueueRemoveById_1f5a10(s32);
s32 GetGameModePhase_1f59b0(void);
void SetGameReqHold_1f5890(void);
void TaskStatePushAll_27c220(void);
void SetGameModePhase_1f59a0(s32);
s32 ActionMgrFindById_233b50(s32, s32);
f32 Sinf_128fd0(f32);
f32 Cosf_128d30(f32);
void CharaPlaceAt_2f3a40(s32, Vec4 *, s32, f32);
Chr *ObjRecGetLiveObject_1c4a90(Scene *, s32);
void MatFromRotPos_1caf90(Mtx *, Vec4 *, Vec4 *);
s32 PartyCountExcludingLeader_3c2610(Params *, s32, s32);
s32 PartyGetNonLeaderId_3c2750(Params *, s32);
void MatMulVec4Args_1cb7f0(Vec4 *, Mtx *, f32, f32, f32, f32);
void PartySetAreaMaybe_3cab50(Params *, s32, s32, s32);
s32 MapGetEnvSlots_1e57a0(s32);
void MapEnvSlotsInit_1e5f40(s32);
void LoadingIconSetEnabled_2ee910(s32);
s32 MapFindAreaSlotById_1e4cb0(s32, s32);
s32 MapDataIsLoaded_1e79d0(s32);
void MapDataGetPosVec4_1e7740(s32, Vec4 *);
void MapDataGetRotVec4_1e7720(s32, Vec4 *);
float MtxInverseAffine_1cb640(Mtx *, Mtx *);
s32 ActionMgrGetCharaList_233b40(s32);
s32 DListGetHead_42ea60(s32);
s32 DListGetNext_42eb30(s32);
void CharaGetPos_2388a0(s32, Vec4 *);
void CharaGetRot_2388b0(s32, Vec4 *);
void MatMulPoint_1cb8e0(Vec4 *, Mtx *, Vec4 *);
s32 CharaGetId_214a80(s32);
f32 AngleWrap_1cbf30(f32);
Cam *ObjRecGetLiveObject_1c3bc0(Scene *, s32);
void sceVu0CopyVector(Vec4 *, Vec4 *);
void StateFlagSet_3ccb70(s32, s32, void *, int);
s32 StateFlagTest_3ccd70(s32, s32);
void GameReqListKeepId_209f60(s32, s32);
void TaskSetEnabled_27c2a0(s32, char *);
void MapBlockIdListClear_1e32e0(Actor *);
Rec *PlanetAreaMatrixLookupByProgress_3ed840(Evt *, s32);
s32 MapGetFirstAreaSlotId_1e57e0(Actor *);
s32 GetLoaderMgr_1f59d0(void);
void StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);
void MapSetSlot0AreaId_1e4140(Actor *, s32);
s32 EvtInfoGetIdMaybe_3ed810(Evt *);
void MapSetSlot1AreaId_1e4130(Actor *, s32);
void MapLocSetNameMaybe_1e4070(Actor *, s32, s32, s32);
void MapSetSkyId_1e41b0(Actor *, s32);
s32 WorldDataMgrNoRequestPending_3eef10(s32);
void MesShowMsgByIndex_278fd0(s32, s32);
s32 MesSlot0GetState_278df0(void);
s32 MapGetFirstAreaSlot_1e5760(s32);
void MapApplySaveStateMaybe_1fe560(void);
void CharaSavePlacedPosMaybe_238270(s32);
void ModelSetPos_151110(Chr *, Vec4 *);
void ModelSetRot_151080(Chr *, Vec4 *);
void CameraSetModeOverrideCur_309e40(s32);
s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
s32 MapBlockGetLocationId_1e0070(s32);
s32 MapBlockGetNavGraphId_1e0050(s32);
Rec8 *HandleEntryFindById_3f2450(s32, s32);
s32 GetNavMgr_2d1950(void);
void HandleEntryRelease_3f1d80(s32, Rec8 *, s32);
Rec8 *HandleEntryFindById_3f1600(s32, s32);
void NavRemoveGraphById_30a3b0(s32);
void EventObjMgrRemoveByIdFwdThunk_2fd970(s32);
void HandleEntryRelease_3f12f0(s32, Rec8 *, s32);
void WorldDataZoneEntriesUpdateMaybe_3f1660(s32, s32, s32, s32);
void WorldDataAreaEntriesUpdateMaybe_3f0cc0(s32, s32, s32, s32);
void HandleEntriesReleaseAll_3f2290(s32);
void HandleEntriesReleaseAll_3f14a0(s32);
void GameDataTick_1febd0(void);
s32 GetEventObjMgr_2d1960(void);
void EventObjMgrResolveAndResetAll_2e88c0(s32);
void NavGraphsSyncAreaXform_30c980(s32);
s32 MapLoadIsSettledMaybe_1e4e10(s32, s32);
s32 MapSlotsFindActiveBlockById_1e4730(s32, s32, s32);
s32 MapDataIsJasterOnly_1e7a90(s32);
s32 PartySwitchLeader_2f3ca0(s32, s32);
void CharaSetAreaId_213c80(s32, s32);
s32 GetGameModeAt_1f5830(s32);
float CharaGetForwardVec_238830(s32, Vec4 *);
void VecScale_1cbca0(Vec4 *, Vec4 *, f32);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
void MesSlot0Close_278e40(void);
void CharaSysBattleHistoryReset_3a5bf0(s32);
void GameDataResetSpotState_3eb690(Evt *);
void TaskUpdateFogParam_201240(void);
void TaskStatePopAll_27c250(void);
void ClearGameReqHold_1f5880(void);
void GameReqQueuePushFront_1f5ab0(s32, s32);
}

static inline void clr(void *p, s32 n)
{
    u8 *q;
    s32 c;
    c = n;
    q = (u8 *)p;
    if (q != NULL) {
        do {
            *q++ = 0;
        } while (--c);
    }
}

static inline bool IsSet(void)
{
    if (D_004D7E00.x2C[0] != 0.0f) return true;
    if (D_004D7E00.x2C[1] != 0.0f) return true;
    if (D_004D7E00.x2C[2] != 0.0f) return true;
    if (D_004D7E00.x38[0] != 0.0f) return true;
    if (D_004D7E00.x38[1] != 0.0f) return true;
    if (D_004D7E00.x38[2] != 0.0f) return true;
    return false;
}

static inline void SetCam(Cam *cam, Vec4 *at, Vec4 *eye)
{
    CamData *cd = (CamData *)cam;
    sceVu0CopyVector(&cd->x1C0, eye);
    cd->x60 = *(u128 *)at;
    cd->x50 = *(u128 *)eye;
    cd->xF0 = *(u128 *)at;
    cd->xE0 = *(u128 *)eye;
}

extern "C" s32 MapWarpModeUpdate_284060(void)
{
    Evt *e;
    s32 s3;
    s32 s5;
    Scene *sc;
    s32 s1;
    s32 s0;
    s32 st;

    e = GetGameData_1fede0();
    s3 = GetWorldDataMgr_1fedf0();
    s5 = GetGameReqQueue_1f5bc0();
    sc = GetCurrentScene_1f5be0();
    s1 = GetMapMgr_201a90();
    s0 = GetActionMgr_1fdb50();
    GameReqQueueRemoveById_1f5a10(5);
    st = GetGameModePhase_1f59b0();
    switch (st) {
    case -1: {
        s32 id;
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        if (D_004D7E00.x0 == 0) {
            SetGameModePhase_1f59a0(200);
            return 0;
        }
        id = e->x18->x18E;
        if (ActionMgrFindById_233b50(s0, id)) {
            f32 r[4] __attribute__((aligned(16))) = {D_004D7E00.xC, D_004D7E00.x10, D_004D7E00.x14, 1.0f};
            f32 q[4] __attribute__((aligned(16))) = {0.0f, D_004D7E00.x18, 0.0f, 1.0f};
            Vec4 m __attribute__((aligned(16)));
            Mtx M __attribute__((aligned(16)));
            Chr *c;
            s32 n;
            s32 i;
            clr(&m, 16);
            m.x = Sinf_128fd0(D_004D7E00.x18);
            m.z = Cosf_128d30(D_004D7E00.x18);
            CharaPlaceAt_2f3a40(id, (Vec4 *)r, 0, q[1]);
            c = ObjRecGetLiveObject_1c4a90(sc, id);
            if (c) {
                c->x464 = 0x1F;
                c->x468 = 0;
            }
            MatFromRotPos_1caf90(&M, (Vec4 *)q, (Vec4 *)r);
            n = PartyCountExcludingLeader_3c2610(e->x18, 1, 1);
            for (i = 0; i < n; i++) {
                Vec4 v __attribute__((aligned(16)));
                id = ((short)PartyGetNonLeaderId_3c2750(e->x18, i));
                if (ActionMgrFindById_233b50(s0, id) == 0) continue;
                c = ObjRecGetLiveObject_1c4a90(sc, id);
                if (c) {
                    c->x464 = 0x1F;
                    c->x468 = 0;
                }
                MatMulVec4Args_1cb7f0(&v, &M, D_004D7E00.x1C[i], 0.0f, D_004D7E00.x24[i], 1.0f);
                CharaPlaceAt_2f3a40(id, &v, 0, q[1]);
            }
        }
        PartySetAreaMaybe_3cab50(e->x18, D_004D7E00.x2, 1, 0);
        MapEnvSlotsInit_1e5f40(MapGetEnvSlots_1e57a0(s1));
        SetGameModePhase_1f59a0(1);
        LoadingIconSetEnabled_2ee910(1);
        return 1;
    }
    case 0: {
        Mtx M, Mi;
        Vec4 a, b;
        s32 it;
        Cam *cam;
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        s1 = MapFindAreaSlotById_1e4cb0(s1, e->x18->xA);
        if (s1 == 0 || ((unsigned char)MapDataIsLoaded_1e79d0(s1)) == 0) {
            SetGameModePhase_1f59a0(200);
            return 0;
        }
        PartySetAreaMaybe_3cab50(e->x18, D_004D7E00.x2, 1, 0);
        D_004D7E00.x4 = e->x18->xA;
        MapDataGetPosVec4_1e7740(s1, &a);
        MapDataGetRotVec4_1e7720(s1, &b);
        MatFromRotPos_1caf90(&M, &b, &a);
        MtxInverseAffine_1cb640(&Mi, &M);
        for (it = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(s0)); it != 0;) {
            Vec4 p, r;
            s32 o = it + 0x10;
            s32 x;
            it = DListGetNext_42eb30(it);
            CharaGetPos_2388a0(o, &p);
            CharaGetRot_2388b0(o, &r);
            MatMulPoint_1cb8e0(&p, &Mi, &p);
            x = ((short)CharaGetId_214a80(o));
            CharaPlaceAt_2f3a40(x, &p, 0, AngleWrap_1cbf30(r.y - b.y));
        }
        cam = ObjRecGetLiveObject_1c3bc0(sc, sc->x4344);
        if (cam) {
            Vec4 c0, c1;
            cam->v39(&c0);
            cam->v40(&c1);
            MatMulPoint_1cb8e0(&c0, &Mi, &c0);
            MatMulPoint_1cb8e0(&c1, &Mi, &c1);
            SetCam(cam, &c0, &c1);
        }
        SetGameModePhase_1f59a0(1);
        LoadingIconSetEnabled_2ee910(1);
        return 1;
    }
    case 1: {
        Evt *e2;
        Rec *r;
        s32 b, a, c;
        s32 k;
        StateFlagSet_3ccb70(e->x10, 0x7E2, (void *)(0), 1);
        if (StateFlagTest_3ccd70(e->x10, 0x7EC)) {
            SetGameModePhase_1f59a0(0xC);
            return 0;
        }
        GameReqListKeepId_209f60(s5, 0xB);
        TaskSetEnabled_27c2a0(0, D_004601D0);
        TaskSetEnabled_27c2a0(0, D_00460108);
        TaskSetEnabled_27c2a0(0, D_004600C8);
        TaskSetEnabled_27c2a0(0, D_004600B8);
        TaskSetEnabled_27c2a0(0, D_004600F8);
        TaskSetEnabled_27c2a0(0, D_00460148);
        TaskSetEnabled_27c2a0(0, D_00460158);
        TaskSetEnabled_27c2a0(0, D_00460168);
        TaskSetEnabled_27c2a0(0, D_00460178);
        TaskSetEnabled_27c2a0(0, D_0045FED0);
        TaskSetEnabled_27c2a0(0, D_00460230);
        TaskSetEnabled_27c2a0(0, D_00460250);
        TaskSetEnabled_27c2a0(0, D_004605C0);
        TaskSetEnabled_27c2a0(0, D_00460200);
        TaskSetEnabled_27c2a0(0, D_004602D8);
        ((Actor *)s1)->x60 |= 8;
        MapBlockIdListClear_1e32e0((Actor *)s1);
        e2 = GetGameData_1fede0();
        r = PlanetAreaMatrixLookupByProgress_3ed840(e2, e2->x18->x4);
        a = -1;
        b = 0;
        c = a;
        if (r) {
            b = r->xC;
            a = r->x10;
            c = r->x12;
        }
        k = e2->x18->x6;
        s32 cur = MapGetFirstAreaSlotId_1e57e0((Actor *)s1);
        if (cur != k) {
            StreamSetChanVolumeFade_1cd960(GetLoaderMgr_1f59d0(), 0, 0, 15.0f);
            MapSetSlot0AreaId_1e4140((Actor *)s1, e2->x18->x6);
            MapSetSlot1AreaId_1e4130((Actor *)s1, EvtInfoGetIdMaybe_3ed810(e2));
            MapLocSetNameMaybe_1e4070((Actor *)s1, b, a, c);
            MapSetSkyId_1e41b0((Actor *)s1, e2->x18->x8);
        }
        SetGameModePhase_1f59a0(2);
        return 0;
    }
    case 2:
        SetGameModePhase_1f59a0(100);
        ((Actor *)s1)->x60 &= ~8;
        return 0;
    case 12:
        if (!WorldDataMgrNoRequestPending_3eef10(e->x8)) return 0;
        MesShowMsgByIndex_278fd0(5, -1);
        StateFlagSet_3ccb70(e->x10, 0x7EC, (void *)(0), 1);
        TaskSetEnabled_27c2a0(1, D_00460118);
        TaskSetEnabled_27c2a0(1, D_00460C88);
        SetGameModePhase_1f59a0(0xD);
        return 0;
    case 13:
        if (MesSlot0GetState_278df0() != 1) {
            if (MesSlot0GetState_278df0() != 2 && MesSlot0GetState_278df0() != 4) SetGameModePhase_1f59a0(1);
        }
        return 0;
    case 100:
        if (!WorldDataMgrNoRequestPending_3eef10(e->x8)) return 0;
        SetGameModePhase_1f59a0(0x65);
        return 1;
    case 101: {
        s32 t;
        s32 t2;
        bool any;
        s32 a, b, c;
        t = MapGetFirstAreaSlot_1e5760(s1);
        if (t == 0 || ((unsigned char)MapDataIsLoaded_1e79d0(t)) == 0) return 0;
        MapApplySaveStateMaybe_1fe560();
        t2 = MapFindAreaSlotById_1e4cb0(s1, D_004D7E00.x4);
        if (t2 != 0 && ((unsigned char)MapDataIsLoaded_1e79d0(t2)) != 0) {
            Mtx M __attribute__((aligned(16)));
            Vec4 a4, b4;
            s32 it;
            Cam *cam;
            MapDataGetPosVec4_1e7740(t2, &a4);
            MapDataGetRotVec4_1e7720(t2, &b4);
            MatFromRotPos_1caf90(&M, &b4, &a4);
            for (it = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(s0)); it != 0;) {
                Chr *ch;
                Vec4 p, r;
                s32 o = it + 0x10;
                s32 x;
                it = DListGetNext_42eb30(it);
                CharaGetPos_2388a0(o, &p);
                CharaGetRot_2388b0(o, &r);
                MatMulPoint_1cb8e0(&p, &M, &p);
                x = ((short)CharaGetId_214a80(o));
                CharaPlaceAt_2f3a40(x, &p, 0, AngleWrap_1cbf30(r.y - b4.y));
                CharaSavePlacedPosMaybe_238270(o);
                ch = ObjRecGetLiveObject_1c4a90(sc, ((short)CharaGetId_214a80(o)));
                if (ch) {
                    CharaGetPos_2388a0(o, &p);
                    CharaGetRot_2388b0(o, &r);
                    ModelSetPos_151110(ch, &p);
                    ModelSetRot_151080(ch, &r);
                    ch->x464 = 0x1F;
                    ch->x468 = 0;
                }
            }
            cam = ObjRecGetLiveObject_1c3bc0(sc, sc->x4344);
            if (cam) {
                Vec4 c0, c1;
                cam->v39(&c0);
                cam->v40(&c1);
                MatMulPoint_1cb8e0(&c0, &M, &c0);
                MatMulPoint_1cb8e0(&c1, &M, &c1);
                SetCam(cam, &c0, &c1);
            }
        }
        any = IsSet();
        if (any) {
            Cam *cam = ObjRecGetLiveObject_1c3bc0(sc, sc->x4344);
            if (cam) {
                Vec4 at, eye;
                CameraSetModeOverrideCur_309e40(0xD);
                at.x = D_004D7E00.x2C[0];
                at.y = D_004D7E00.x2C[1];
                at.z = D_004D7E00.x2C[2];
                at.w = 1.0f;
                eye.x = D_004D7E00.x38[0];
                eye.y = D_004D7E00.x38[1];
                eye.z = D_004D7E00.x38[2];
                eye.w = 1.0f;
                SetCam(cam, &at, &eye);
            }
        }
        a = D_004D7E00.x6;
        b = D_004D7E00.x8;
        c = D_004D7E00.xA;
        if (a >= 0) {
            s32 m = MapSlotsFindBlockById_1e49b0(s1, a, 0);
            if (m != 0) {
                s32 p = ((short)MapBlockGetLocationId_1e0070(m));
                s32 q = MapBlockGetNavGraphId_1e0050(m);
                bool f = true;
                bool f2;
                if (p != b) {
                    Rec8 *r = HandleEntryFindById_3f2450(s3, p);
                    if (r) {
                        s32 k = r->xC;
                        if (k == 3) goto set_f;
                        if (k == 4) {
                        set_f:
                            f = true;
                        }
                    }
                }
                if (f) {
                    Rec8 *r2 = HandleEntryFindById_3f2450(s3, b);
                    if (r2) {
                        GetNavMgr_2d1950();
                        HandleEntryRelease_3f1d80(s3, r2, 1);
                    }
                }
                f2 = true;
                if (q != c) {
                    Rec8 *r = HandleEntryFindById_3f1600(s3, c);
                    if (r) {
                        s32 k = r->x8;
                        if (k == 3) goto set_f2;
                        if (k == 4) {
                        set_f2:
                            f2 = true;
                        }
                    }
                }
                if (f2) {
                    Rec8 *r3 = HandleEntryFindById_3f1600(s3, c);
                    if (r3) {
                        NavRemoveGraphById_30a3b0(c);
                        EventObjMgrRemoveByIdFwdThunk_2fd970(c);
                        HandleEntryRelease_3f12f0(s3, r3, 1);
                    }
                }
                WorldDataZoneEntriesUpdateMaybe_3f1660(s3, p, 0, 0);
                WorldDataAreaEntriesUpdateMaybe_3f0cc0(s3, q, 0, 0);
            }
        }
        HandleEntriesReleaseAll_3f2290(s3);
        HandleEntriesReleaseAll_3f14a0(s3);
        GameDataTick_1febd0();
        EventObjMgrResolveAndResetAll_2e88c0(GetEventObjMgr_2d1960());
        NavGraphsSyncAreaXform_30c980(GetNavMgr_2d1950());
        TaskSetEnabled_27c2a0(1, D_004601D0);
        TaskSetEnabled_27c2a0(1, D_00460108);
        TaskSetEnabled_27c2a0(1, D_00460148);
        TaskSetEnabled_27c2a0(1, D_00460158);
        TaskSetEnabled_27c2a0(1, D_00460568);
        TaskSetEnabled_27c2a0(1, D_0045FED0);
        TaskSetEnabled_27c2a0(1, D_004601E0);
        SetGameModePhase_1f59a0(0x66);
        return 0;
    }
    case 102: {
        s32 t;
        s32 o;
        if (!((unsigned char)MapLoadIsSettledMaybe_1e4e10(s1, 0))) return 0;
        {
            s32 k = e->x18->x30;
            D_004821F8 = 0;
            t = MapSlotsFindActiveBlockById_1e4730(s1, k, 0);
        }
        if (t != 0 && ((unsigned char)MapDataIsJasterOnly_1e7a90(t)) != 0 && PartySwitchLeader_2f3ca0(0, 1) != 0) {
            D_004821F8 = 15;
            TaskSetEnabled_27c2a0(1, D_004600E8);
            TaskSetEnabled_27c2a0(1, D_00460188);
            TaskSetEnabled_27c2a0(1, D_00460198);
            TaskSetEnabled_27c2a0(1, D_00460108);
            TaskSetEnabled_27c2a0(1, D_00460168);
        }
        o = ActionMgrFindById_233b50(s0, e->x18->x18E);
        if (o != 0) {
            CharaSetAreaId_213c80(o, e->x18->x30);
            if (GetGameModeAt_1f5830(1) == 11 && GetGameModeAt_1f5830(2) == 20) {
                Cam *cam = ObjRecGetLiveObject_1c3bc0(sc, sc->x4344);
                Vec4 a, c, b;
                CharaGetForwardVec_238830(o, &a);
                CharaGetPos_2388a0(o, &b);
                b.y = b.y + 25.0f;
                VecScale_1cbca0(&a, &a, 80.0f);
                VecSub_1cbd00(&c, &b, &a);
                SetCam(cam, &c, &b);
            }
        }
        SetGameModePhase_1f59a0(0x67);
        return 1;
    }
    case 103:
        {
            s32 x = e->x8;
            D_004821F8 = D_004821F8 - 1;
            if (WorldDataMgrNoRequestPending_3eef10(x) == 0) return 0;
        }
        MesSlot0Close_278e40();
        MapApplySaveStateMaybe_1fe560();
        CharaSysBattleHistoryReset_3a5bf0(e->x20);
        GameDataResetSpotState_3eb690(e);
        SetGameModePhase_1f59a0(200);
        return 1;
    case 200: {
        s32 i;
        D_004821F8 = D_004821F8 - 1;
        if (D_004821F8 >= 0) return 0;
        D_004D7E00.x0 = 0;
        D_004D7E00.x2 = -1;
        D_004D7E00.x4 = -1;
        D_004D7E00.x6 = -1;
        D_004D7E00.x8 = -1;
        D_004D7E00.xA = -1;
        D_004D7E00.xC = 0.0f;
        D_004D7E00.x10 = 0.0f;
        D_004D7E00.x14 = 0.0f;
        D_004D7E00.x18 = 0.0f;
        for (i = 0; i < 2; i++) {
            D_004D7E00.x1C[i] = 0.0f;
            D_004D7E00.x24[i] = 0.0f;
        }
        for (i = 0; i < 3; i++) {
            D_004D7E00.x2C[i] = 0.0f;
            D_004D7E00.x38[i] = 0.0f;
        }
        TaskUpdateFogParam_201240();
        TaskStatePopAll_27c250();
        ClearGameReqHold_1f5880();
        GameReqQueuePushFront_1f5ab0(0, -1);
        return 0;
    }
    }
    return 0;
}
