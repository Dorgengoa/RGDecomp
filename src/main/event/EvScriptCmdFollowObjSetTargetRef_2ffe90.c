#include "types.h"

s32 LookupNameValueNoCase_1cab50(s32, void *, s32);                      /* extern */
s32 TargetRefSetMapNode_2e6370(s32, s32, s32, f32);                   /* extern */
s32 TargetRefSetMapObj_2e6470(s32, s32, s32, f32);                   /* extern */
extern s32 TargetRefSetModelFrameFwdMaybe_2e65e0(s32, s32, s32, f32);
s32 EvFollowObjGetTargetRef_2f80d0(void *);                              /* extern */
s32 ScriptArgGetAreaId_3019b0(s32);                              /* extern */
s32 ScriptArgGetStr_301a00(s32);                              /* extern */
s32 ScriptArgGetInt_301a60(s32);                              /* extern */
s32 EventStrDup_301aa0(s32);                              /* extern */
extern u8 D_00451E10[0x400];
extern u8 D_004E6880[0x400];

s32 EvScriptCmdFollowObjSetTargetRef_2ffe90(s32 arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_17;
    s32 temp_17_2;
    s32 temp_17_3;
    s32 temp_2;

    if (arg1 != 3) {
        return 0;
    }
    temp_16 = EvFollowObjGetTargetRef_2f80d0(&(*(s32 *)D_004E6880));
    temp_2 = LookupNameValueNoCase_1cab50(ScriptArgGetStr_301a00(arg0), &(*(s32 *)D_00451E10), 0);
    switch (temp_2) {                               /* irregular */
    case 5:
        temp_17_3 = ScriptArgGetInt_301a60(arg0 + 8);
        TargetRefSetModelFrameFwdMaybe_2e65e0(temp_16, temp_17_3, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10)), 0.0f);
        break;
    case 7:
        temp_17_2 = ScriptArgGetAreaId_3019b0(arg0 + 8);
        TargetRefSetMapObj_2e6470(temp_16, temp_17_2, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10)), 0.0f);
        break;
    case 9:
        temp_17 = ScriptArgGetInt_301a60(arg0 + 8);
        TargetRefSetMapNode_2e6370(temp_16, temp_17, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10)), 0.0f);
        break;
    }
    return 1;
}
