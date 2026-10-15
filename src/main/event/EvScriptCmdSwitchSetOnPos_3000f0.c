#include "types.h"
#pragma no_branch_likely on
#pragma no_branch_likely off

extern s32 EventRecGetKey_2e5730(void *);
extern s32 EvSwitchObjGetStateRec_2f8410(void *, s32);
extern void EvSwitchRecSetPos_2f8830(s32, f32, f32, f32);
extern f32 ScriptArgGetFloat_301a20(s32);
extern u8 D_004E6720[0x400];

s32 EvScriptCmdSwitchSetOnPos_3000f0(s32 arg0, s32 arg1) {
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_2;

    if (arg1 != 3) {
        return 0;
    }
    if (!(EventRecGetKey_2e5730(&(*(u8 *)D_004E6720)) != 0)) {
        return 1;
    }
    temp_2 = EvSwitchObjGetStateRec_2f8410(&(*(u8 *)D_004E6720), 1);
    if (temp_2 == 0) {
        return 1;
    }
    temp_f21 = ScriptArgGetFloat_301a20(arg0);
    temp_f20 = ScriptArgGetFloat_301a20(arg0 + 8);
    EvSwitchRecSetPos_2f8830(temp_2, temp_f21, temp_f20, ScriptArgGetFloat_301a20(arg0 + 0x10));
    return 1;
}
