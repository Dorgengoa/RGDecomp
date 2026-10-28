/* rgp:protos */
#define RGP_SELF_FactoryModeUpdate_27db40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The title/boot state machine's step function: one switch on the phase,
   ten cases, each advancing the phase with SetGameModePhase_1f59a0().

   ★ The case ORDER is read off the compare chain and written BACKWARDS
   (subsystem-decomp-track section 2): retail tests 0xC9, 0xC8, 0x64, 5, 4,
   3, 2, 1, 0, -1 in that order, so the source is -1, 0, 1, 2, 3, 4, 5, 100,
   200, 201 -- which is also the order the bodies are laid out in. */

extern char D_0045FF88[];
extern char D_004601D0[];
extern char D_00460500[];
extern char D_00460588[];
extern char D_00460700[];
extern char D_00460860[];
extern char D_00460C30[];
extern char D_00460C48[];
extern char D_00460D60[];

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

s32 FactoryModeUpdate_27db40(void)
{
    s32 scene;
    s32 world;
    s32 snd;

    GetGameData_1fede0();
    scene = GetCurrentScene_1f5be0();
    world = ((s32)GetMapMgr_201a90());
    GetActionMgr_1fdb50();
    GameReqQueueRemoveById_1f5a10(0x10);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        ClearGameReqHold_1f5880();
        TaskStatePushAll_27c220();
        TaskSetEnabled_27c2a0(1, D_00460588);
        TaskSetEnabled_27c2a0(1, D_00460C48);
        TaskSetEnabled_27c2a0(0, D_004601D0);
        snd = ((s32)GetEffectMgr_2d9040());
        EffectGroupSetPaused_2e2c80(snd, 0xBB8, 1);
        EffectGroupSetHidden_2e2bd0(snd, 0xBB8, 1);
        SetGameModePhase_1f59a0(0);
        return 0;
    case 0:
        if (LoaderCountQueued_1cd620(((s32)GetLoaderMgr_1f59d0())) > 0) {
            return 0;
        }
        ScreenFadeOutColor_1cf730(scene, 0x2D, 0.0f, 0.0f, 0.0f);
        snd = ((s32)GetStreamMgr_207ea0());
        StreamMgrSetChanVolumeFade_1d63a0(snd, 0, 0x2D, 0.0f);
        StreamMgrSetChanVolumeFade_1d63a0(snd, 1, 0x2D, 0.0f);
        StreamMgrSetChanVolumeFade_1d63a0(snd, 2, 0x2D, 0.0f);
        SetGameModePhase_1f59a0(1);
        return 0;
    case 1:
        if (ScreenFadeIsDone_1cf6c0(scene) == 0) {
            return 0;
        }
        snd = ((s32)GetStreamMgr_207ea0());
        StreamMgrPauseChan_1d6630(snd, 0);
        StreamMgrPauseChan_1d6630(snd, 1);
        StreamMgrPauseChan_1d6630(snd, 2);
        SetGameModePhase_1f59a0(2);
        return 0;
    case 2:
        if (((unsigned char)MapLoadIsSettledMaybe_1e4e10(world, 0)) == 0) {
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
        if (((unsigned char)MapLoadIsSettledMaybe_1e4e10(world, 0)) == 0) {
            return 0;
        }
        FactoryMenuOpen_2048b0();
        FactoryFloorBuild_3679f0(0x2EE2);
        SetGameModePhase_1f59a0(4);
        return 0;
    case 4:
        if (((unsigned char)FactoryMenuResReady_204890()) == 0) {
            return 0;
        }
        if (((unsigned char)MapLoadIsSettledMaybe_1e4e10(world, 0)) == 0) {
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
        if (((unsigned char)FactoryMenuIsActiveThunk_4ec3e0()) != 0) {
            return 0;
        }
        ScreenFadeOutColor_1cf730(scene, 0x2D, 0.0f, 0.0f, 0.0f);
        BgmResumeSavedTrack_207420(1);
        snd = ((s32)GetStreamMgr_207ea0());
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
        snd = ((s32)GetEffectMgr_2d9040());
        EffectGroupSetPaused_2e2c80(snd, 0xBB8, 0);
        EffectGroupSetHidden_2e2bd0(snd, 0xBB8, 0);
        snd = ((s32)GetStreamMgr_207ea0());
        StreamMgrPauseChan_1d6630(snd, 0);
        StreamMgrPauseChan_1d6630(snd, 1);
        StreamMgrPauseChan_1d6630(snd, 2);
        SetGameModePhase_1f59a0(0xC9);
        return 0;
    case 201:
        if (((unsigned char)MapLoadIsSettledMaybe_1e4e10(world, 0)) == 0) {
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
