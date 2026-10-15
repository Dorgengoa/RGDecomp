#include "types.h"
#pragma opt_propagation off

s32 PadIsHeld_183a20();
s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
s32 UiEntryListSelectByTag_28ea90(s32, s32, s32);
s32 UiEntryListGetCurrentData_28ec60(s32);
s32 StateMachineSetState_28ede0(s32, s32, s32);
extern s32 D_0048470C;
extern s32 D_00484720;
extern u8 *D_00484740;
extern u8 D_004B2570[0x100];

s32 TransMenuItemMoveTargetState_37dfe0(s32 pd0, s32 arg1) {
    s32 temp_17;
    s64 var_16;
    u8 *q;
    s32 k;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00484720, 0xB, 0);
    }
    temp_17 = MenuGridCursorInput_28e170(D_00484720, D_004B2570, 6, 0);
    UiEntryListGetCurrentData_28ec60(D_00484720);
    var_16 = 0;
    k = 1;
    if (temp_17 == k) {
        var_16 = (s8)k;
    } else if (temp_17 == 2) {
        D_00484740[0x1C] = 0;
        StateMachineSetState_28ede0(D_0048470C, 0x38, k);
    } else if (temp_17 == 6) {
        q = D_004B2570;
        if (PadIsHeld_183a20(q, 0x10, k) != 0 || PadIsHeld_183a20(q, 0x80) != 0) {
            var_16 = 1;
        }
    }
    if (var_16 != 0) {
        StateMachineSetState_28ede0(D_0048470C, 0x39, 0);
    }
    return 1;
}
