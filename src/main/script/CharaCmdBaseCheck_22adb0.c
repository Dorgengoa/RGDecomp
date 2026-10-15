#include "types.h"

s32 GetActionMgr_1fdb50();                                 /* extern */
s32 CharaGetActScopeId_214a70(s32);                              /* extern */
s32 ActCfgTableGetScopeId_223d00(s32);                              /* extern */
s32 CharaCmdRunIfElseEvnt_22e480(s32, s32, u8 *, s32);               /* extern */
s32 ActionMgrFindById_233b50(s32, s32);                         /* extern */
s32 ActionMgrFindTableByScopeId_233c20(s32, s32);                         /* extern */
s32 ScriptArgGetInt_302d70(u8 *);                              /* extern */

s32 CharaCmdBaseCheck_22adb0(s32 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_19;
    s32 temp_19_2;
    s32 temp_2;
    s32 temp_2_2;

    if ((arg2 != 1) && (arg2 != 2) && (arg2 != 3)) {
        return 1;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (temp_2 == 0) {
        return 1;
    }
    temp_19_2 = GetActionMgr_1fdb50();
    temp_2_2 = ActionMgrFindTableByScopeId_233c20(temp_19_2, CharaGetActScopeId_214a70(temp_2));
    if (temp_2_2 == 0) {
        return 1;
    }
    temp_19 = ActCfgTableGetScopeId_223d00(temp_2_2);
    return CharaCmdRunIfElseEvnt_22e480(*arg0, temp_19 == ScriptArgGetInt_302d70(arg1), arg1 + 5, arg2 - 1);
    return 1;
}
