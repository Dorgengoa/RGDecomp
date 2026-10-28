/* rgp:protos */
#define RGP_SELF_CharaCmdThink_22c8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj00233b50 {
    u8 pad00[0xA44];
    u32 unkA44;
} Obj00233b50;

/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdThink_22c8c0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 var_2;
    s32 var_2_2;
    Obj00233b50 *temp_2;
    u8 flag;

    if (arg2 != 1) {
        return 1;
    }
    temp_2 = ((Obj00233b50 *)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *arg0));
    if (temp_2 == NULL) {
        return 1;
    }
    flag = !(ScriptArgGetInt_302d70(arg1) != 0);
    if (!(flag & 0xFF)) {
        var_2 = temp_2->unkA44 & 0xFF7FFFFF;
    } else {
        var_2 = temp_2->unkA44 | 0x800000;
    }
    temp_2->unkA44 = var_2;
    flag = (ScriptArgGetInt_302d70(arg1) != 0);
    if (!flag) {
        var_2_2 = temp_2->unkA44 & 0xFEFFFFFF;
    } else {
        var_2_2 = temp_2->unkA44 | 0x01000000;
    }
    temp_2->unkA44 = var_2_2;
    return 1;
}
