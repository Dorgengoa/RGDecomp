#include "types.h"
#pragma opt_propagation off

extern s32 GetActionMgr_1fdb50(void);
extern s32 GetGameData_1fede0(void);
extern s32 CharaUseActionGaugeOnce_214010(s32, s32, s32);
extern s32 CharaGetActionTable_214cd0(s32);
extern s32 CharaCmdRunIfElseEvnt_22e480(s32, s32, u8 *, s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 ScriptArgGetInt_302d70(u8 *);
extern s32 ActorFindById_3eb870(s32, s32);

s32 CharaCmdUseAtg_22b840(s32 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_2;
    s32 var_19;

    if ((arg2 != 0) && (arg2 != 1) && (arg2 != 2) && (arg2 != 3)) {
        return 0;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (temp_2 == 0) {
        return 1;
    }
    if (CharaGetActionTable_214cd0(temp_2) == 0) {
        return 1;
    }
    var_19 = -1;
    if (arg2 > 0) {
        var_19 = ScriptArgGetInt_302d70(arg1);
    }
    return CharaCmdRunIfElseEvnt_22e480(*arg0, CharaUseActionGaugeOnce_214010(temp_2, ActorFindById_3eb870(GetGameData_1fede0(), *arg0), var_19), arg1 + 5, arg2 - 1);
}
