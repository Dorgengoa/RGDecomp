#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32 arg0, s32 arg1);
extern void CharaSetPosVec_2387a0(s32 arg0, f32 *arg1);
extern f32 ScriptSlotGetFloat_2cc9a0(s32 arg0);
extern s32 ScriptSlotGetInt_2cc9c0(s32 arg0);

s32 AiCmdCharaSetPosById_2c9ee0(s64 *arg0, s32 arg1) {
    f32 sp[3];
    s32 temp_16;
    s32 temp_2;

    if (arg1 != 4) {
        return 0;
    }
    temp_16 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    sp[0] = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    sp[1] = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    sp[2] = ScriptSlotGetFloat_2cc9a0((s32)arg0);
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), temp_16);
    if (temp_2 != 0) {
        CharaSetPosVec_2387a0(temp_2, sp);
    }
    return 1;
}
