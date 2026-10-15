#include "types.h"

typedef unsigned __int128 u128;

class Obj {
public:
    u8 pad[0x1B0];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void f38();
    virtual void v13();
    virtual void v14();
    virtual void f44(f32);
};

extern "C" {
s32 ModelObjExGetQueuedSeIds_1b0730(Obj *, s32 *, s32);
void ModelObjExCalcSoundVolPan_1b0780(Obj *, f32 *, f32 *);
s32 SoundNextPlayHandle_1b81c0(void);
void SoundPlayScaledVolPan_1b9680(s32, s32, s32, f32, f32);
s32 ObjRecGetValue_1c3d30(s32, s32, s32);
s32 ObjRecGetFlags_1c3d90(s32, s32, s32);
void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
void SceneObjApplyWind_1c47e0(s32, s32);
s32 ObjRecIsActiveMaybe_1c4830(s32, s32);
Obj *ObjRecGetLiveObject_1c4a90(s32, s32);
f32 GameSceneGetTimeStep_1ceba0(s32);
s8 *ParamTableGetRec_1cfbc0(s32, s32);
s32 GameSceneSoundSlot1GetHandle_1d07b0(s32);
s32 MapSlotsFindById_1e4b90(s32, s32, s32);
s16 MapResolveGroundMaterialIdMaybe_1e5290(s32, s32, s32);
s32 MapDataIsWindOff_1e7ae0(s32);
s32 GetGameMode_1f59c0(void);
s32 GetCurrentScene_1f5be0(void);
s32 CharaWeaponSeIdRemap_1fd430(s32, s32);
void GetGameData_1fede0(void);
s32 GetMapMgr_201a90(void);
f32 CharaGetEffectiveSpeedScale_213dd0(s32);
void ActionMgrUpdateTintAll_232d80(u8 *, f32);
s32 ActionMgrFindById_233b50(u8 *, s32);
s32 EventObjMgrIsRunning_27af20(void);
s32 IsInBattleMode_288380(void);
s32 IsInBattle_288420(void);
extern u8 D_0045B080[0x400];
extern s32 D_00481A78;
extern s32 D_00481A7C;
extern s32 D_00481A90;
extern u8 D_004B8680[0x400];
void SceneObjsStep_1f97a0(void);
}

void SceneObjsStep_1f97a0(void) {
    f32 ec;
    f32 e8;
    s32 buf[4];
    u8 *tab;
    f32 base;
    f32 a;
    f32 b;
    f32 sc;
    s32 mgr;
    s32 ctx;
    s32 i;
    Obj *o;
    s32 j;
    s32 n;
    s32 flags;
    s32 h;
    s8 *d;


    GetGameData_1fede0();
    tab = D_004B8680;
    mgr = GetCurrentScene_1f5be0();
    ctx = GetMapMgr_201a90();
    base = GameSceneGetTimeStep_1ceba0(mgr);
    if (EventObjMgrIsRunning_27af20() != 0) {
        ActionMgrUpdateTintAll_232d80(tab, base);
    }
    D_00481A90--;
    if (D_00481A90 < 0) {
        D_00481A90 = -1;
    }
    D_00481A78--;
    if (D_00481A78 < 0) {
        D_00481A78 = -1;
    }
    D_00481A7C--;
    if (D_00481A7C < 0) {
        D_00481A7C = -1;
    }
    a = 10.0f * *(f32 *)D_0045B080;
    b = 50.0f * *(f32 *)D_0045B080;
    if (IsInBattle_288420() != 0) {
        a = 20.0f * *(f32 *)D_0045B080;
        b = 80.0f * *(f32 *)D_0045B080;
    }
    i = 0;
    do {
        if (ObjRecIsActiveMaybe_1c4830(mgr, i) == 0) {
            goto next;
        }
        o = ObjRecGetLiveObject_1c4a90(mgr, i);
        if (o == 0) {
            goto next;
        }
        if (ObjRecGetValue_1c3d30(mgr, 1, i) == 5) {
            goto next;
        }
        d = ParamTableGetRec_1cfbc0(mgr, i);
        if (d == 0) {
            goto next;
        }
        *(f32 *)((u8 *)o + 0x520) = a;
        *(f32 *)((u8 *)o + 0x524) = b;
        h = MapSlotsFindById_1e4b90(ctx, *(s16 *)(d + 0x12), 0);
        if (GetGameMode_1f59c0() == 9 || (h != 0 && MapDataIsWindOff_1e7ae0(h) != 0)) {
            o->f38();
        } else {
            SceneObjApplyWind_1c47e0(mgr, i);
        }
        sc = base;
        h = ActionMgrFindById_233b50(tab, i);
        if (h != 0 && IsInBattleMode_288380() != 0) {
            sc = base * CharaGetEffectiveSpeedScale_213dd0(h);
        }
        o->f44(sc);
        flags = ObjRecGetFlags_1c3d90(mgr, 1, i);
        *(s16 *)(d + 0x10) = MapResolveGroundMaterialIdMaybe_1e5290(ctx, *(s16 *)(d + 0x12), *(s16 *)(d + 0x10));
        n = ModelObjExGetQueuedSeIds_1b0730(o, buf, 4);
        ec = 0;
        e8 = 0;
        ModelObjExCalcSoundVolPan_1b0780(o, &ec, &e8);
        if (n > 0 && i >= 0 && i < 12) {
            for (j = 0; j < n; j++) {
                s32 m = *(s32 *)((u8 *)o + 0x4FC);
                SoundPlayScaledVolPan_1b9680(m, CharaWeaponSeIdRemap_1fd430(i, buf[j]), SoundNextPlayHandle_1b81c0(), ec, e8);
            }
        }
        if (flags & 0x200000) {
            SoundPlayScaledVolPan_1b9680(GameSceneSoundSlot1GetHandle_1d07b0(mgr), *(s16 *)(d + 0x10) * 2, SoundNextPlayHandle_1b81c0(), ec, e8);
            ObjRecClearFlags_1c3dc0(mgr, 1, i, 0x200000);
        }
        if (flags & 0x400000) {
            SoundPlayScaledVolPan_1b9680(GameSceneSoundSlot1GetHandle_1d07b0(mgr), *(s16 *)(d + 0x10) * 2 + 1, SoundNextPlayHandle_1b81c0(), ec, e8);
            ObjRecClearFlags_1c3dc0(mgr, 1, i, 0x400000);
        }
        if (flags & 0x20000000) {
            ObjRecClearFlags_1c3dc0(mgr, 1, i, 0x20000000);
        }
    next:
        i++;
    } while (i < 0xE0);
}
