/* rgp:protos */
#define RGP_SELF_CharaCmdBaseCheck_22adb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                                 /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/               /* extern */
/*rgp*/                         /* extern */
/*rgp*/                         /* extern */
/*rgp*/                              /* extern */

s32 CharaCmdBaseCheck_22adb0(s32 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_19;
    s32 temp_19_2;
    s32 temp_2;
    s32 temp_2_2;

    if ((arg2 != 1) && (arg2 != 2) && (arg2 != 3)) {
        return 1;
    }
    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *arg0));
    if (temp_2 == 0) {
        return 1;
    }
    temp_19_2 = ((s32)GetActionMgr_1fdb50());
    temp_2_2 = ((s32)ActionMgrFindTableByScopeId_233c20(temp_19_2, ((short)CharaGetActScopeId_214a70(temp_2))));
    if (temp_2_2 == 0) {
        return 1;
    }
    temp_19 = ((short)ActCfgTableGetScopeId_223d00(temp_2_2));
    return CharaCmdRunIfElseEvnt_22e480(*arg0, temp_19 == ScriptArgGetInt_302d70(arg1), arg1 + 5, arg2 - 1);
    return 1;
}
