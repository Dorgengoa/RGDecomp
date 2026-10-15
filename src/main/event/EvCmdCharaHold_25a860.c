#include "types.h"

extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrGetCharaList_233b40(s32);
extern s32 DListGetHead_42ea60(s32);
extern s32 DListGetNext_42eb30(s32);
extern void CharaSetHoldFlags_214270(s32, s32);

extern u8 D_0045EE70[];

s32 EvCmdCharaHold_25a860(void)
{
    s32 p;
    s32 q;

    TaskSetEnabled_27c2a0(1, D_0045EE70);
    p = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(GetActionMgr_1fdb50()));
    while (p != 0) {
        q = p + 0x10;
        p = DListGetNext_42eb30(p);
        CharaSetHoldFlags_214270(q, 1);
    }
    return 1;
}
