#include "types.h"
#pragma peephole off

extern s32 GetActionMgr_1fdb50(void);
extern s32 CharaGetActionTable_214cd0(s32 arg0);
extern void CharaTrailSetupByName_21f6c0(s32, s32, s32, f32, f32, f32, f32, s32, s32, s32);
extern s32 ActionMgrFindById_233b50(s32 arg0, s32 arg1);
extern s32 ScriptArgGetStr_302cb0(s32 arg0);
extern f32 ScriptArgGetFloat_302cf0(s32 arg0);
extern s32 ScriptArgGetInt_302d70(s32 arg0);

s32 ScriptCmdCharaTrailSetup_22be30(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_2;
    s32 temp_2_2;
    f32 temp_f23;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f20;
    s32 temp_20;
    s32 temp_19;
    s32 temp_17;

    if (arg2 <= 4) {
        return 0;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (temp_2 == 0) {
        return 1;
    }
    temp_2_2 = CharaGetActionTable_214cd0(temp_2);
    if (temp_2_2 == 0) {
        return 1;
    }
    temp_f23 = ScriptArgGetFloat_302cf0(arg1 + 0x14);
    if (arg2 > 5) {
        var_f0 = ScriptArgGetFloat_302cf0(arg1 + 0x19);
    } else {
        var_f0 = 1.0f;
    }
    if (arg2 > 6) {
        var_f0_2 = ScriptArgGetFloat_302cf0(arg1 + 0x1E);
    } else {
        var_f0_2 = temp_f23;
    }
    if (arg2 > 7) {
        var_f20 = ScriptArgGetFloat_302cf0(arg1 + 0x23);
    } else {
        var_f20 = 5.0f;
    }
    temp_20 = ScriptArgGetStr_302cb0(arg1 + 0xF);
    temp_19 = ScriptArgGetInt_302d70(arg1 + 0xA);
    temp_17 = ScriptArgGetInt_302d70(arg1);
    CharaTrailSetupByName_21f6c0(temp_2_2, *arg0, temp_20, var_f0, temp_f23, var_f0_2, var_f20, temp_19, temp_17, ScriptArgGetStr_302cb0(arg1 + 5));
    return 1;
}
