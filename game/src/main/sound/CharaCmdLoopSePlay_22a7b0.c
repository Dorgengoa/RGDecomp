/* rgp:protos */
#define RGP_SELF_CharaCmdLoopSePlay_22a7b0 1
#include "port/game_protos.h"
#line 1
/* PARK 1/3: length-wrong (50w vs retail 52w). m2c draft was fully typed already; retail keeps a duplicated per-branch epilogue (b + inline return value) that -O4 here merges away. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdLoopSePlay_22a7b0(s32 *arg0, s32 arg1, s32 arg2) {
    f32 var_f0;
    s32 temp_2;
    s32 temp_16;

    if ((arg2 != 1) && (arg2 != 2)) {
        return 1;
    }
    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *arg0));
    if (temp_2 == 0) {
        return 1;
    }
    temp_16 = CharaWeaponSeIdRemap_1fd430(*arg0, ScriptArgGetInt_302d70(arg1));
    if (arg2 >= 2) {
        var_f0 = ScriptArgGetFloat_302cf0(arg1 + 5);
    } else {
        var_f0 = 1.0f;
    }
    CharaPlayLoopSe_213c10(temp_2, temp_16);
    return 1;
}
