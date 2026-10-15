#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern void CharaRequestAction_212410(s32, s32, f32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern f32 ScriptArgGetFloat_302cf0(s32);

s32 CharaCmdActionPlay_22ce30(s32 *arg0, s32 arg1, s32 arg2) {
    f32 var_f20;
    s32 temp_2;

    if ((arg2 != 1) && (arg2 != 2)) {
        return 0;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (temp_2 == 0) {
        return 1;
    }
    var_f20 = 1.0f;
    if (arg2 > 1) {
        var_f20 = ScriptArgGetFloat_302cf0(arg1 + 5);
    }
    CharaRequestAction_212410(temp_2, ScriptArgGetStr_302cb0(arg1), var_f20);
    return 1;
}
