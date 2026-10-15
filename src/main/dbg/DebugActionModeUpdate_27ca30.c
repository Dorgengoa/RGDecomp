#include "types.h"

/* Phase driver of the SetGameModePhase_1f59a0 family (see
   memory/levers.d/main-phase-driver-family.md): one switch on the phase,
   every case ends with its OWN `return`, never a `break` to a shared tail.

   ★ Case order is the compare chain BACKWARDS -- retail tests 0xC8, 0x64,
   0, -1, so the source order is -1, 0, 100, 200, and the case BODIES appear
   in that same order in the listing, which is the independent check.
   ★ Both loop latches emit `slti $1, $16, 0x3C` into $at, so the source
   wrote the OR-EQUAL form `i <= 0x3B` -- [[at-compare-class]]: at a latch
   the only $at spellings are `<=`/`>=`. */

extern const char D_00460050[];
extern const char D_004600E8[];
extern const char D_00460108[];
extern const char D_00460148[];
extern const char D_00460158[];
extern const char D_00460168[];
extern const char D_00460188[];
extern const char D_00460198[];
extern const char D_004602C0[];
extern const char D_00460850[];
extern const char D_004609C0[];

extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
extern void ClearGameReqHold_1f5880(void);
extern void SetGameReqHold_1f5890(void);
extern void SetGameModePhase_1f59a0(s32);
extern s32  GetGameModePhase_1f59b0(void);
extern void GameReqQueueRemoveById_1f5a10(s32);
extern s32  GameReqQueuePeekHead_1f5a70(s32);
extern s32  GetCurrentScene_1f5be0(void);
extern s32  GetActionMgr_1fdb50(void);
extern s32  GetGameData_1fede0(void);
extern s32  GetMapMgr_201a90(void);
extern void ReturnZero_207f40(void);
extern void TaskStatePushAll_27c220(void);
extern void TaskStatePopAll_27c250(void);
extern void TaskSetEnabled_27c2a0(s32, const char *);
extern void TaskSetCharaTasksPaused_288130(s32);

s32 DebugActionModeUpdate_27ca30(void)
{
    s32 scene;
    s32 i;

    GetGameData_1fede0();
    scene = GetCurrentScene_1f5be0();
    GetMapMgr_201a90();
    GetActionMgr_1fdb50();
    GameReqQueueRemoveById_1f5a10(0x15);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
    case 0:
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        TaskSetCharaTasksPaused_288130(1);
        TaskSetEnabled_27c2a0(1, D_00460050);
        TaskSetEnabled_27c2a0(1, D_004609C0);
        TaskSetEnabled_27c2a0(1, D_004600E8);
        TaskSetEnabled_27c2a0(1, D_00460188);
        TaskSetEnabled_27c2a0(1, D_00460198);
        TaskSetEnabled_27c2a0(1, D_00460148);
        TaskSetEnabled_27c2a0(1, D_00460158);
        TaskSetEnabled_27c2a0(1, D_00460168);
        TaskSetEnabled_27c2a0(1, D_004602C0);
        TaskSetEnabled_27c2a0(1, D_00460108);
        TaskSetEnabled_27c2a0(0, D_00460850);
        i = 0;
        do {
            ObjRecSetFlags_1c3e00(scene, 1, i, 0x38);
            i = i + 1;
        } while (i <= 0x3B);
        SetGameModePhase_1f59a0(0x64);
        return 0;
    case 100:
        if (GameReqQueuePeekHead_1f5a70(0) == 0) {
            SetGameModePhase_1f59a0(0xC8);
            return 1;
        }
        ReturnZero_207f40();
        return 0;
    case 200:
        i = 0;
        do {
            ObjRecClearFlags_1c3dc0(scene, 1, i, 0x38);
            i = i + 1;
        } while (i <= 0x3B);
        TaskStatePopAll_27c250();
        ClearGameReqHold_1f5880();
        return 0;
    }
    return 0;
}
