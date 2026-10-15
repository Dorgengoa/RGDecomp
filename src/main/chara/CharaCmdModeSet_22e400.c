#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 ScriptArgGetInt_302d70(s32);
extern void CharaSetBaseActionMode_213820(s32, s32);

struct Obj0 {
    s32 m00;
};

s32 CharaCmdModeSet_22e400(struct Obj0 *p0, s32 p1, s32 argc)
{
    s32 r0;
    s32 o;

    if (argc != 1) {
        return 0;
    }
    r0 = GetActionMgr_1fdb50();
    o = ActionMgrFindById_233b50(r0, p0->m00);
    if (o == 0) {
        return 1;
    }
    CharaSetBaseActionMode_213820(o, ScriptArgGetInt_302d70(p1));
    return 1;
}
