#include "types.h"

struct E25eb70 { s32 a; s32 b; };

extern s32 ScriptGetInt_26a2a0(void *p);
extern f32 TaggedGetFloat_26a280(void *p);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32 a, s32 b);
extern void CharaSetSrtVec40FromVec_238780(s32 obj, f32 *v);

s32 EvCmdCharaSetSrtVec40_25eb70(struct E25eb70 *p)
{
    f32 v[3];
    s32 a;
    s32 obj;

    a = ScriptGetInt_26a2a0(p++);
    obj = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), a);
    if (obj == 0) {
        return 0;
    }
    v[0] = TaggedGetFloat_26a280(p++);
    v[1] = TaggedGetFloat_26a280(p++);
    v[2] = TaggedGetFloat_26a280(p);
    CharaSetSrtVec40FromVec_238780(obj, v);
    return 1;
}
