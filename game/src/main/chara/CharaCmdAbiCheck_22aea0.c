/* rgp:protos */
#define RGP_SELF_CharaCmdAbiCheck_22aea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdAbiCheck_22aea0(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_16;
    s32 temp_2;

    if ((arg2 != 1) && (arg2 != 2) && (arg2 != 3)) {
        return 1;
    }
    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *arg0));
    if (temp_2 == 0) {
        return 1;
    }
    temp_16 = ((s32)CharaGetAbltName_213810(temp_2));
    return CharaCmdRunIfElseEvnt_22e480(*arg0, ((unsigned char)StrEqualNonNull_1ca6c0(temp_16, ScriptArgGetStr_302cb0(arg1))) & 0xFF, (u8 *)arg1 + 5, arg2 - 1);
    return 1;
}
