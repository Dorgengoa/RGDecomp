#include "types.h"

/* Phase driver of the SetGameModePhase_1f59a0 family.  Compare chain is 0x65, 0x64, 4,
   3, 2, 1, 0, -1, so the source order is -1, 0, 1, 2, 3, 4, 100, 101 and the
   bodies are laid out in that order.

   ★ D_004821F4 is RELOADED from gp before each StreamMgrSetChanVolumeFade_1d63a0 argument and
   forwarded from the store only for the ScreenFadeOutColor_1cf730 call immediately after
   it -- i.e. the source names the global at every use, and the one that
   reads as a constant is mwcc forwarding across a call-free gap. */

struct Root {
    u8  pad0[0xC];
    s32 mC;
};

extern const char D_004600B8[];
extern const char D_004601D0[];
extern const char D_00460588[];
extern const char D_004605C0[];
extern const char D_004605D8[];
extern const char D_00460C48[];
extern const char D_00460CD0[];

extern s32 D_004821F4;

extern s32  CdDiscGetCurrent_1c3080(void);
extern void CdDiscSelect_1c3090(s32);
extern s32  LoaderCountQueued_1cd620(s32);
extern void ScreenFadeOutColor_1cf730(s32, s32, f32, f32, f32);
extern void ScreenFadeIn_1cf740(s32, s32);
extern void GameSceneSoundFadeOut_1d0340(s32, s32);
extern void GameSceneSoundFadeIn_1d0350(s32, s32);
extern void StreamMgrSetChanVolumeFade_1d63a0(s32, s32, s32, f32);
extern void StreamMgrPauseChan_1d6630(s32, s32);
extern void StreamMgrStopChan_1d66b0(s32, s32);
extern s32  MapLoadIsSettledMaybe_1e4e10(s32, s32);
extern void ClearGameReqHold_1f5880(void);
extern void SetGameReqHold_1f5890(void);
extern void SetGameModePhase_1f59a0(s32);
extern s32  GetGameModePhase_1f59b0(void);
extern s32  GetLoaderMgr_1f59d0(void);
extern void GameReqQueueRemoveById_1f5a10(s32);
extern void GameReqQueuePushFront_1f5ab0(s32, s32);
extern s32  GetCurrentScene_1f5be0(void);
extern struct Root *GetGameData_1fede0(void);
extern s32  GetMapMgr_201a90(void);
extern void BgmRequestTrack_2077e0(s32, s32);
extern void BgmPlayTrackIfChangedMaybe_207880(s32, s32);
extern s32  GetStreamMgr_207ea0(void);
extern void TaskStatePushAll_27c220(void);
extern void TaskStatePopAll_27c250(void);
extern void TaskSetEnabled_27c2a0(s32, const char *);
extern void TaskSetUpdateTasksPaused_287dd0(s32);
extern s32  StateGetRequiredDisc_3d5ed0(s32);
extern void OptionsSetDataSetIndexMaybe_3d5f00(s32, s32);

s32 DiscChangeModeUpdate_2850b0(void)
{
    struct Root *root;
    s32 scene;
    s32 world;
    s32 h;
    s32 id;
    s32 cur;

    scene = GetCurrentScene_1f5be0();
    world = GetMapMgr_201a90();
    root = GetGameData_1fede0();
    GameReqQueueRemoveById_1f5a10(4);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        TaskSetEnabled_27c2a0(0, D_004601D0);
        TaskSetEnabled_27c2a0(0, D_004600B8);
        id = StateGetRequiredDisc_3d5ed0(root->mC);
        cur = CdDiscGetCurrent_1c3080();
        if (cur != id) {
            SetGameModePhase_1f59a0(0);
        } else {
            SetGameModePhase_1f59a0(0x65);
        }
        return 1;
    case 0:
        if (LoaderCountQueued_1cd620(GetLoaderMgr_1f59d0()) > 0) {
            return 0;
        }
        D_004821F4 = 0x1E;
        ScreenFadeOutColor_1cf730(scene, D_004821F4, 0.0f, 0.0f, 0.0f);
        h = GetStreamMgr_207ea0();
        StreamMgrSetChanVolumeFade_1d63a0(h, 0, D_004821F4, 0.0f);
        StreamMgrSetChanVolumeFade_1d63a0(h, 1, D_004821F4, 0.0f);
        StreamMgrSetChanVolumeFade_1d63a0(h, 2, D_004821F4, 0.0f);
        GameSceneSoundFadeOut_1d0340(scene, D_004821F4);
        SetGameModePhase_1f59a0(1);
        return 0;
    case 1:
        D_004821F4 = D_004821F4 - 1;
        if (D_004821F4 >= 0) {
            return 0;
        }
        TaskSetUpdateTasksPaused_287dd0(1);
        TaskSetEnabled_27c2a0(1, D_00460588);
        TaskSetEnabled_27c2a0(1, D_00460C48);
        TaskSetEnabled_27c2a0(0, D_004601D0);
        TaskSetEnabled_27c2a0(0, D_004605D8);
        TaskSetEnabled_27c2a0(0, D_004605C0);
        h = GetStreamMgr_207ea0();
        StreamMgrPauseChan_1d6630(h, 0);
        StreamMgrPauseChan_1d6630(h, 1);
        StreamMgrPauseChan_1d6630(h, 2);
        StreamMgrStopChan_1d66b0(h, 0);
        StreamMgrStopChan_1d66b0(h, 1);
        StreamMgrStopChan_1d66b0(h, 2);
        BgmPlayTrackIfChangedMaybe_207880(0, 1);
        BgmRequestTrack_2077e0(0, 1);
        SetGameModePhase_1f59a0(2);
        return 0;
    case 2:
        if (MapLoadIsSettledMaybe_1e4e10(world, 0) == 0) {
            return 0;
        }
        MapLoadIsSettledMaybe_1e4e10(world, 1);
        TaskSetEnabled_27c2a0(1, D_00460CD0);
        SetGameModePhase_1f59a0(3);
        return 0;
    case 3:
        SetGameModePhase_1f59a0(4);
        return 0;
    case 4:
        CdDiscSelect_1c3090(StateGetRequiredDisc_3d5ed0(root->mC));
        OptionsSetDataSetIndexMaybe_3d5f00(root->mC, -1);
        TaskSetEnabled_27c2a0(0, D_00460CD0);
        StreamMgrSetChanVolumeFade_1d63a0(GetStreamMgr_207ea0(), 0, 0x1E, 1.0f);
        GameSceneSoundFadeIn_1d0350(scene, 0x1E);
        SetGameModePhase_1f59a0(0x64);
        return 1;
    case 100:
        ScreenFadeIn_1cf740(scene, 0x1E);
        SetGameModePhase_1f59a0(0x65);
        break;
    case 101:
        GameReqQueuePushFront_1f5ab0(0, -1);
        TaskStatePopAll_27c250();
        ClearGameReqHold_1f5880();
        return 1;
    }
    return 0;
}
