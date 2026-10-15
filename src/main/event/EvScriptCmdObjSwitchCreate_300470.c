#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

#pragma opt_rebuildconditionals off

extern s32 GetEventObjMgr_2d1960(void);
extern void EventObjMgrCreateObjSwitch_2ea0d0(s32 arg0, s32 arg1, s32 arg2, void *arg3);
extern void EvObjSwitchCtorWithName_2f8b50(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 ScriptArgGetAreaId_3019b0(s32 arg0);
extern s32 ScriptArgGetStr_301a00(s32 arg0);
extern void EvScriptTemplatesReset_301c20(void);
extern s32 D_0047F0C0;
extern s32 D_0047F0C4;

s32 EvScriptCmdObjSwitchCreate_300470(s32 arg0, s32 arg1)
{
    void * arg_h0;

    s32 var_18;
    s32 temp_16;
    s32 temp_17;
    u8 sp40[0xe8];

    EvScriptTemplatesReset_301c20();
    if ((arg1 != 3) && (arg1 != 4)) {
        return 0;
    }
    if (arg1 == 4) {
        var_18 = ScriptArgGetStr_301a00(arg0 + 0x18);
    } else {
        var_18 = 0;
    }
    temp_17 = ScriptArgGetStr_301a00(arg0);
    temp_16 = ScriptArgGetAreaId_3019b0(arg0 + 8);
    arg_h0 = sp40;
    EvObjSwitchCtorWithName_2f8b50(arg_h0, temp_17, 0, var_18, temp_16, ScriptArgGetStr_301a00(arg0 + 0x10));
    EventObjMgrCreateObjSwitch_2ea0d0(GetEventObjMgr_2d1960(), D_0047F0C0, D_0047F0C4, sp40);
    return 1;
}
