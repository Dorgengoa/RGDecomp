/* rgp:protos */
#line 1
#include "types.h"

class Chr {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;              
    void Set(f32 a0) { VCM(void, (void *, f32), 0x44, a0); } /* 0x44 */
    u8 pad1B4[0x464 - 0x1B4];
    s32 x464;
    u8 x468;
};

class Obj {
public:
    VC_VPTR_MEMBER;     
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
        
    void Act() { VCM0(void, 0x1B4); } /* 0x1B4 */
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
    Vec4 pos __attribute__((aligned(16)));
    Vec4 rot __attribute__((aligned(16)));
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
        if (MapIdListsMaxPendingHeapSize_1e5080(a) > 0x15E00 && ((unsigned char)MapLoadIsSettledMaybe_1e4e10(a, 0)) == 0) {
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
        switch ((s16)((short)MainMenuGetExitCodeThunkMaybe_2974d0())) {
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
            id = ((short)PartyGetMemberId_3c2490(gm->x18, i));
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
            if (((unsigned char)IsInBattle_288420()) != 0 && ((unsigned char)CharaResSptLoadDoneMaybe_1f08f0(c, id)) == 0) {
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
        if (((unsigned char)MapLoadIsSettledMaybe_1e4e10(a, 0)) == 0) {
            return 0;
        }
        ScreenFadeIn_1cf740(ctx, 0x1E);
        SetGameModePhase_1f59a0(2);
        return 1;
    }
    return 0;
}
