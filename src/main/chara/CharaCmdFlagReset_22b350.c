#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32 a, s32 b);
extern s32 ScriptArgGetInt_302d70(void *p);
extern void CharaFlagWordClear_214840(s32 obj, s32 r);

s32 CharaCmdFlagReset_22b350(s32 *p0, void *p1, s32 kind)
{
    s32 obj;

    if (kind != 1) {
        return 1;
    }
    obj = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *p0);
    if (obj == 0) {
        return 1;
    }
    CharaFlagWordClear_214840(obj, ScriptArgGetInt_302d70(p1));
    return 1;
}
