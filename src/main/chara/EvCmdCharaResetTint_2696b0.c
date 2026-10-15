#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ScriptGetInt_26a2a0(void *p);
extern s32 ActionMgrFindById_233b50(s32 a, s32 b);
extern void CharaRequestTint_213fd0(s32 obj, s32 a, s32 b, f32 c, f32 d, f32 e, f32 f, f32 g);

s32 EvCmdCharaResetTint_2696b0(void *p, s32 count)
{
    s32 obj;

    if (count <= 0) {
        return 1;
    }
    obj = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), ScriptGetInt_26a2a0(p));
    if (obj == 0) {
        return 1;
    }
    CharaRequestTint_213fd0(obj, -1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    return 1;
}
