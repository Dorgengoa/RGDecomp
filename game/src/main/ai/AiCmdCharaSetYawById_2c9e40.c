/* rgp:protos */
#define RGP_SELF_AiCmdCharaSetYawById_2c9e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdCharaSetYawById_2c9e40(s64 *arg0, s32 arg1) {
    f32 t20;
    s32 t16;
    s32 t2;

    if (arg1 != 4) {
        return 0;
    }
    t16 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    t20 = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    ScriptSlotGetFloat_2cc9a0((s32)arg0);
    t2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), t16));
    if (t2 != 0) {
        CharaSetYaw_2138f0(t2, t20);
    }
    return 1;
}
