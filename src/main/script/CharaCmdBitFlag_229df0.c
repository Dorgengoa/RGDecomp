#include "types.h"

s32 GetActionMgr_1fdb50();                                 /* extern */
u8 *GetGameData_1fede0();                               /* extern */
s32 CharaGetActionTable_214cd0(s32);                              /* extern */
s32 CharaCmdRunIfElseEvnt_22e480(s32, s32, u8 *, s32);               /* extern */
s32 ActionMgrFindById_233b50(s32, s32);                         /* extern */
s32 ScriptArgGetStr_302cb0(u8 *);                              /* extern */
s32 ScriptArgGetInt_302d70(u8 *);                              /* extern */
s32 ScriptArgGetTag_302df0(u8 *);                              /* extern */
s32 StateFlagTestByName_3ccd10(s32, s32);                         /* extern */
s32 StateFlagTest_3ccd70(s32, s32);                         /* extern */

s32 CharaCmdBitFlag_229df0(s32 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_2;
    s32 var_2;
    u8 *temp_16;

    if (arg2 < 0) {
        return 0;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (temp_2 == 0) {
        return 1;
    }
    if (CharaGetActionTable_214cd0(temp_2) == 0) {
        return 1;
    }
    temp_16 = GetGameData_1fede0();
    if (ScriptArgGetTag_302df0(arg1) == 2) {
        var_2 = StateFlagTestByName_3ccd10((*(s32 *)((u8 *)temp_16 + 0x10)), ScriptArgGetStr_302cb0(arg1)) & 0xFF;
    } else {
        var_2 = StateFlagTest_3ccd70((*(s32 *)((u8 *)temp_16 + 0x10)), ScriptArgGetInt_302d70(arg1)) & 0xFF;
    }
    return CharaCmdRunIfElseEvnt_22e480(*arg0, var_2, arg1 + 5, arg2 - 1);
    return 1;
}
