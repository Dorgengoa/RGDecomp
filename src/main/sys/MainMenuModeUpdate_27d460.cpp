#include "types.h"

class Chr {
public:
    u8 pad0[0x1B0];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void Set(f32); /* 0x44 */
    u8 pad1B4[0x464 - 0x1B4];
    s32 x464;
    u8 x468;
};

class Obj {
public:
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5();
    virtual void vf6(); virtual void vf7(); virtual void vf8(); virtual void vf9(); virtual void vf10(); virtual void vf11();
    virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15(); virtual void vf16(); virtual void vf17();
    virtual void vf18(); virtual void vf19(); virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
    virtual void vf24(); virtual void vf25(); virtual void vf26(); virtual void vf27(); virtual void vf28(); virtual void vf29();
    virtual void vf30(); virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35();
    virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39(); virtual void vf40(); virtual void vf41();
    virtual void vf42(); virtual void vf43(); virtual void vf44(); virtual void vf45(); virtual void vf46(); virtual void vf47();
    virtual void vf48(); virtual void vf49(); virtual void vf50(); virtual void vf51(); virtual void vf52(); virtual void vf53();
    virtual void vf54(); virtual void vf55(); virtual void vf56(); virtual void vf57(); virtual void vf58(); virtual void vf59();
    virtual void vf60(); virtual void vf61(); virtual void vf62(); virtual void vf63(); virtual void vf64(); virtual void vf65();
    virtual void vf66(); virtual void vf67(); virtual void vf68(); virtual void vf69(); virtual void vf70(); virtual void vf71();
    virtual void vf72(); virtual void vf73(); virtual void vf74(); virtual void vf75(); virtual void vf76(); virtual void vf77();
    virtual void vf78(); virtual void vf79(); virtual void vf80(); virtual void vf81(); virtual void vf82(); virtual void vf83();
    virtual void vf84(); virtual void vf85(); virtual void vf86(); virtual void vf87(); virtual void vf88(); virtual void vf89();
    virtual void vf90(); virtual void vf91(); virtual void vf92(); virtual void vf93(); virtual void vf94(); virtual void vf95();
    virtual void vf96(); virtual void vf97(); virtual void vf98(); virtual void vf99(); virtual void vf100(); virtual void vf101();
    virtual void vf102(); virtual void vf103(); virtual void vf104(); virtual void vf105(); virtual void vf106();
    virtual void Act(void); /* 0x1B4 */
};

typedef struct Pty {
    u8 pad0[0x18E];
    s16 x18E;
} Pty;

typedef struct Gm {
    u8 pad0[0x18];
    Pty *x18;
} Gm;

typedef struct Vec4 {
    f32 x, y, z, w;
} Vec4;

extern "C" Gm *GetGameData_1fede0(void);
extern "C" s32 GetCurrentScene_1f5be0(void);
extern "C" s32 GetMapMgr_201a90(void);
extern "C" s32 GetActionMgr_1fdb50(void);
extern "C" s32 GetCharaResMgr_1fdb60(void);
extern "C" void GameReqQueueRemoveById_1f5a10(s32);
extern "C" s32 GetGameModePhase_1f59b0(void);
extern "C" void SetGameReqHold_1f5890(void);
extern "C" void ClearGameReqHold_1f5880(void);
extern "C" void PadSaveRepeatConfig_1838f0(void *, s32 *);
extern "C" void PadApplyRepeatConfig_183800(void *, s32 *);
extern "C" void TaskStatePushAll_27c220(void);
extern "C" void TaskStatePopAll_27c250(void);
extern "C" void TaskDisableFieldHudSet_285ff0(void);
extern "C" void TaskEnableLoadingSet_285f90(void);
extern "C" void TaskSetEnabled_27c2a0(s32, void *);
extern "C" void GameSceneSoundSlot0PlaySe_1d05b0(s32, s32);
extern "C" void ScreenFadeReset_1cf760(s32);
extern "C" void ScreenFadeIn_1cf740(s32, s32);
extern "C" void GameDataLatchLeaderId_2f38e0(void);
extern "C" void SetGameModePhase_1f59a0(s32);
extern "C" s32 MapIdListsMaxPendingHeapSize_1e5080(s32);
extern "C" s32 MapLoadIsSettledMaybe_1e4e10(s32, s32);
extern "C" void MainMenuSysOpenMaybe_204a50(void);
extern "C" void MainMenuOpen_204a20(void);
extern "C" s32 ReturnTrue_204a10(void);
extern "C" void MenuModeResTeardownMaybe_2048e0(s32);
extern "C" void PartyLoadSlotsFill_2f46d0(void);
extern "C" void SceneSoundMutePush_2f6710(void);
extern "C" void SceneSoundMutePop_2f6670(void);
extern "C" void SceneOverlayModeOn_288340(void);
extern "C" void SceneOverlayModeOff_288300(void);
extern "C" s32 IsInBattle_288420(void);
extern "C" s32 MainMenuIsFadingThunkMaybe_2974e0(void);
extern "C" s32 MainMenuGetExitCodeThunkMaybe_2974d0(void);
extern "C" void TaskSetRenderTasksEnabled_287b90(s32);
extern "C" void GameReqQueuePushFront_1f5ab0(s32, s32);
extern "C" void PartyRefreshMembersMaybe_2f40b0(s32);
extern "C" void PartyApplyLeaderChange_2f36f0(void);
extern "C" void CameraSnapReqAt_1f6d70(s32);
extern "C" void CameraSnapReqEye_1f6d60(s32);
extern "C" void CameraSnapSetYawOffset_1f6d50(f32);
extern "C" void CameraSnapToLeader_1f6a00(void);
extern "C" s32 PartyCountMembers_3c2010(Pty *, s32, s32);
extern "C" s32 PartyGetMemberId_3c2490(Pty *, s32);
extern "C" Chr *ObjRecGetLiveObject_1c4a90(s32, s32);
extern "C" s32 ActionMgrFindById_233b50(s32, s32);
extern "C" Obj *PartyFindActiveChara_3c2350(Pty *, s32);
extern "C" s32 CharaGetModelObj_2386f0(s32);
extern "C" void CharaGetPos_2388a0(s32, Vec4 *);
extern "C" void CharaGetRot_2388b0(s32, Vec4 *);
extern "C" void ModelSetPos_151110(Chr *, Vec4 *);
extern "C" void ModelSetRot_151080(Chr *, Vec4 *);
extern "C" void ModelObjPlayMotionByName_1867a0(Chr *, void *, s32);
extern "C" void CharaSetModelObj_238700(s32, Chr *);
extern "C" void ActionMgrLoadActionInfo_2336b0(s32, s32);
extern "C" s32 ActorFindById_3eb870(Gm *, s32);
extern "C" void CharaPreUpdate_20f3a0(s32);
extern "C" void CharaActDispatch_20d190(s32, s32 *);
extern "C" f32 GameSceneGetTimeStep_1ceba0(s32);
extern "C" void CharaPostUpdateMaybe_20f0b0(s32, f32);
extern "C" s32 CharaResIsReadyById_1f0400(s32, s32);
extern "C" s32 CharaResSptLoadDoneMaybe_1f08f0(s32, s32);

extern "C" u8 D_00460118[];
extern "C" u8 D_00460148[];
extern "C" u8 D_00460320[];
extern "C" u8 D_00460338[];
extern "C" u8 D_00460368[];
extern "C" u8 D_00460408[];
extern "C" u8 D_00460588[];
extern "C" u8 D_00460850[];
extern "C" u8 D_00460970[];
extern "C" u8 D_00460988[];
extern "C" u8 D_00460AC8[];
extern "C" u8 D_00460C48[];
extern "C" u8 D_00460C88[];
extern "C" u8 D_00460D58[];
extern "C" s32 D_0047EA40;
extern "C" s8 D_00482274;
extern "C" u8 D_004B2570[];
extern "C" s32 D_004D7E90[];
extern "C" u8 D_004D7F94[];

extern "C" s32 MainMenuModeUpdate_27d460(void)
{
    Vec4 pos;
    Vec4 rot;
    s32 tmp[2];
    Gm *gm;
    s32 ctx;
    s32 a;
    s32 b;
    s32 c;
    s32 n;
    s32 i;
    Chr *ch;
    s32 w;
    s32 id;
    Obj *u;

    gm = GetGameData_1fede0();
    ctx = GetCurrentScene_1f5be0();
    a = GetMapMgr_201a90();
    b = GetActionMgr_1fdb50();
    c = GetCharaResMgr_1fdb60();
    GameReqQueueRemoveById_1f5a10(0xC);
    GameReqQueueRemoveById_1f5a10(0xD);
    GameReqQueueRemoveById_1f5a10(0x11);
    GameReqQueueRemoveById_1f5a10(0x13);
    GameReqQueueRemoveById_1f5a10(0x14);
    if (D_00482274 == 0) {
        D_004D7E90[0] = 0;
        D_004D7F94[0] = 0;
        D_00482274 = 1;
    }
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        GameReqQueueRemoveById_1f5a10(0xE);
        SetGameReqHold_1f5890();
        PadSaveRepeatConfig_1838f0(D_004B2570, D_004D7E90);
        TaskStatePushAll_27c220();
        TaskDisableFieldHudSet_285ff0();
        TaskSetEnabled_27c2a0(0, D_00460118);
        TaskSetEnabled_27c2a0(0, D_00460C88);
        TaskSetEnabled_27c2a0(0, D_00460368);
        TaskSetEnabled_27c2a0(0, D_00460850);
        TaskSetEnabled_27c2a0(0, D_00460320);
        TaskSetEnabled_27c2a0(0, D_00460970);
        TaskSetEnabled_27c2a0(0, D_00460338);
        TaskSetEnabled_27c2a0(0, D_00460988);
        GameSceneSoundSlot0PlaySe_1d05b0(ctx, 2);
        ScreenFadeReset_1cf760(ctx);
        GameDataLatchLeaderId_2f38e0();
        SetGameModePhase_1f59a0(0);
        return 0;
    case 0:
        if (MapIdListsMaxPendingHeapSize_1e5080(a) > 0x15E00 && MapLoadIsSettledMaybe_1e4e10(a, 0) == 0) {
            return 0;
        }
        MainMenuSysOpenMaybe_204a50();
        PartyLoadSlotsFill_2f46d0();
        SetGameModePhase_1f59a0(1);
        return 0;
    case 1:
        ScreenFadeReset_1cf760(ctx);
        SetGameModePhase_1f59a0(2);
    case 2:
        SetGameReqHold_1f5890();
        TaskEnableLoadingSet_285f90();
        TaskSetEnabled_27c2a0(1, D_00460408);
        TaskSetEnabled_27c2a0(1, D_00460AC8);
        TaskSetEnabled_27c2a0(1, D_00460588);
        TaskSetEnabled_27c2a0(1, D_00460C48);
        SceneSoundMutePush_2f6710();
        SceneOverlayModeOn_288340();
        D_0047EA40 = gm->x18->x18E;
        SetGameModePhase_1f59a0(100);
        return 0;
    case 100:
        if (ReturnTrue_204a10() == 0) {
            return 0;
        }
        SetGameModePhase_1f59a0(200);
        return 1;
    case 200:
        TaskSetRenderTasksEnabled_287b90(MainMenuIsFadingThunkMaybe_2974e0() != 0);
        TaskSetEnabled_27c2a0(1, D_00460C48);
        switch ((s16)MainMenuGetExitCodeThunkMaybe_2974d0()) {
        case 1:
            return 0;
        case 2:
            SetGameModePhase_1f59a0(300);
            PartyRefreshMembersMaybe_2f40b0(0);
            SceneOverlayModeOff_288300();
            break;
        case 3:
            GameReqQueuePushFront_1f5ab0(0xE, 0);
        default:
            SetGameModePhase_1f59a0(400);
            SceneSoundMutePop_2f6670();
            SceneOverlayModeOff_288300();
            TaskStatePopAll_27c250();
            break;
        }
        return 1;
    case 400:
        MenuModeResTeardownMaybe_2048e0(0);
        PartyRefreshMembersMaybe_2f40b0(0);
        PartyApplyLeaderChange_2f36f0();
n = gm->x18->x18E; if (D_0047EA40 != n) {
            CameraSnapReqAt_1f6d70(1);
            CameraSnapReqEye_1f6d60(1);
            CameraSnapSetYawOffset_1f6d50(0.0f);
            CameraSnapToLeader_1f6a00();
}
        SetGameModePhase_1f59a0(401);
        return 1;
    case 401:
        TaskSetEnabled_27c2a0(1, D_00460148);
        n = PartyCountMembers_3c2010(gm->x18, 1, 1);
        for (i = 0; i < n; i++) {
            id = PartyGetMemberId_3c2490(gm->x18, i);
            ch = ObjRecGetLiveObject_1c4a90(ctx, id);
            w = ActionMgrFindById_233b50(b, id);
            u = PartyFindActiveChara_3c2350(gm->x18, id);
            if (w != 0 && ch != 0 && CharaGetModelObj_2386f0(w) == 0) {
                CharaGetPos_2388a0(w, &pos);
                CharaGetRot_2388b0(w, &rot);
                ModelSetPos_151110(ch, &pos);
                ModelSetRot_151080(ch, &rot);
                ModelObjPlayMotionByName_1867a0(ch, D_00460D58, 0);
                ch->x464 = 0x1F;
                ch->x468 = 1;
                ch->Set(0.0f);
                CharaSetModelObj_238700(w, ch);
                ActionMgrLoadActionInfo_2336b0(b, id);
                tmp[0] = ActorFindById_3eb870(gm, id);
                CharaPreUpdate_20f3a0(w);
                CharaActDispatch_20d190(w, tmp);
                CharaPostUpdateMaybe_20f0b0(w, GameSceneGetTimeStep_1ceba0(ctx));
                if (u != 0) {
                    u->Act();
                }
            }
            if (CharaResIsReadyById_1f0400(c, id) == 0) {
                break;
            }
            if (IsInBattle_288420() != 0 && CharaResSptLoadDoneMaybe_1f08f0(c, id) == 0) {
                break;
            }
        }
        if (i != n) {
            return 0;
        }
        SetGameModePhase_1f59a0(500);
        return 1;
    case 500:
        GameReqQueuePushFront_1f5ab0(0, -1);
        PadApplyRepeatConfig_183800(D_004B2570, D_004D7E90);
        ClearGameReqHold_1f5880();
        return 0;
    case 300:
        GameReqQueuePushFront_1f5ab0(0x10, -1);
        ClearGameReqHold_1f5880();
        SetGameModePhase_1f59a0(0x12D);
        return 0;
    case 301:
        SetGameReqHold_1f5890();
        MainMenuOpen_204a20();
        SetGameModePhase_1f59a0(0x12E);
        return 1;
    case 302:
        if (MapLoadIsSettledMaybe_1e4e10(a, 0) == 0) {
            return 0;
        }
        ScreenFadeIn_1cf740(ctx, 0x1E);
        SetGameModePhase_1f59a0(2);
        return 1;
    }
    return 0;
}
