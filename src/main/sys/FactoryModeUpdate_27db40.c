#include "types.h"

/* The title/boot state machine's step function: one switch on the phase,
   ten cases, each advancing the phase with SetGameModePhase_1f59a0().

   ★ The case ORDER is read off the compare chain and written BACKWARDS
   (subsystem-decomp-track section 2): retail tests 0xC9, 0xC8, 0x64, 5, 4,
   3, 2, 1, 0, -1 in that order, so the source is -1, 0, 1, 2, 3, 4, 5, 100,
   200, 201 -- which is also the order the bodies are laid out in. */

extern const char D_0045FF88[];
extern const char D_004601D0[];
extern const char D_00460500[];
extern const char D_00460588[];
extern const char D_00460700[];
extern const char D_00460860[];
extern const char D_00460C30[];
extern const char D_00460C48[];
extern const char D_00460D60[];

extern void OverlayLoad_1c3210(s32);
extern s32  LoaderCountQueued_1cd620(s32);
extern s32  ScreenFadeIsDone_1cf6c0(s32);
extern void ScreenFadeOutColor_1cf730(s32, s32, f32, f32, f32);
extern void ScreenFadeIn_1cf740(s32, s32);
extern void StreamMgrSetChanVolumeFade_1d63a0(s32, s32, s32, f32);
extern void StreamMgrPauseChan_1d6630(s32, s32);
extern void MapMgrSlotsReleaseMotionEvents_1e15a0(s32);
extern void MapReleaseSlot3Area_1e2dc0(s32, s32);
extern void MapReleaseSlot2Area_1e2de0(s32, s32);
extern void MapBlockIdListAdd_1e3320(s32, s32);
extern void MapSetSlot2AreaIdByName_1e40c0(s32, const char *);
extern s32  MapLoadIsSettledMaybe_1e4e10(s32, s32);
extern void ClearGameReqHold_1f5880(void);
extern s32  GetGameModePhase_1f59b0(void);
extern void SetGameModePhase_1f59a0(s32);
extern s32  GetLoaderMgr_1f59d0(void);
extern void GameReqQueueRemoveById_1f5a10(s32);
extern s32  GetCurrentScene_1f5be0(void);
extern s32  GetActionMgr_1fdb50(void);
extern s32  GetGameData_1fede0(void);
extern void PartyLeaderRebuildBlockIdList_2012e0(void);
extern void FactoryMenuRelease_204810(void);
extern void FactoryMenuOpen_2048b0(void);
extern s32  FactoryMenuResReady_204890(void);
extern void MenuModeResTeardownMaybe_2048e0(s32);
extern s32  GetMapMgr_201a90(void);
extern void BgmResumeSavedTrack_207420(s32);
extern s32  GetStreamMgr_207ea0(void);
extern void TaskEnableFactorySet_286150(void);
extern void TaskStatePushAll_27c220(void);
extern void TaskStatePopAll_27c250(void);
extern void TaskSetEnabled_27c2a0(s32, const char *);

extern s32  GetEffectMgr_2d9040(void);
extern void EffectGroupSetHidden_2e2bd0(s32, s32, s32);
extern void EffectGroupSetPaused_2e2c80(s32, s32, s32);
extern void FieldViewModeReset_2f3510(void);
extern void FieldModeResReleaseMaybe_2f35b0(void);
extern void SceneSoundMutePop_2f6670(void);
extern void FactoryFloorBuild_3679f0(s32);
extern void FactorySetupPoolsAndLoadLayout_367a30(void);
extern void FactoryTerm_367c00(void);
extern void FactoryInit_367cd0(void);
extern s32  FactoryLoadIsIdle_367ca0(void);
extern s32  FactoryMenuIsActiveThunk_4ec3e0(void);
extern void GameReqQueuePushFront_1f5ab0(s32, s32);

s32 FactoryModeUpdate_27db40(void)
{
    s32 scene;
    s32 world;
    s32 snd;

    GetGameData_1fede0();
    scene = GetCurrentScene_1f5be0();
    world = GetMapMgr_201a90();
    GetActionMgr_1fdb50();
    GameReqQueueRemoveById_1f5a10(0x10);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        ClearGameReqHold_1f5880();
        TaskStatePushAll_27c220();
        TaskSetEnabled_27c2a0(1, D_00460588);
        TaskSetEnabled_27c2a0(1, D_00460C48);
        TaskSetEnabled_27c2a0(0, D_004601D0);
        snd = GetEffectMgr_2d9040();
        EffectGroupSetPaused_2e2c80(snd, 0xBB8, 1);
        EffectGroupSetHidden_2e2bd0(snd, 0xBB8, 1);
        SetGameModePhase_1f59a0(0);
        return 0;
    case 0:
        if (LoaderCountQueued_1cd620(GetLoaderMgr_1f59d0()) > 0) {
            return 0;
        }
        ScreenFadeOutColor_1cf730(scene, 0x2D, 0.0f, 0.0f, 0.0f);
        snd = GetStreamMgr_207ea0();
        StreamMgrSetChanVolumeFade_1d63a0(snd, 0, 0x2D, 0.0f);
        StreamMgrSetChanVolumeFade_1d63a0(snd, 1, 0x2D, 0.0f);
        StreamMgrSetChanVolumeFade_1d63a0(snd, 2, 0x2D, 0.0f);
        SetGameModePhase_1f59a0(1);
        return 0;
    case 1:
        if (ScreenFadeIsDone_1cf6c0(scene) == 0) {
            return 0;
        }
        snd = GetStreamMgr_207ea0();
        StreamMgrPauseChan_1d6630(snd, 0);
        StreamMgrPauseChan_1d6630(snd, 1);
        StreamMgrPauseChan_1d6630(snd, 2);
        SetGameModePhase_1f59a0(2);
        return 0;
    case 2:
        if (MapLoadIsSettledMaybe_1e4e10(world, 0) == 0) {
            return 0;
        }
        MapLoadIsSettledMaybe_1e4e10(world, 1);
        OverlayLoad_1c3210(4);
        MenuModeResTeardownMaybe_2048e0(1);
        FieldModeResReleaseMaybe_2f35b0();
        FactoryInit_367cd0();
        SceneSoundMutePop_2f6670();
        MapMgrSlotsReleaseMotionEvents_1e15a0(world);
        TaskEnableFactorySet_286150();
        TaskSetEnabled_27c2a0(0, D_0045FF88);
        TaskSetEnabled_27c2a0(0, D_00460860);
        TaskSetEnabled_27c2a0(0, D_00460500);
        TaskSetEnabled_27c2a0(0, D_00460C30);
        TaskSetEnabled_27c2a0(0, D_00460700);
        MapSetSlot2AreaIdByName_1e40c0(world, D_00460D60);
        MapBlockIdListAdd_1e3320(world, 0x2EE0);
        SetGameModePhase_1f59a0(3);
        return 0;
    case 3:
        if (MapLoadIsSettledMaybe_1e4e10(world, 0) == 0) {
            return 0;
        }
        FactoryMenuOpen_2048b0();
        FactoryFloorBuild_3679f0(0x2EE2);
        SetGameModePhase_1f59a0(4);
        return 0;
    case 4:
        if (FactoryMenuResReady_204890() == 0) {
            return 0;
        }
        if (MapLoadIsSettledMaybe_1e4e10(world, 0) == 0) {
            return 0;
        }
        TaskSetEnabled_27c2a0(1, D_0045FF88);
        TaskSetEnabled_27c2a0(1, D_00460860);
        FactorySetupPoolsAndLoadLayout_367a30();
        SetGameModePhase_1f59a0(5);
        return 0;
    case 5:
        if (FactoryLoadIsIdle_367ca0() == 0) {
            return 0;
        }
        TaskSetEnabled_27c2a0(1, D_00460500);
        TaskSetEnabled_27c2a0(1, D_00460C30);
        TaskSetEnabled_27c2a0(1, D_00460700);
        ScreenFadeIn_1cf740(scene, 0xF);
        SetGameModePhase_1f59a0(0x64);
        return 1;
    case 100:
        if (FactoryMenuIsActiveThunk_4ec3e0() != 0) {
            return 0;
        }
        ScreenFadeOutColor_1cf730(scene, 0x2D, 0.0f, 0.0f, 0.0f);
        BgmResumeSavedTrack_207420(1);
        snd = GetStreamMgr_207ea0();
        StreamMgrSetChanVolumeFade_1d63a0(snd, 0, 0x2D, 0.0f);
        StreamMgrSetChanVolumeFade_1d63a0(snd, 1, 0x2D, 0.0f);
        StreamMgrSetChanVolumeFade_1d63a0(snd, 2, 0x2D, 0.0f);
        SetGameModePhase_1f59a0(0xC8);
        return 1;
    case 200:
        if (ScreenFadeIsDone_1cf6c0(scene) == 0) {
            return 0;
        }
        MapReleaseSlot2Area_1e2de0(world, 1);
        MapReleaseSlot3Area_1e2dc0(world, 1);
        FactoryMenuRelease_204810();
        FactoryTerm_367c00();
        PartyLeaderRebuildBlockIdList_2012e0();
        snd = GetEffectMgr_2d9040();
        EffectGroupSetPaused_2e2c80(snd, 0xBB8, 0);
        EffectGroupSetHidden_2e2bd0(snd, 0xBB8, 0);
        snd = GetStreamMgr_207ea0();
        StreamMgrPauseChan_1d6630(snd, 0);
        StreamMgrPauseChan_1d6630(snd, 1);
        StreamMgrPauseChan_1d6630(snd, 2);
        SetGameModePhase_1f59a0(0xC9);
        return 0;
    case 201:
        if (MapLoadIsSettledMaybe_1e4e10(world, 0) == 0) {
            return 0;
        }
        FieldViewModeReset_2f3510();
        TaskStatePopAll_27c250();
        ClearGameReqHold_1f5880();
        GameReqQueuePushFront_1f5ab0(0, -1);
        OverlayLoad_1c3210(3);
        return 0;
    }
    return 0;
}
