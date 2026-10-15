#include "types.h"
extern s32 GetActionMgr_1fdb50(void);
extern void CharaSetInvincibleTime_2138a0(void *arg0, s32 arg1, s32 arg2, f32 arg3);
extern void *ActionMgrFindById_233b50(s32 arg0, s32 arg1);
extern void ScriptSetRefInt_26a1e0(s32 arg0, s32 arg1);
extern void *FieldRandomSpawnRollMaybe_2f2090(void);

s32 EvCmdFieldRandomSpawnMaybe_25bbb0(s32 arg0)
{
    s32 f;
    u8 *t;
    u8 *p;

    t = FieldRandomSpawnRollMaybe_2f2090();
    if (t != NULL) {
        ScriptSetRefInt_26a1e0(arg0, *(s32 *)(t + 0xC));
        p = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s32 *)(t + 0xC));
        if (p != NULL) {
            f = *(s32 *)(p + 0xA44);
            *(s32 *)(p + 0xA44) = f | 0x01000000;
            CharaSetInvincibleTime_2138a0(p, 0x01000000, f, 330.0f);
        }
    } else {
        ScriptSetRefInt_26a1e0(arg0, -1);
    }
    return 1;
}
