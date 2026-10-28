/* rgp:protos */
#define RGP_SELF_CharaCmdPress_22a440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdPress_22a440(s32 *arg0, s32 arg1, s32 arg2) {
    f32 temp_f20;
    s32 temp_16;
    s32 temp_2;

    if (arg2 != 1) {
        return 0;
    }
    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *arg0));
    if (temp_2 == 0) {
        return 1;
    }
    temp_16 = ((s32)CharaGetSquash_2149d0(temp_2));
    temp_f20 = ScriptArgGetFloat_302cf0(arg1);
    CharaSquashStart_219190(temp_16, ScriptArgGetInt_302d70(arg1 + 5), temp_f20);
    return 1;
}
