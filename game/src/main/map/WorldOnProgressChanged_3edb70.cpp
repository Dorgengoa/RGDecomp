/* rgp:protos */
#line 1
#include "types.h"

typedef struct Sub18 {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 padA[0x34 - 0xA];
    s16 unk34;
    s16 unk36;
} Sub18;

typedef struct Ent {
    u8 pad0[4];
    s16 *unk4;
    s16 *unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
} Ent;

typedef struct Info {
    u8 pad0[0xC];
    u8 unkC;
    u8 unkD;
} Info;

typedef struct SubC {
    u8 pad0[0x2E];
    s16 unk2E;
} SubC;

typedef struct Obj {
    u8 pad0[8];
    s32 unk8;
    SubC *unkC;
    s32 unk10;
    u8 pad14[4];
    Sub18 *unk18;
    u8 pad1C[4];
    s32 unk20;
    u8 pad24[0x2C - 0x24];
    u8 unk2C;
} Obj;

extern "C" {
extern void MapReset_1e2e60(s32);
extern void MapLocSetNameMaybe_1e4070(s32, s32, s32, s32);
extern void MapSetSlot1AreaId_1e4130(s32, s32);
extern void MapSetSlot0AreaId_1e4140(s32, s16);
extern void MapSetSkyId_1e41b0(s32, s16);
extern void GameReqQueuePushFront_1f5ab0(s32, s32);
extern void MapApplySaveStateMaybe_1fe560();
extern s32 GetMapMgr_201a90();
extern void CharaSysEncounterDistRoll_3a59d0(s32, s32);
extern void PartySelectEncounter_3c9c30(Sub18 *);
extern void PartyRefreshBgmOverride_3ca730(Sub18 *);
extern void PartySetSpotMaybe_3ca7c0(Sub18 *, long long, int, int);
extern void PartySetSubAreaMaybe_3ca890(Sub18 *, s16, s32, int);
extern void StateVarSet_3cc9c0(s32, s32, s32, s32);
extern Info * ProgressGetCurSubEntryMaybe_3cd200(s32, int, int, int);
extern s32 StateGetRequiredDisc_3d5ed0(void);
extern void GameDataResetSpotState_3eb690(Obj *);
extern void TranspParamRefreshCondsMaybe_3ecce0(Obj *, s32);
extern void BgmParamRefreshCondsMaybe_3ece90(Obj *, s32);
extern void MapObjParamRefreshCondsMaybe_3ed0a0(Obj *, s32);
extern s32 EvtInfoGetIdMaybe_3ed810(Obj *);
extern Ent *PlanetAreaMatrixLookupByProgress_3ed840(Obj *, s16);
extern void HandleEntriesReleaseAll_3f2290(s32);
s32 WorldOnProgressChanged_3edb70(Obj *arg0, int rgp_a1, int rgp_a2, int rgp_a3);
}

s32 WorldOnProgressChanged_3edb70(Obj *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    Info *info;
    Ent *ent;
    s16 v;
    bool f1;
    bool f2;
    s32 h;

    if (arg0->unk8 == 0) {
        return 0;
    }
    if (arg0->unk2C & 1) {
        return 0;
    }
    info = ProgressGetCurSubEntryMaybe_3cd200(arg0->unk10, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    if (info == 0) {
        return 0;
    }
    f1 = false;
    f2 = false;
    ent = PlanetAreaMatrixLookupByProgress_3ed840(arg0, arg0->unk18->unk4);
    if (ent != 0) {
        if (ent->unk4 != 0) {
            v = *ent->unk4;
            if (v != arg0->unk18->unk6) {
                f1 = true;
                PartySetSubAreaMaybe_3ca890(arg0->unk18, v, 0, 0);
            }
        }
        if (ent->unk8 != 0) {
            v = *ent->unk8;
            if (v != arg0->unk18->unk8) {
                f2 = true;
                PartySetSpotMaybe_3ca7c0(arg0->unk18, (long long)(v), 0, 0);
            }
        }
    }
    HandleEntriesReleaseAll_3f2290(arg0->unk8);
    if (arg0->unk18 != 0) {
        arg0->unk18->unk34 = 1;
        arg0->unk18->unk36 = 1;
    }
    MapObjParamRefreshCondsMaybe_3ed0a0(arg0, -1);
    BgmParamRefreshCondsMaybe_3ece90(arg0, -1);
    TranspParamRefreshCondsMaybe_3ecce0(arg0, -1);
    h = GetMapMgr_201a90();
    if (h != 0 && ent != 0) {
        if (f1 || f2) {
            MapReset_1e2e60(h);
        } else {
            MapApplySaveStateMaybe_1fe560();
        }
        if (f1 && ent->unk4 != 0) {
            MapSetSlot0AreaId_1e4140(h, *ent->unk4);
        }
        if (f2 && ent->unk8 != 0) {
            MapSetSkyId_1e41b0(h, *ent->unk8);
        }
        MapSetSlot1AreaId_1e4130(h, EvtInfoGetIdMaybe_3ed810(arg0));
        MapLocSetNameMaybe_1e4070(h, ent->unkC, ent->unk10, ent->unk12);
    }
    PartySelectEncounter_3c9c30(arg0->unk18);
    CharaSysEncounterDistRoll_3a59d0(arg0->unk20, 0);
    PartyRefreshBgmOverride_3ca730(arg0->unk18);
    StateVarSet_3cc9c0(arg0->unk10, 0x13, info->unkC, 1);
    StateVarSet_3cc9c0(arg0->unk10, 0x12, info->unkD, 1);
    GameDataResetSpotState_3eb690(arg0);
    s32 last=arg0->unkC->unk2E;
    s32 cmp=((unsigned char)StateGetRequiredDisc_3d5ed0());
    if (cmp!=last) {
        GameReqQueuePushFront_1f5ab0(4, -1);
    }
    return 1;
}
