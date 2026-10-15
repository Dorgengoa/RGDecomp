#include "types.h"


extern "C" {
s32 DrawEnvGetVsyncInterval_144130(s32);
s32 GetDrawCtx_15de80();
void DbgPrintf_15e780(u8 *);
s32 PadIsTriggered_1839f0(u8 *, s32);
s32 PadIsHeld_183a20(u8 *, s32);
void PadUpdateVibration_184250(u8 *, s32);
void PadUpdate_1843a0(u8 *);
s32 PadIsAnalogMode_184960(u8 *);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
void SoundSetMasterVolume_1bb420(f32);
s32 GetGameMode_1f59c0();
void GetLoaderMgr_1f59d0();
s32 GameReqQueuePeekHead_1f5a70(s32);
void GameReqQueuePushFront_1f5ab0(s32, s32);
s32 GetCurrentScene_1f5be0();
u8 *GetGameData_1fede0();
void GoTitleMenuClose_202fd0();
void GoTitleMenuOpen_203030();
void SceneSoundUpdate_207a50();
s32 SceneSoundGetSlot0HandleCur_207df0();
s32 GetStreamMgr_207ea0();
s32 ReturnZero_207f40();
s32 ReturnZero_207fe0();
s32 EvtCurAbort_26a8b0(s32);
s32 EvtCurTrySkip_26a8f0(s32);
void TaskSetEnabled_27c2a0(s32, u8 *);
s32 IsPad2Enabled_2882c0();
void PauseSetRequest_2f6620(s32);
s32 PauseGetRequest_2f6630();
s32 PauseIsAllowed_2f6650();
s32 GetPauseStep_2f6660();
void SceneSoundMutePop_2f6670();
void SceneSoundMutePush_2f6710();
s32 SaveIsBusy_376b00();
s32 DiscStatusMessagePoll_39ee00(s32);
void StateFlagSet_3ccb70(s32, s32, s32, s32);
void SoundStreamSlotThreadResumeThunk_1bd660(s32);
void SoundStreamSlotThreadPauseThunk_1bd670(s32);
s32 GoTitleMenuUpdateThunk_39bf70();
extern u8 D_00461BF0[];
extern u8 D_00461C20[];
extern u8 D_00461C40[];
extern u8 D_00461C60[];
extern u8 D_00461C90[];
extern s32 D_0048276C;
extern u32 D_00482770;
extern u8 D_004B2570[];
extern u8 D_004B27E0[];
void PauseStepUpdate_2f5fb0(void);
}

void PauseStepUpdate_2f5fb0(void) {
    s32 flag; bool keep; bool ok; bool fin; s32 v; s32 h; s32 r; s32 i;

    flag = (u8)PauseGetRequest_2f6630();
    PauseSetRequest_2f6620(0);
    keep = true;
    switch (GetPauseStep_2f6660()) {
    case 0:
        v = GetGameMode_1f59c0();
        if (v == 3 || v == 4 || v == 2 || v == 1 || v == -1) break;
        if (flag == 0) break;
        if (ReturnZero_207f40() != 0) break;
        if (GameReqQueuePeekHead_1f5a70(0) == 2) break;
        if (PauseIsAllowed_2f6650() != 0 || (PauseIsAllowed_2f6650() == 0 && D_00482770 - 4 < 3)) {
            DbgPrintf_15e780(D_00461BF0);
            D_0048276C = 1;
            TaskSetEnabled_27c2a0(1, D_00461C20);
            h = GetStreamMgr_207ea0();
            if (SaveIsBusy_376b00() == 0) {
                SoundStreamSlotThreadPauseThunk_1bd670(h);
            }
        }
        break;
    case 1:
        DbgPrintf_15e780(D_00461C40);
        D_0048276C = 2;
        if (SaveIsBusy_376b00() == 0) {
            SceneSoundMutePush_2f6710();
            SceneSoundUpdate_207a50();
            SoundSetMasterVolume_1bb420(0.0f);
        }
        break;
    case 2:
        if (ReturnZero_207f40() != 0) break;
        ok = false;
        fin = false;
        switch (D_00482770) {
        case 1:
            if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0 || (IsPad2Enabled_2882c0() != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x10) != 0)) {
                if (EvtCurTrySkip_26a8f0(GetCurrentScene_1f5be0()) != 0) {
                    StateFlagSet_3ccb70(*(s32 *)(GetGameData_1fede0() + 0x10), 0x143, 1, 1);
                    SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
                    ok = true;
                } else {
                    SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 6, 0, 1.0f);
                }
            }
            break;
        case 4:
            ok = PadIsAnalogMode_184960(D_004B2570) != 0 && PadIsTriggered_1839f0(D_004B2570, 0x40) != 0;
            fin = true;
            break;
        case 5:
            ok = PadIsAnalogMode_184960(D_004B27E0) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x40) != 0;
            fin = true;
            break;
        case 6:
            ok = !(DiscStatusMessagePoll_39ee00(0) != 0);
            fin = true;
            break;
        }
        keep = !ok;
        if (fin) break;
        if (keep && ReturnZero_207fe0() != 0 && PadIsTriggered_1839f0(D_004B2570, 0x10) != 0 && PadIsHeld_183a20(D_004B2570, 8) != 0 &&
            PadIsHeld_183a20(D_004B2570, 2) != 0 && EvtCurAbort_26a8b0(GetCurrentScene_1f5be0()) != 0) {
            StateFlagSet_3ccb70(*(s32 *)(GetGameData_1fede0() + 0x10), 0x143, 1, 1);
            SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
            keep = false;
        }
        if (keep && (PadIsTriggered_1839f0(D_004B2570, 0x800) != 0 || (IsPad2Enabled_2882c0() != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x800) != 0))) {
            GetLoaderMgr_1f59d0();
            keep = false;
        }
        if (keep && (PadIsTriggered_1839f0(D_004B2570, 0x80) != 0 || (IsPad2Enabled_2882c0() != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x80) != 0)) && D_00482770 < 2) {
            DbgPrintf_15e780(D_00461C60);
            GoTitleMenuOpen_203030();
            D_0048276C = 3;
        }
        break;
    case 3:
        r = 0;
        for (i = 0; i < DrawEnvGetVsyncInterval_144130(GetDrawCtx_15de80()); i++) {
            r = GoTitleMenuUpdateThunk_39bf70();
            if (r > 0) break;
        }
        switch (r) {
        case 1:
            GoTitleMenuClose_202fd0();
            GameReqQueuePushFront_1f5ab0(3, 0);
            keep = false;
            break;
        case 2:
            DbgPrintf_15e780(D_00461C40);
            GoTitleMenuClose_202fd0();
            D_0048276C = 2;
            break;
        }
        break;
    case 4:
        keep = false;
        break;
    }
    if (keep) return;
    DbgPrintf_15e780(D_00461C90);
    SceneSoundMutePop_2f6670();
    SoundSetMasterVolume_1bb420(1.0f);
    D_0048276C = 0;
    D_00482770 = 0;
    SoundStreamSlotThreadResumeThunk_1bd660(GetStreamMgr_207ea0());
    TaskSetEnabled_27c2a0(0, D_00461C20);
    PadUpdateVibration_184250(D_004B2570, 0);
    PadUpdate_1843a0(D_004B2570);
    PadUpdateVibration_184250(D_004B27E0, 0);
    PadUpdate_1843a0(D_004B27E0);
}
