#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ScriptGetInt_26a2a0(void *p);
extern f32 TaggedGetFloat_26a280(void *p);
extern s32 ActionMgrFindById_233b50(s32 a, s32 b);
extern void CharaRequestTint_213fd0(s32 obj, s32 a, s32 b, f32 c, f32 d, f32 e, f32 f, f32 g);

struct E { s32 a; s32 b; };

s32 EvCmdCharaRequestTint_269740(struct E *p, s32 count)
{
    s32 obj;
    s32 a;
    s32 b;
    f32 c;
    f32 d;
    f32 e;
    f32 f;
    f32 g;

    if (count < 7) {
        return 1;
    }
    obj = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), ScriptGetInt_26a2a0(p++));
    if (obj == 0) {
        return 1;
    }
    a = ScriptGetInt_26a2a0(p++);
    b = ScriptGetInt_26a2a0(p++);
    c = (f32)ScriptGetInt_26a2a0(p++);
    d = (f32)ScriptGetInt_26a2a0(p++);
    e = (f32)ScriptGetInt_26a2a0(p++);
    f = (f32)ScriptGetInt_26a2a0(p++);
    g = 1.0f;
    if (count >= 8) {
        g = TaggedGetFloat_26a280(p);
    }
    CharaRequestTint_213fd0(obj, a, b, c, d, e, f, g);
    return 1;
}
