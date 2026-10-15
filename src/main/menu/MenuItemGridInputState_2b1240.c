#include "types.h"

extern s32 PadIsHeld_183a20();
extern s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern void UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32 D_0048235C;
extern s32 D_00482364;
extern u8 *D_00482374;
extern u8 D_004B2570[0x40];

s32 MenuItemGridInputState_2b1240(void)
{
    s8 var_16;
    s32 temp_17;

    temp_17 = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 6, 0);
    UiEntryListGetCurrentData_28ec60(D_00482364);
    var_16 = 0;
    if (temp_17 == 1) {
        var_16 = 1;
    } else if (temp_17 == 2) {
        D_00482374[0x1C] = 0;
        StateMachineSetState_28ede0(D_0048235C, 0xF, 1);
    } else if (temp_17 == 6) {
        u8 *p = D_004B2570;
        if ((PadIsHeld_183a20(p, 0x10) != 0) || (PadIsHeld_183a20(p, 0x80) != 0)) {
            var_16 = 1;
        }
    }
    if ((s32)var_16) {
        StateMachineSetState_28ede0(D_0048235C, 0x10, 0);
    }
    return 1;
}
