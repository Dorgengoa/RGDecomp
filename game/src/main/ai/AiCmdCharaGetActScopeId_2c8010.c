/* rgp:protos */
#define RGP_SELF_AiCmdCharaGetActScopeId_2c8010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004DB92C[0x400];

s32 AiCmdCharaGetActScopeId_2c8010(s64 *arg0, s32 arg1)
{
    s32 temp_16;
    s32 temp_2;

    if (arg1 == 1) {
        if ((*(s32 *)D_004DB92C) != 0) {
            ScriptSlotStoreIntRef_2cc900((s32)arg0, ((short)CharaGetActScopeId_214a70((*(s32 *)D_004DB92C))));
        }
    } else if (arg1 == 2) {
        temp_16 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
        temp_2 = (s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), temp_16);
        if (temp_2 != 0) {
            ScriptSlotStoreIntRef_2cc900((s32)arg0, ((short)CharaGetActScopeId_214a70(temp_2)));
        } else {
            ScriptSlotStoreIntRef_2cc900((s32)arg0, -1);
        }
    }
    return 1;
}
