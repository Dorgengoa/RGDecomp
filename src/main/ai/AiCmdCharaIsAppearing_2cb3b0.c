#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 CharaIsAppearing_214d80(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 D_004DB92C[4];

s32 AiCmdCharaIsAppearing_2cb3b0(s64 *arg0, s32 arg1) {
    s32 t;
    s32 u;

    if (arg1 == 1) {
        if (D_004DB92C[0] == 0) {
            return 0;
        }
        ScriptSlotStoreIntRef_2cc900((s32)arg0, CharaIsAppearing_214d80(D_004DB92C[0]) & 0xFF);
        goto gpt_return;
    }
    if (arg1 == 2) {
        t = ScriptSlotGetInt_2cc9c0((s32)arg0++);
        if (t < 0 || t >= 0xE0) {
            ScriptSlotStoreIntRef_2cc900((s32)arg0, 0);
            return 1;
        }
        u = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), t);
        if (u == 0) {
            return 1;
        }
        ScriptSlotStoreIntRef_2cc900((s32)arg0, CharaIsAppearing_214d80(u) & 0xFF);
    }
    goto gpt_return;

gpt_return: return 1;
}
