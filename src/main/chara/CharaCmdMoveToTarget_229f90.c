#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32 a, s32 b);
extern s32 ScriptArgGetInt_302d70(u8 *p);
extern f32 ScriptArgGetFloat_302cf0(u8 *p);
extern void CharaMoveTowardTarget_211320(s32 a, s32 b, f32 x, f32 y);

s32 CharaCmdMoveToTarget_229f90(s32 *self, u8 *p1, s32 kind)
{
    s32 obj;
    s32 b;
    f32 x;

    if (kind != 3) {
        return 0;
    }
    obj = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *self);
    if (obj == 0) {
        return 1;
    }
    b = ScriptArgGetInt_302d70(p1);
    x = ScriptArgGetFloat_302cf0(p1 + 5);
    CharaMoveTowardTarget_211320(obj, b, x, ScriptArgGetFloat_302cf0(p1 + 0xA));
    return 1;
}
