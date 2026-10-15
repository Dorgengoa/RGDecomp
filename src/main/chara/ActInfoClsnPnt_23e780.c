#include "types.h"

extern void ActInfoClsnPntInit_230dd0(s32, f32, s32, f32, s32);
extern s32 ScriptArgGetStr_23fba0(s32);
extern f32 ScriptArgGetFloat_23fbc0(s32);
extern s32 ScriptArgGetInt_23fc00(s32);
extern s32 StrDupArena_23fc40(s32);
extern s32 D_00481E90;
extern s32 D_00481E94;

s32 ActInfoClsnPnt_23e780(s32 arg0, s32 arg1)
{
    f32 temp_f20;
    f32 var_f21;
    s32 temp_19;
    s32 var_18;

    if ((arg1 != 2) && (arg1 != 3) && (arg1 != 4)) {
        return 0;
    }
    if ((D_00481E90 == 0) || (D_00481E94 >= 0x40)) return 1;
    var_18 = 0;
    var_f21 = 0.0f;
    temp_19 = D_00481E90 + (D_00481E94 * 0x10);
    if (arg1 > 2) {
        var_18 = ScriptArgGetInt_23fc00(arg0 + 0x10) != 0;
    }
    if (arg1 > 3) {
        var_f21 = ScriptArgGetFloat_23fbc0(arg0 + 0x18);
    }
    temp_f20 = ScriptArgGetFloat_23fbc0(arg0);
    ActInfoClsnPntInit_230dd0(temp_19, var_f21, StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 8)), temp_f20, var_18);
    D_00481E94 += 1;
    return 1;
    return 1;
}
