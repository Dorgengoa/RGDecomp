/* rgp:protos */
#define RGP_SELF_AiCmdCharaSetRetargetOnDamageMaybe_2c2f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

typedef struct S2c2f { u8 pad[0xA44]; s32 unkA44; } S2c2f;
s32 AiCmdCharaSetRetargetOnDamageMaybe_2c2f00(s32 arg0, s32 arg1)
{
    s32 temp_16;
    s32 var_2;
    S2c2f *temp_2;

    if (arg1 < 2) {
        return 0;
    }
    temp_16 = ((s32)GetActionMgr_1fdb50());
    temp_2 = ActionMgrFindById_233b50(temp_16, ScriptSlotGetInt_2cc9c0(arg0));
    if (temp_2 == NULL) {
        return 1;
    }
    {
        u8 f = ScriptSlotGetInt_2cc9c0(arg0 + 8) != 0;
        if (f) {
            var_2 = temp_2->unkA44 & 0xFFEFFFFF;
        } else {
            var_2 = temp_2->unkA44 | 0x100000;
        }
        temp_2->unkA44 = var_2;
    }
    return 1;
}
