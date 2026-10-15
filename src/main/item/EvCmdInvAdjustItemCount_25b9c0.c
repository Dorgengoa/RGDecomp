#include "types.h"

u8 *GetGameData_1fede0();
s32 ScriptGetInt_26a2a0(s32);
s32 InvConsumeById_3c46b0(s32, s32, s32, s32, s32);
s32 InvAddItemRepeat_3c47b0(s32, s32, s32, s32);

s32 EvCmdInvAdjustItemCount_25b9c0(s64 *arg0, s32 arg1) {
    u8 *g;
    s32 a;
    s32 n;
    s32 b;
    s32 i;

    g = GetGameData_1fede0();
    a = ScriptGetInt_26a2a0((s32)arg0++);
    n = ScriptGetInt_26a2a0((s32)arg0++);
    if (n > 0) {
        b = 0;
        if (arg1 >= 3) {
            b = ScriptGetInt_26a2a0((s32)arg0);
        }
        for (i = 0; i < n; i++) {
            InvAddItemRepeat_3c47b0(*(s32 *)(g + 0x18), a, b, 1);
        }
    } else if (n < 0) {
        b = 0;
        if (arg1 >= 3) {
            b = ScriptGetInt_26a2a0((s32)arg0);
        }
        InvConsumeById_3c46b0(*(s32 *)(g + 0x18), a, -n, b, 1);
    }
    return 1;
}
