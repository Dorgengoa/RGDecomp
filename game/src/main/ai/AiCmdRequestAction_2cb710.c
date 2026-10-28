/* rgp:protos */
#define RGP_SELF_AiCmdRequestAction_2cb710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdRequestAction_2cb710(s64 *arg0, s32 arg1)
{
    s32 temp_17;
    f32 var_f0;
    s32 temp_16;
    s32 temp_2;

    if ((arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    temp_16 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    temp_17 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), temp_16));
    temp_2 = ScriptSlotGetCodeAddr_2cc980((s32)arg0++);
    if (!((((unsigned char)CharaIsCurAction_211000(temp_17, temp_2)) & 0xFF) != 1)) {
        return 1;
    }
    var_f0 = 1.0f;
    if (arg1 == 3) {
        var_f0 = ScriptSlotGetFloat_2cc9a0((s32)arg0);
    }
    CharaRequestAction_212410(temp_17, temp_2, var_f0);
    return 1;
}
