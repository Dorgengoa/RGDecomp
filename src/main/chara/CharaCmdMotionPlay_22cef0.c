#include "types.h"

extern void MotionListResetAll_171e00(s32 arg0);
extern void ModelObjPlayMotionByName_1867a0(s32 arg0, s32 arg1, s32 arg2);
extern s32 ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
extern s32 ObjIdResolveAlias_1ce490(s32 arg0, s32 arg1);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetActionMgr_1fdb50(void);
extern void CharaPlayMotion_212590(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4);
extern s32 ActionMgrFindById_233b50(s32 arg0, s32 arg1);
extern s32 ScriptArgGetStr_302cb0(s32 arg0);
extern s32 ScriptArgGetInt_302d70(s32 arg0);

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
    t = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), id);
    if (t == 0) {
        return 1;
    }
    v = 0;
    if (arg2 > 2) {
        v = ScriptArgGetInt_302d70(arg1 + 0xA);
    }
    p = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
    if (p != 0) {
        CharaPlayMotion_212590(p, t, ScriptArgGetStr_302cb0(arg1 + 5), v, 1.0f);
    } else {
        MotionListResetAll_171e00(t + 0x1F0);
        ModelObjPlayMotionByName_1867a0(t, ScriptArgGetStr_302cb0(arg1 + 5), v);
    }
    return 1;
}
