/* rgp:protos */
#define RGP_SELF_EvCmdCharaResetTint_2696b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCharaResetTint_2696b0(void *p, s32 count)
{
    s32 obj;

    if (count <= 0) {
        return 1;
    }
    obj = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), ScriptGetInt_26a2a0(p)));
    if (obj == 0) {
        return 1;
    }
    CharaRequestTint_213fd0(obj, -1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    return 1;
}
