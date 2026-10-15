#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern void CharaSetHoldDir_214390(s32 arg0, f32 *arg1);
extern s32 ActionMgrFindById_233b50(s32 arg0, s32 arg1);
extern f32 TaggedGetFloat_26a280(s32 arg0);
extern s32 ScriptGetInt_26a2a0(s32 arg0);

s32 EvCmdCharaSetHoldDir_25a6b0(s64 *arg0) {
    f32 v[3];
    s32 t;

    t = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), ScriptGetInt_26a2a0((s32)arg0++));
    if (t != 0) {
        v[0] = TaggedGetFloat_26a280((s32)arg0++);
        v[1] = TaggedGetFloat_26a280((s32)arg0++);
        v[2] = TaggedGetFloat_26a280((s32)arg0);
        CharaSetHoldDir_214390(t, v);
    }
    return 1;
}
