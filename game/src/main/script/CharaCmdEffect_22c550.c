/* rgp:protos */
#define RGP_SELF_CharaCmdEffect_22c550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                                 /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                      /* extern */
/*rgp*/                         /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */

s32 CharaCmdEffect_22c550(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 temp_2_2;
    s32 var_2;

    if ((arg2 != 1) && (arg2 != 2)) {
        return 0;
    }
    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *arg0));
    if (temp_2 == 0) {
        return 1;
    }
    var_2 = 0;
    if (arg2 > 1) {
        var_2 = ScriptArgGetInt_302d70(arg1 + 5) != 0;
    }
    if ((var_2 != 0) && (CharaGetActAbortCodeMaybe_2149b0(temp_2) != 0)) {
        return 1;
    }
    temp_2_2 = CharaGetActionTable_214cd0(temp_2);
    if (temp_2_2 == 0) {
        return 1;
    }
    CharaPlayEffectByName_21f800(temp_2_2, *arg0, ScriptArgGetStr_302cb0(arg1));
    return 1;
}
