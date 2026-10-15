#include "types.h"

extern void EffectInstanceSetParamInt_2dd6a0(s32 arg0, s32 arg1, s32 arg2);
extern s32 ScriptSlotGetInt_3348b0(s32 arg0);
extern s32 D_004826E0;

s32 ScriptCmdEffectSetParamInt_332fa0(s64 *arg0, s32 arg1)
{
    s32 temp_16;
    s32 var_17;

    if ((arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    var_17 = 0;
    switch (arg1) {
    case 2:
    case 3:
        var_17 = D_004826E0;
        break;
    }
    if (var_17 == 0) {
        return 0;
    }
    temp_16 = ScriptSlotGetInt_3348b0((s32)arg0++);
    EffectInstanceSetParamInt_2dd6a0(var_17, ScriptSlotGetInt_3348b0((s32)arg0), temp_16);
    return 1;
    return 0;
}
