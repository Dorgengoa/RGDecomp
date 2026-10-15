/* PARK 1/3: length-wrong (50w vs retail 52w). m2c draft was fully typed already; retail keeps a duplicated per-branch epilogue (b + inline return value) that -O4 here merges away. */
#include "types.h"

s32 CharaWeaponSeIdRemap_1fd430(s32, s32);
s32 GetActionMgr_1fdb50(void);
void CharaPlayLoopSe_213c10(s32, s32, f32);
s32 ActionMgrFindById_233b50(s32, s32);
f32 ScriptArgGetFloat_302cf0(s32);
s32 ScriptArgGetInt_302d70(s32);

s32 CharaCmdLoopSePlay_22a7b0(s32 *arg0, s32 arg1, s32 arg2) {
    f32 var_f0;
    s32 temp_2;
    s32 temp_16;

    if ((arg2 != 1) && (arg2 != 2)) {
        return 1;
    }
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (temp_2 == 0) {
        return 1;
    }
    temp_16 = CharaWeaponSeIdRemap_1fd430(*arg0, ScriptArgGetInt_302d70(arg1));
    if (arg2 >= 2) {
        var_f0 = ScriptArgGetFloat_302cf0(arg1 + 5);
    } else {
        var_f0 = 1.0f;
    }
    CharaPlayLoopSe_213c10(temp_2, temp_16, var_f0);
    return 1;
}
