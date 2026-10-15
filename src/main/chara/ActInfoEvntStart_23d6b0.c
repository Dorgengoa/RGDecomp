#include "types.h"
#pragma optimization_level 3
extern void ActInfoEvntInit_22f340(s32, s32, s32, s32);
extern s32 ScriptArgGetStr_23fba0(s32);
extern s32 StrDupArena_23fc40(s32);
extern s32 D_00481E78;
extern s32 D_00481E7C;
extern s32 D_004BCE64[];
extern s16 D_004BCE8E[];

s32 ActInfoEvntStart_23d6b0(s32 arg0, s32 arg1)
{
    s32 temp_16;

    if (arg1 != 1) {
        return 0;
    }
    if (D_004BCE64[0] == 0 || D_004BCE8E[0] >= 0x40) {
        return 1;
    }
    temp_16 = D_004BCE64[0] + (D_004BCE8E[0] * 0xC);
    ActInfoEvntInit_22f340(temp_16, StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0)), D_00481E78 + (D_00481E7C * 0xC), 0);
    return 1;
}
