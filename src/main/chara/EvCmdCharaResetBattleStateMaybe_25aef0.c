#include "types.h"
struct E8 { u8 b[8]; };
extern s32 GetActionMgr_1fdb50(void);
extern s32 ScriptGetInt_26a2a0(struct E8 *);
extern void *ActionMgrFindById_233b50(s32, s32);
extern void CharaResetBattleStateMaybe_212f20(void *, s32);
s32 EvCmdCharaResetBattleStateMaybe_25aef0(struct E8 *p0, s32 p1)
{
    struct E8 *q;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 flag;
    void *r5;

    q = p0;
    r0 = GetActionMgr_1fdb50();
    r1 = ScriptGetInt_26a2a0(q++);
    flag = 0;
    if (p1 >= 2) {
        r2 = ScriptGetInt_26a2a0(q);
        flag = (r2 != 0);
    }
    r5 = ActionMgrFindById_233b50(r0, r1);
    if (r5 != 0) {
        CharaResetBattleStateMaybe_212f20(r5, flag);
    }
    return 1;
}
