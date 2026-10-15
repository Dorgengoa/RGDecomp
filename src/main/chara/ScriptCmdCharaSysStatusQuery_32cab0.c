#include "types.h"
#pragma opt_propagation off
u8 *GetGameData_1fede0();
s32 ScriptSlotStoreFloatRef_3347d0(s32, f32);
s32 ScriptSlotStoreIntRef_3347f0(s32, u8);
s32 ScriptSlotGetInt_3348b0(s32);
s32 CharaSysStatusFind_3a16f0(s32, s32, s32);
f32 StatusEntryGetTime_3a60f0(s32);
s32 StatusEntryHasFlag2Maybe_3a6130(s32);
s32 StatusEntryIsExpired_3a6160(s32);

s32 ScriptCmdCharaSysStatusQuery_32cab0(s32 arg0, s32 arg1)
{
    f32 f;
    u8 b;
    s32 t;
    u8 *m;

    if (arg1 < 2) {
        return 1;
    }
    m = GetGameData_1fede0();
    t = CharaSysStatusFind_3a16f0(*(s32 *)(m + 0x20), ScriptSlotGetInt_3348b0(arg0), 0);
    f = 0.0f;
    b = 0;
    if (t != 0) {
        f = StatusEntryGetTime_3a60f0(t);
        b = StatusEntryIsExpired_3a6160(t) != 0 || StatusEntryHasFlag2Maybe_3a6130(t) != 0;
    }
    if (arg1 >= 2) {
        ScriptSlotStoreFloatRef_3347d0(arg0 + 8, f);
    }
    if (arg1 >= 3) {
        ScriptSlotStoreIntRef_3347f0(arg0 + 0x10, b);
    }
    return 1;
}
