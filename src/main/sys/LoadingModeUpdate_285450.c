#include "types.h"

/* A second phase driver of the same family as FactoryModeUpdate_27db40: one switch on
   the phase, every case guarded and every exit its own `return`.

   ★ Outer case ORDER is the compare chain BACKWARDS -- retail tests 0xC9,
   0xC8, 0x65, 0x64, 0, -1, so the source is -1, 0, 100, 101, 200, 201.  The
   inner switch tests 0xD, 0xC, 0xB, so its source is 11, 12, 13 with 12 and
   13 sharing one body.
   ★ `D_004821EC = GetGameModePhase_1f59b0() == 0;` is the u8 bool idiom (xor + sltiu 1),
   and the global really is a byte -- retail stores it with `sb`. */

extern const char D_0045FF98[];
extern const char D_0045FFB8[];
extern const char D_004601D0[];
extern const char D_00460588[];
extern const char D_00460598[];
extern const char D_004605A8[];
extern const char D_004605C0[];
extern const char D_004605D8[];
extern const char D_00460C48[];
extern const char D_00460C58[];
extern const char D_00460CB0[];
extern const char D_00460CE8[];

extern u8  D_004821EC;
extern s32 D_004821F0;

extern void SoundBankStopAll_1bad70(s32);
extern void SoundBankRelease_1bb6e0(s32);
extern void LoaderPurgeAll_1cd240(s32);
extern void StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);
extern void StreamPauseChan_1cd9f0(s32, s32);
extern void StreamStopChan_1cda60(s32, s32);
extern void ScreenFadeOutColor_1cf730(s32, s32, f32, f32, f32);
extern void SetGameExitRequest_1f57d0(s32);
extern s32  GetGameModeAt_1f5830(s32);
extern void ClearGameReqHold_1f5880(void);
extern void SetGameReqHold_1f5890(void);
extern void SetGameModePhase_1f59a0(s32);
extern s32  GetGameModePhase_1f59b0(void);
extern s32  GetLoaderMgr_1f59d0(void);
extern void GameReqQueueClear_1f59e0(void);
extern void GameReqQueueRemoveById_1f5a10(s32);
extern s32  GameReqQueuePeekHead_1f5a70(s32);
extern s32  GetCurrentScene_1f5be0(void);
extern s32  GetActionMgr_1fdb50(void);
extern s32  GetGameData_1fede0(void);
extern s32  GetMapMgr_201a90(void);
extern void BgmPlayTrackIfChangedMaybe_207880(s32, s32);
extern void EventPlayerAbort_2498b0(void *, s32);
extern void EventMenuWinInitAll_26b410(void);
extern void *GetCurEventPlayer_26b830(void);
extern void GameResumeFieldControl_27bca0(void);
extern void SetFieldControlActive_27bd30(s32);
extern s32  GetFieldControlActive_27bd40(void);
extern void TaskMoveBefore_27bf50(const char *, const char *);
extern void TaskStatePushAll_27c220(void);
extern void TaskStatePopAll_27c250(void);
extern void TaskSetEnabled_27c2a0(s32, const char *);
extern void TaskSetUpdateTasksPaused_287dd0(s32);
extern void SceneOverlayModeOff_288300(void);
extern void SceneScreenOverlayResetMaybe_2f1ea0(void);
extern void PauseSetAllowed_2f6640(s32);
extern void EventFireTriggers_3e2660(void *, s32);
extern void ActionPacketInitLoading_3e3a90(void *, s32);
extern void ActionPacketReset_3e3d00(void *);

struct Party;
struct Party { u8 padA60[0xA60]; s32 mA60; };

s32 LoadingModeUpdate_285450(void)
{
    u8 blk[0x30];
    struct Party *p;
    s32 scene;
    s32 snd;

    GetGameData_1fede0();
    scene = GetCurrentScene_1f5be0();
    GetMapMgr_201a90();
    GetActionMgr_1fdb50();
    GameReqQueueRemoveById_1f5a10(3);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
    case 0:
        D_004821EC = GetGameModePhase_1f59b0() == 0;
        TaskMoveBefore_27bf50(D_00460C48, D_00460CE8);
        SetGameReqHold_1f5890();
        TaskSetEnabled_27c2a0(0, D_004601D0);
        TaskSetEnabled_27c2a0(0, D_004605A8);
        TaskSetEnabled_27c2a0(0, D_004605C0);
        TaskSetEnabled_27c2a0(0, D_004605D8);
        TaskSetEnabled_27c2a0(0, D_0045FF98);
        TaskSetEnabled_27c2a0(0, D_0045FFB8);
        TaskSetEnabled_27c2a0(0, D_00460CB0);
        TaskSetEnabled_27c2a0(0, D_00460598);
        TaskSetEnabled_27c2a0(0, D_00460C58);
        TaskStatePushAll_27c220();
        if (D_004821EC != 0) {
            TaskSetUpdateTasksPaused_287dd0(1);
        }
        PauseSetAllowed_2f6640(0);
        D_004821F0 = 0xF;
        SceneOverlayModeOff_288300();
        ScreenFadeOutColor_1cf730(scene, D_004821F0, 0.0f, 0.0f, 0.0f);
        TaskSetEnabled_27c2a0(1, D_00460588);
        TaskSetEnabled_27c2a0(1, D_00460C48);
        snd = GetLoaderMgr_1f59d0();
        StreamSetChanVolumeFade_1cd960(snd, 0, D_004821F0, 0.0f);
        StreamSetChanVolumeFade_1cd960(snd, 1, D_004821F0, 0.0f);
        StreamSetChanVolumeFade_1cd960(snd, 2, D_004821F0, 0.0f);
        SetGameModePhase_1f59a0(0x64);
        return 0;
    case 100:
        D_004821F0 = D_004821F0 - 1;
        if (D_004821F0 >= 0) {
            return 0;
        }
        snd = GetLoaderMgr_1f59d0();
        LoaderPurgeAll_1cd240(snd);
        StreamPauseChan_1cd9f0(snd, 0);
        StreamPauseChan_1cd9f0(snd, 1);
        StreamPauseChan_1cd9f0(snd, 2);
        StreamStopChan_1cda60(snd, 0);
        StreamStopChan_1cda60(snd, 1);
        StreamStopChan_1cda60(snd, 2);
        BgmPlayTrackIfChangedMaybe_207880(0, 1);
        SceneScreenOverlayResetMaybe_2f1ea0();
        if (D_004821EC != 0) {
            SetGameModePhase_1f59a0(0xC8);
            return 0;
        }
        switch (GetGameModeAt_1f5830(1)) {
        case 11:
            p = GetCurEventPlayer_26b830();
            if (p != 0) {
                p->mA60 = p->mA60 | 8;
                EventPlayerAbort_2498b0(p, scene);
            }
            SetGameModePhase_1f59a0(0x65);
            break;
        case 12:
        case 13:
            GameResumeFieldControl_27bca0();
            SetGameModePhase_1f59a0(0x65);
            break;
        default:
            SetGameModePhase_1f59a0(0xC8);
            break;
        }
        return 1;
    case 101:
        if (GetFieldControlActive_27bd40() == 0) {
            return 0;
        }
        SetFieldControlActive_27bd30(0);
        SetGameModePhase_1f59a0(0xC8);
        return 1;
    case 200:
        SoundBankStopAll_1bad70(-1);
        SoundBankRelease_1bb6e0(4);
        SetGameModePhase_1f59a0(0xC9);
        return 0;
    case 201:
        TaskStatePopAll_27c250();
        TaskSetEnabled_27c2a0(1, D_00460588);
        TaskSetEnabled_27c2a0(1, D_00460C48);
        if (D_004821EC != 0) {
            SetGameExitRequest_1f57d0(1);
            return 0;
        }
        snd = GetLoaderMgr_1f59d0();
        StreamPauseChan_1cd9f0(snd, 0);
        StreamPauseChan_1cd9f0(snd, 1);
        StreamPauseChan_1cd9f0(snd, 2);
        StreamStopChan_1cda60(snd, 0);
        StreamStopChan_1cda60(snd, 1);
        StreamStopChan_1cda60(snd, 2);
        GameReqQueueClear_1f59e0();
        ClearGameReqHold_1f5880();
        EventMenuWinInitAll_26b410();
        ActionPacketReset_3e3d00(blk);
        ActionPacketInitLoading_3e3a90(blk, scene);
        EventFireTriggers_3e2660(blk, 0);
        if (GameReqQueuePeekHead_1f5a70(0) == -1) {
            SetGameExitRequest_1f57d0(1);
        }
        return 0;
    }
    return 0;
}
