#include "types.h"

extern s32 PadIsTriggered_1839f0(void *, s32);
extern s32 PadIsHeld_183a20(void *, s32);
extern void SetGameExitRequest_1f57d0(s32);
extern s32 GetGameExitRequest_1f57e0(void);
extern void GameFrameUpdate_27c4c0(void);
extern s32 SaveIsBusy_376b00(void);

extern char D_004B2570[32];

s32 GameFrameStep_1f5cf0(void) {
    s32 var_2;

    if (PadIsHeld_183a20(D_004B2570, 0x100) != 0 && PadIsTriggered_1839f0(D_004B2570, 0x800) != 0) {
        SaveIsBusy_376b00();
    }
    SetGameExitRequest_1f57d0(0);
    GameFrameUpdate_27c4c0();
    var_2 = GetGameExitRequest_1f57e0() != 0;
    if (var_2 != 0) {
        var_2 = !(SaveIsBusy_376b00() != 0);
    }
    return var_2 & 0xFF;
}
