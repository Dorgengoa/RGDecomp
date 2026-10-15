#include "types.h"

s32 GetActionMgr_1fdb50();                                 /* extern */
void CharaJudgeObjCreate_213cf0(s32, s32, s32, f32);              /* extern */
s32 ActionMgrFindById_233b50(s32, s32);                         /* extern */
s32 ScriptArgGetStr_302cb0(s32);                              /* extern */
f32 ScriptArgGetFloat_302cf0(s32);                              /* extern */

s32 CharaCmdJoCreate_22b710(s32 *arg0, s32 arg1, s32 arg2) {
    f32 var_f20;
    s32 temp_2;
    s32 temp_16;

    if ((arg2 != 2) && (arg2 != 3)) {
        return 0;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (temp_2 == 0) {
        return 1;
    }
    var_f20 = 0.0f;
    if (arg2 > 2) {
        var_f20 = ScriptArgGetFloat_302cf0(arg1 + 0xA);
    }
    temp_16 = ScriptArgGetStr_302cb0(arg1);
    CharaJudgeObjCreate_213cf0(temp_2, temp_16, ScriptArgGetStr_302cb0(arg1 + 5), var_f20);
    return 1;
}
