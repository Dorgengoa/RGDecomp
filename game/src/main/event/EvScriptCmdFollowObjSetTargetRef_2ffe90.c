/* rgp:protos */
#define RGP_SELF_EvScriptCmdFollowObjSetTargetRef_2ffe90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                      /* extern */
/*rgp*/                   /* extern */
/*rgp*/                   /* extern */
/*rgp*/
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
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
    temp_16 = ((s32)EvFollowObjGetTargetRef_2f80d0(&(*(s32 *)D_004E6880)));
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
