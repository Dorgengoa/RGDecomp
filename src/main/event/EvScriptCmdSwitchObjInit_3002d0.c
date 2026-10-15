#include "types.h"

extern void EvSwitchObjInitByName_2f85b0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
extern s32 ScriptArgGetAreaId_3019b0(s32 arg0);
extern s32 ScriptArgGetStr_301a00(s32 arg0);
extern s32 EventStrDup_301aa0(s32 arg0);
extern void EvScriptTemplatesReset_301c20(void);
extern u8 D_004E6720[0x400];

s32 EvScriptCmdSwitchObjInit_3002d0(s32 arg0, s32 arg1)
{
    s32 temp_20;
    s32 temp_19;
    s32 temp_19_2;
    s32 temp_16;
    s32 temp_18;
    s32 temp_17;
    s32 temp_18_2;
    s32 temp_17_2;
    s32 temp_16_2;

    EvScriptTemplatesReset_301c20();
    if ((arg1 != 5) && (arg1 != 6)) {
        return 0;
    }
    switch (arg1) {
    case 5:
        temp_19_2 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0));
        temp_18_2 = ScriptArgGetAreaId_3019b0(arg0 + 8);
        temp_17_2 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10));
        temp_16_2 = ScriptArgGetAreaId_3019b0(arg0 + 0x18);
        EvSwitchObjInitByName_2f85b0(&(*(u8 *)D_004E6720), temp_19_2, 0, 0, temp_18_2, temp_17_2, temp_16_2, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x20)));
        break;
    case 6:
        temp_20 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0));
        temp_19 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x28));
        temp_18 = ScriptArgGetAreaId_3019b0(arg0 + 8);
        temp_17 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10));
        temp_16 = ScriptArgGetAreaId_3019b0(arg0 + 0x18);
        EvSwitchObjInitByName_2f85b0(&(*(u8 *)D_004E6720), temp_20, 0, temp_19, temp_18, temp_17, temp_16, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x20)));
        break;
    }
    return 1;
}
