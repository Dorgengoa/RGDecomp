#include "types.h"
#pragma opt_dead_assignments off

extern void ActInfoAliasPairInit_22f0f0(s32, s32, s32);
extern s32 ScriptArgGetStr_23fba0(s32);
extern s32 StrDupArena_23fc40(s32);
extern s32 D_00481E80;
extern s32 D_00481E84;

s32 ActInfoAliasName_23d170(s32 arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_17;

    if (arg1 != 2) {
        return 0;
    }
    if ((D_00481E80 == 0) || (D_00481E84 >= 0x100)) return 1;
    temp_17 = D_00481E80 + (D_00481E84 * 8);
    temp_16 = StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0));
    ActInfoAliasPairInit_22f0f0(temp_17, temp_16, StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 8)));
    D_00481E84 += 1;
    return 1;
    return 1;
}
