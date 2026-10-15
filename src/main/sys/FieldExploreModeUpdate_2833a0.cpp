#include "types.h"
#include "vec.h"

typedef struct Buf33a0 {
    u8 pad[0x30];
} Buf33a0;

typedef struct Sub18_33a0 {
    u8 pad0[0x30];
    s16 m30;
    u8 pad32[0x18E - 0x32];
    s16 m18E;
} Sub18_33a0;

typedef struct Sub8_33a0 {
    u8 pad0[0x6C];
    s32 m6C;
} Sub8_33a0;

typedef struct Ctx33a0 {
    u8 pad0[8];
    Sub8_33a0 *m8;
    u8 padC[4];
    s32 m10;
    u8 pad14[4];
    Sub18_33a0 *m18;
} Ctx33a0;

typedef struct Ob33a0 {
    u8 pad0[0x60];
    s32 m60;
} Ob33a0;

typedef struct Ev33a0 {
    s16 m0;
    u8 pad2[0x1C];
    u8 m1E;
} Ev33a0;

typedef struct R41c {
    u8 pad0[8];
    s16 m8;
} R41c;

typedef struct Q70e0 {
    u8 pad0[4];
    f32 m4;
    f32 m8;
    u8 padC[4];
    f32 m10;
} Q70e0;

typedef struct R80c0 {
    u8 pad0[0x10];
    s16 *m10;
} R80c0;

typedef struct W6ad0 {
    s32 m0;
    R80c0 *m4;
} W6ad0;

typedef struct St21D0 {
    s16 id;
    s16 v;
    u8 b0:1;
    u8 b1:1;
    u8 b2:1;
    u8 b3:5;
} St21D0;

extern "C" {
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
s32 PadIsTriggered_1839f0(void *, s32);
void PadUpdateVibration_184250(void *, s32);
void PadUpdate_1843a0(void *);
Ev33a0 *SysGetModeMsg_1c39b0(void);
f32 VecDot3_1cba90(Vec4 *, Vec4 *);
void VecNormalize_1cbb80(Vec4 *, Vec4 *);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
void GameSceneSetTimeScaleLockedMaybe_1ceb90(s32, s32);
void ScreenFadeCaptureFrame_1cf550(s32);
s32 ScreenFadeIsDone_1cf6c0(s32);
void ScreenFadeDissolveIn_1cf720(s32, s32, f32);
void ScreenFadeOutColor_1cf730(s32, s32, f32, f32, f32);
void ScreenFadeIn_1cf740(s32, s32);
void ScreenFadeReset_1cf760(s32);
void GameSceneSoundSlot0PlaySeVol_1d05f0(s32, s32, f32);
void MapMgrMinimapExitFullView_1e26c0(Ob33a0 *);
void MapMgrMinimapEnterFullView_1e2760(Ob33a0 *);
s32 MapSlotsFindActiveBlockById_1e4730(s32, s32, s32);
s32 MapLoadIsSettledMaybe_1e4e10(Ob33a0 *, s32);
s32 MapDataIsJasterOnly_1e7a90(s32);
void ClearGameReqHold_1f5880(void);
void SetGameReqHold_1f5890(void);
void SetGameModePhase_1f59a0(s32);
s32 GetGameModePhase_1f59b0(void);
void GameReqQueueRemoveById_1f5a10(s32);
s32 GameReqQueuePeekHead_1f5a70(s32);
void GameReqQueuePushFront_1f5ab0(s32, s32);
void GameReqQueuePushBack_1f5b50(s32, s32);
s32 GetCurrentScene_1f5be0(void);
void PartyUpdateLeaderFlags_1fc3c0(void);
s32 GetActionMgr_1fdb50(void);
Ctx33a0 *GetGameData_1fede0(void);
void FuncPointDeactivate_2000e0(s32, s32);
void MapAreaTriggerEventsMaybe_200950(void);
s32 FuncPointGetActiveId_201a00(void);
Ob33a0 *GetMapMgr_201a90(void);
void EasyMenuClose_203060(void);
void EasyMenuOpen_2030d0(void);
W6ad0 *GetSelectedInsectEntryMaybe_206ad0(void);
s32 CharaIsStandOrWalkMaybe_20fe90(s32);
s32 CharaIsFreeMoveStateMaybe_210190(s32);
s32 CharaIsActionFreeMaybe_2105e0(s32);
s32 CharaHasEvObjContact_214960(s32);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaGetPos_2388a0(s32, Vec4 *);
void CharaGetRot_2388b0(s32, Vec4 *);
void MesSlot0Close_278e40(void);
void MesShowMsgByIndex_278fd0(s32, s32);
void TaskTableRestoreOrder_27bed0(void);
void TaskMoveBefore_27bf50(void *, void *);
void TaskStatePushAll_27c220(void);
void TaskStatePopAll_27c250(void);
void TaskSetEnabled_27c2a0(s32, void *);
void GameReqPushWarp_285ea0(s32, s32, s32, s32);
void TaskEnableFieldSet_2874a0(void);
void TaskSetUpdateTasksPaused_287dd0(s32);
Q70e0 *TargetRefGetObjSlot_2e70e0(s32);
s32 TargetRefGetId_2e7120(s32);
s32 TargetRefGetKind_2e7130(s32);
void BattleEncounterSetupMaybe_2f25f0(void);
void FieldViewModeSet_2f3590(s32);
void FieldModeResReleaseMaybe_2f35b0(void);
void FieldViewModeEnter_2f35e0(void);
void FieldViewModeLeave_2f3660(s32, s32);
void PartyApplyLeaderChange_2f36f0(void);
void GameDataLatchLeaderId_2f38e0(void);
s32 PartySwitchLeader_2f3ca0(s32, s32);
void HudFadeOutAll_2f47e0(s32);
void HudFadeInAll_2f4850(s32);
s32 LeaderGetControlStateMaybe_2f5440(void);
void CameraResetLevelViewMaybe_30a150(s32);
void CameraSwitchTo3Fixed_30a2a0(void);
s32 GetTargetMng_313dd0(void);
void TargetMngSetEnabled_31f4e0(s32, s32);
s32 TargetMngGetTargetRef_320820(s32);
R80c0 *InvGetItem4B0_3c80c0(Sub18_33a0 *, s32);
s32 StateFlagTest_3ccd70(s32, s32);
s32 EventFireTriggers_3e2660(Buf33a0 *, s32);
void ActionPacketInitFieldExplore_3e2aa0(Buf33a0 *, s32, s32);
void ActionPacketInitSpaceMenuMaybe_3e39f0(Buf33a0 *, s32, s32, s32);
void ActionPacketReset_3e3d00(Buf33a0 *);
void SkillLockClearResetSpot_3eb6c0(Ctx33a0 *, s32);
void SkillLockSetResetSpot_3eb6f0(Ctx33a0 *, s32);
R41c *GroupGetRecordById_41c2a0(s32, s32, s32, s32);
s32 LeaderSwitchMenuIsActiveThunk_39d200(void);
extern char D_004600B8[];
extern char D_004600F8[];
extern char D_004602E8[];
extern char D_004603B0[];
extern char D_00460588[];
extern char D_004605C0[];
extern char D_00460850[];
extern char D_00460998[];
extern char D_004609C0[];
extern char D_00460A48[];
extern char D_00460A90[];
extern char D_00460C48[];
extern char D_00460C88[];
extern char D_00460CB0[];
extern char D_004B2570[];
extern f32 D_0047DCF0;
extern St21D0 D_004821D0;
extern s32 D_004821D8;
}

extern "C" s32 FieldExploreModeUpdate_2833a0(void)
{
    Buf33a0 bE0;
    Vec4 vD0;
    Vec4 vC0;
    Vec4 vB0;
    Vec4 vA0;
    Vec4 v90;
    Buf33a0 b60;
    Ctx33a0 *ctx;
    s32 sys;
    Ob33a0 *ob;
    s32 h;
    s32 st;

    ctx = GetGameData_1fede0();
    sys = GetCurrentScene_1f5be0();
    ob = GetMapMgr_201a90();
    h = GetActionMgr_1fdb50();
    GameReqQueueRemoveById_1f5a10(6);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        TaskStatePushAll_27c220();
    case 0:
        {
            Ev33a0 *e = SysGetModeMsg_1c39b0();
            if (e != 0 && e->m0 == 6 && (e->m1E & 1)) {
                BattleEncounterSetupMaybe_2f25f0();
                SetGameModePhase_1f59a0(1);
                return 0;
            }
        }
        FieldViewModeSet_2f3590(-1);
    case 1:
        FieldViewModeEnter_2f35e0();
        PartyUpdateLeaderFlags_1fc3c0();
        SkillLockClearResetSpot_3eb6c0(ctx, 0);
        TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 1);
        SetGameReqHold_1f5890();
        TaskEnableFieldSet_2874a0();
        SetGameModePhase_1f59a0(100);
        GameSceneSetTimeScaleLockedMaybe_1ceb90(sys, 0);
        HudFadeInAll_2f4850(15);
    case 100:
        switch (GameReqQueuePeekHead_1f5a70(0)) {
        case 4:
            SetGameModePhase_1f59a0(1);
            ClearGameReqHold_1f5880();
            return 1;
        case 5:
            FuncPointDeactivate_2000e0(0, 0);
            FieldViewModeLeave_2f3660(0xFFFF, 1);
            SetGameModePhase_1f59a0(0x3E8);
            return 1;
        case 13:
        case 14:
            HudFadeOutAll_2f47e0(15);
        case 12:
        case 17:
        case 19:
        case 20:
            MesSlot0Close_278e40();
            TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
            SetGameModePhase_1f59a0(1);
            ClearGameReqHold_1f5880();
            return 1;
        case 7:
            SkillLockSetResetSpot_3eb6f0(ctx, 1);
        case 21:
            FieldViewModeLeave_2f3660(0xFFFF, 1);
        case 11:
            FuncPointDeactivate_2000e0(0, 1);
            TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
            HudFadeOutAll_2f47e0(15);
            SetGameModePhase_1f59a0(1);
            ClearGameReqHold_1f5880();
            return 1;
        case 15:
        case 16:
            TaskSetEnabled_27c2a0(0, D_004605C0);
            SetGameModePhase_1f59a0(0x7D0);
            return 1;
        }
        FieldViewModeEnter_2f35e0();
        {
            s32 r = MapSlotsFindActiveBlockById_1e4730((s32)ob, ctx->m18->m30, 0);
            if (r != 0 && MapDataIsJasterOnly_1e7a90(r) != 0) {
                if (PartySwitchLeader_2f3ca0(0, 1) != 0) {
                    ScreenFadeReset_1cf760(sys);
                    ScreenFadeCaptureFrame_1cf550(sys);
                    ScreenFadeDissolveIn_1cf720(sys, 15, 1.0f);
                }
            } else if (PadIsTriggered_1839f0(D_004B2570, 0x200) != 0) {
                GameDataLatchLeaderId_2f38e0();
                TaskStatePushAll_27c220();
                TaskSetUpdateTasksPaused_287dd0(1);
                TaskSetEnabled_27c2a0(1, D_004603B0);
                TaskSetEnabled_27c2a0(1, D_00460A90);
                TaskSetEnabled_27c2a0(1, D_00460588);
                TaskSetEnabled_27c2a0(1, D_00460C48);
                EasyMenuOpen_2030d0();
                SetGameModePhase_1f59a0(0x1F4);
                return 0;
            }
        }
        if (PadIsTriggered_1839f0(D_004B2570, 0x100) != 0) {
            SetGameModePhase_1f59a0(0x190);
            return 0;
        }
        h = ActionMgrFindById_233b50(h, ctx->m18->m18E);
        if (h != 0 && CharaIsFreeMoveStateMaybe_210190(h) != 0 && PadIsTriggered_1839f0(D_004B2570, 0x400) != 0) {
            CameraSwitchTo3Fixed_30a2a0();
            TaskSetEnabled_27c2a0(0, D_004600B8);
            TaskSetEnabled_27c2a0(0, D_00460C88);
            SetGameModePhase_1f59a0(0x12C);
            return 0;
        }
        if (StateFlagTest_3ccd70(ctx->m10, 0x7F8) != 0) {
            GameReqQueuePushBack_1f5b50(0x11, -1);
            return 1;
        }
        if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
            switch (LeaderGetControlStateMaybe_2f5440()) {
            case 0:
                GameReqQueuePushBack_1f5b50(0x11, -1);
                return 1;
            case 2:
                MesShowMsgByIndex_278fd0(2, 60);
                return 0;
            case 3:
                MesShowMsgByIndex_278fd0(3, 60);
                return 0;
            }
        }
        if (PadIsTriggered_1839f0(D_004B2570, 0x40) == 0) {
            goto ret0;
        }
        if (h == 0) {
            goto ret0;
        }
        if (CharaIsStandOrWalkMaybe_20fe90(h) != 0) {
            MapAreaTriggerEventsMaybe_200950();
            if (GameReqQueuePeekHead_1f5a70(0) != -1) {
                return 1;
            }
            if (FuncPointGetActiveId_201a00() >= 0) {
                ActionPacketReset_3e3d00(&bE0);
                ActionPacketInitFieldExplore_3e2aa0(&bE0, sys, 1);
                if (EventFireTriggers_3e2660(&bE0, 0) == 0) {
                    GameReqQueuePushFront_1f5ab0(0x14, -1);
                    return 1;
                }
            }
        }
        {
            s32 m = TargetMngGetTargetRef_320820(GetTargetMng_313dd0());
            if (m == 0) {
                goto ret0;
            }
            if (CharaIsActionFreeMaybe_2105e0(h) == 0) {
                goto ret0;
            }
            switch (TargetRefGetKind_2e7130(m)) {
            case 3:
                D_004821D0.id = ctx->m18->m18E;
                D_004821D0.v = TargetRefGetId_2e7120(m);
                D_004821D0.b0 = false;
                D_004821D0.b1 = false;
                D_004821D0.b2 = true;
                GameReqQueuePushBack_1f5b50(12, -1);
                return 1;
            case 13:
                {
                    s32 id;
                    bool ok;
                    Q70e0 *q;
                    f32 ang;
                    R41c *r;
                    CharaGetPos_2388a0(h, &vD0);
                    CharaGetRot_2388b0(h, &vC0);
                    vD0.w = 1.0f;
                    vD0.y = 0.0f;
                    id = TargetRefGetId_2e7120(m);
                    r = GroupGetRecordById_41c2a0(ctx->m8->m6C, (s16)id, -1, 0);
                    ok = r != 0 && r->m8 == 0x20;
                    q = TargetRefGetObjSlot_2e70e0(m);
                    D_004821D0.id = ctx->m18->m18E;
                    D_004821D0.v = id;
                    D_004821D0.b0 = true;
                    D_004821D0.b1 = ok;
                    ang = q->m4;
                    vB0.x = Sinf_128fd0(ang);
                    vB0.y = 0.0f;
                    vB0.z = Cosf_128d30(ang);
                    vB0.w = 1.0f;
                    VecNormalize_1cbb80(&vB0, &vB0);
                    vA0.x = q->m8;
                    vA0.y = 0.0f;
                    vA0.z = q->m10;
                    vA0.w = 1.0f;
                    VecSub_1cbd00(&v90, &vA0, &vD0);
                    VecNormalize_1cbb80(&v90, &v90);
                    D_004821D0.b2 = VecDot3_1cba90(&vB0, &v90) < D_0047DCF0;
                    GameReqQueuePushBack_1f5b50(12, -1);
                    return 1;
                }
            case 9:
                if (StateFlagTest_3ccd70(ctx->m10, 0xA3) != 0 && StateFlagTest_3ccd70(ctx->m10, 0xA4) == 0) {
                    GameReqPushWarp_285ea0(0x640, 0x1780, 0x3E8, 0);
                } else {
                    ActionPacketReset_3e3d00(&b60);
                    ActionPacketInitSpaceMenuMaybe_3e39f0(&b60, sys, 1, 1);
                    if (EventFireTriggers_3e2660(&b60, 0) == 0) {
                        GameReqQueuePushBack_1f5b50(0x13, -1);
                        return 1;
                    }
                }
                break;
            case 11:
                D_004821D8 = TargetRefGetId_2e7120(m);
                GameReqQueuePushBack_1f5b50(13, -1);
                return 1;
            case 12:
                {
                    W6ad0 *w = GetSelectedInsectEntryMaybe_206ad0();
                    R80c0 *rr = InvGetItem4B0_3c80c0(ctx->m18, TargetRefGetId_2e7120(m));
                    w->m4 = rr;
                    if (rr != 0) {
                        w->m0 = *rr->m10;
                    } else {
                        w->m0 = -1;
                    }
                    GameSceneSoundSlot0PlaySeVol_1d05f0(sys, 5, 1.0f);
                    GameReqQueuePushBack_1f5b50(14, 2);
                    return 1;
                }
            }
        }
    ret0:
        return 0;
    case 0x12C:
        {
            s32 o = ActionMgrFindById_233b50(h, ctx->m18->m18E);
            if (o == 0 || CharaIsFreeMoveStateMaybe_210190(o) == 0 || PadIsTriggered_1839f0(D_004B2570, 0x400) != 0 || GameReqQueuePeekHead_1f5a70(0) == 11) {
                CameraResetLevelViewMaybe_30a150(CharaHasEvObjContact_214960(o));
                SetGameModePhase_1f59a0(1);
                return 0;
            }
            TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
            TaskSetEnabled_27c2a0(0, D_00460850);
            return 0;
        }
    case 0x190:
        if ((ob->m60 & 4) == 0) {
            TaskMoveBefore_27bf50(D_00460A48, D_00460998);
            TaskStatePushAll_27c220();
            TaskSetUpdateTasksPaused_287dd0(1);
            TaskSetEnabled_27c2a0(1, D_004602E8);
            TaskMoveBefore_27bf50(D_00460998, D_00460CB0);
            TaskSetEnabled_27c2a0(0, D_00460C88);
            MapMgrMinimapEnterFullView_1e2760(ob);
            return 0;
        }
        if (PadIsTriggered_1839f0(D_004B2570, 0x100) != 0) {
            TaskStatePopAll_27c250();
            TaskMoveBefore_27bf50(D_00460998, D_004609C0);
            TaskTableRestoreOrder_27bed0();
            MapMgrMinimapExitFullView_1e26c0(ob);
            SetGameModePhase_1f59a0(100);
        }
        return 0;
    case 0x1F4:
        if (LeaderSwitchMenuIsActiveThunk_39d200() == 0) {
            PartyApplyLeaderChange_2f36f0();
            PadUpdateVibration_184250(D_004B2570, 0);
            PadUpdate_1843a0(D_004B2570);
            EasyMenuClose_203060();
            TaskStatePopAll_27c250();
            SetGameModePhase_1f59a0(1);
            return 0;
        }
        return 0;
    case 0x3E8:
        SetGameModePhase_1f59a0(0x3E9);
        TaskSetEnabled_27c2a0(0, D_004600B8);
        TaskSetEnabled_27c2a0(0, D_004600F8);
        ScreenFadeOutColor_1cf730(sys, 15, 0.0f, 0.0f, 0.0f);
        return 0;
    case 0x3E9:
        if (ScreenFadeIsDone_1cf6c0(sys) == 0) {
            return 0;
        }
        SetGameModePhase_1f59a0(0x3EA);
        ClearGameReqHold_1f5880();
        return 1;
    case 0x3EA:
        ScreenFadeIn_1cf740(sys, 15);
        TaskSetEnabled_27c2a0(1, D_004600B8);
        TaskSetEnabled_27c2a0(1, D_004600F8);
        SetGameReqHold_1f5890();
        SetGameModePhase_1f59a0(0);
        return 1;
    case 0x7D0:
        SetGameModePhase_1f59a0(0x7D1);
        TaskSetEnabled_27c2a0(0, D_004600B8);
        TaskSetEnabled_27c2a0(0, D_004600F8);
        ScreenFadeOutColor_1cf730(sys, 15, 0.0f, 0.0f, 0.0f);
        return 0;
    case 0x7D1:
        if (ScreenFadeIsDone_1cf6c0(sys) == 0) {
            return 0;
        }
        FuncPointDeactivate_2000e0(0, 0);
        FieldViewModeLeave_2f3660(0xFFFF, 1);
        FieldModeResReleaseMaybe_2f35b0();
        TargetMngSetEnabled_31f4e0(GetTargetMng_313dd0(), 0);
        HudFadeOutAll_2f47e0(15);
        SetGameModePhase_1f59a0(0x834);
        ClearGameReqHold_1f5880();
        return 1;
    case 0x834:
        if (MapLoadIsSettledMaybe_1e4e10(ob, 0) == 0) {
            return 0;
        }
        TaskSetEnabled_27c2a0(1, D_004600B8);
        TaskSetEnabled_27c2a0(1, D_004600F8);
        SetGameModePhase_1f59a0(0);
        ScreenFadeIn_1cf740(sys, 15);
        return 1;
    }
    return 0;
}
