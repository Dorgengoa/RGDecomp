/* rgp:protos */
#define RGP_SELF_CharaCmdMotionPlay_22cef0 1
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
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdMotionPlay_22cef0(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 id;
    s32 t;
    s32 v;
    s32 p;

    if ((arg2 != 2) && (arg2 != 3)) {
        return 0;
    }
    id = ObjIdResolveAlias_1ce490(*arg0, ScriptArgGetInt_302d70(arg1));
    t = ((s32)ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), id));
    if (t == 0) {
        return 1;
    }
    v = 0;
    if (arg2 > 2) {
        v = ScriptArgGetInt_302d70(arg1 + 0xA);
    }
    p = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), id));
    if (p != 0) {
        CharaPlayMotion_212590(p, t, ScriptArgGetStr_302cb0(arg1 + 5), v, 1.0f);
    } else {
        MotionListResetAll_171e00(t + 0x1F0);
        ModelObjPlayMotionByName_1867a0(t, ScriptArgGetStr_302cb0(arg1 + 5), v);
    }
    return 1;
}
