#include "types.h"

extern void EffectInstanceSetPos_2dd570(s32, void *);
extern void ScriptSlotsToVec4_334810(void *, s32);
extern s32 D_004826E0;

s32 ScriptCmdEffectSetPos_3327c0(s32 arg0, s32 arg1) {
    u8 sp20[0x10];
    s32 var_16;

    if (arg1 != 4 && arg1 != 3) {
        return 0;
    }
    var_16 = 0;
    switch (arg1) {
    case 3:
    case 4:
        var_16 = D_004826E0;
        break;
    }
    if (var_16 == 0) {
        return 0;
    }
    ScriptSlotsToVec4_334810(sp20, arg0);
    EffectInstanceSetPos_2dd570(var_16, sp20);
    return 1;
}
