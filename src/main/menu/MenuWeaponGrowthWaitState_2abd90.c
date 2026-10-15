#include "types.h"

extern void UiSelFrameAnimStep_28d820(void *, s32);
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void MenuWeaponCombineAnimTickMaybe_361cd0(s32);
extern void MenuWeaponCombineAutoHideTick_362700(s32);

extern s32 D_0048235C;
extern s32 D_00482364;
extern s32 D_00482384;
extern u8 D_004823CC;
extern char D_004B2570[32];
extern char D_004DB430[32];

s32 MenuWeaponGrowthWaitState_2abd90(void) {
    s32 temp_16;

    if ((u32)(MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0) - 1) < 2U) {
        StateMachineSetState_28ede0(D_0048235C, 0x1F, 0);
    }
    if (D_004823CC != 0) {
        temp_16 = D_00482384;
        MenuWeaponCombineAutoHideTick_362700(temp_16);
        MenuWeaponCombineAnimTickMaybe_361cd0(temp_16);
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
