#include "types.h"
#pragma optimization_level 3
extern void ClsnInfoSetChain_228170(s32, s32, s32);
extern s32 ScriptArgGetInt_23fc00(s32);
extern s32 D_00481EB0;
extern s32 D_00481EB4;

s32 ClsnInfoChain_23bba0(s32 arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_17;

    if (arg1 != 2) {
        return 0;
    }
    if ((D_00481EB0 == 0) || (D_00481EB4 <= 0)) {
        return 1;
    }
    temp_17 = (D_00481EB0 + (D_00481EB4 << 5)) - 0x20;
    temp_16 = ScriptArgGetInt_23fc00(arg0);
    ClsnInfoSetChain_228170(temp_17 + 4, temp_16, ScriptArgGetInt_23fc00(arg0 + 8));
    return 1;
}
