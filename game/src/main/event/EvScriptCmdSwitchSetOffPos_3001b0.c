/* rgp:protos */
#define RGP_SELF_EvScriptCmdSwitchSetOffPos_3001b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma no_branch_likely on
#pragma no_branch_likely off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004E6720[0x400];

s32 EvScriptCmdSwitchSetOffPos_3001b0(s32 arg0, s32 arg1)
{
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_2;

    if (arg1 != 3) {
        return 0;
    }
    if (!(EventRecGetKey_2e5730(&(*(u8 *)D_004E6720)) != 0)) {
        return 1;
    }
    temp_2 = ((s32)EvSwitchObjGetStateRec_2f8410(&(*(u8 *)D_004E6720), 0));
    if (temp_2 == 0) {
        return 1;
    }
    temp_f21 = ScriptArgGetFloat_301a20(arg0);
    temp_f20 = ScriptArgGetFloat_301a20(arg0 + 8);
    EvSwitchRecSetPos_2f8830(temp_2, temp_f21, temp_f20, ScriptArgGetFloat_301a20(arg0 + 0x10));
    return 1;
}
