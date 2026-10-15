#include "types.h"

extern s32 ModelObjTexAnimIsPlayingByName_1ac490(s32 a, s32 b);
extern void ModelObjTexAnimResetByName_1ac510(s32 a, s32 b);
extern void ModelObjTexAnimStartByName_1ac590(s32 a, s32 b);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32 a, s32 b);
extern s32 CharaGetModelObj_2386f0(s32 v);
extern s32 ScriptArgGetStr_302cb0(s32 v);
extern s32 ScriptArgGetInt_302d70(s32 v);

s32 CharaCmdTexAnime_22cb20(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 t;
    s32 h;
    s32 k;
    s32 hasA;

    if ((arg2 != 2) && (arg2 != 3)) {
        return 0;
    }
    t = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (t == 0) {
        return 1;
    }
    h = CharaGetModelObj_2386f0(t);
    if (h == 0) {
        return 1;
    }
    k = ScriptArgGetStr_302cb0(arg1);
    hasA = ScriptArgGetInt_302d70(arg1 + 0xA) != 0;
    if (ScriptArgGetInt_302d70(arg1 + 5) != 0) {
        if ((hasA != 0) || (ModelObjTexAnimIsPlayingByName_1ac490(h, k) == 0)) {
            ModelObjTexAnimStartByName_1ac590(h, k);
        }
    } else if ((hasA != 0) || (ModelObjTexAnimIsPlayingByName_1ac490(h, k) != 0)) {
        ModelObjTexAnimResetByName_1ac510(h, k);
    }
    return 1;
}
