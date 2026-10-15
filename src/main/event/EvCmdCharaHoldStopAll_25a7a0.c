#include "types.h"

extern const u8 D_0045EE70[];
extern void TaskSetEnabled_27c2a0(s32, const u8 *);
extern void *GetActionMgr_1fdb50(void);
extern void *ActionMgrGetCharaList_233b40(void *);
extern void *DListGetHead_42ea60(void *);
extern void *DListGetNext_42eb30(void *);
extern void CharaSetHoldFlags_214270(void *, s32);
extern void CharaSetHoldDirXYZ_214380(void *, f32, f32, f32);

s32 EvCmdCharaHoldStopAll_25a7a0(void)
{
    void *n;
    void *o;

    TaskSetEnabled_27c2a0(1, D_0045EE70);
    n = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(GetActionMgr_1fdb50()));
    while (n != 0) {
        o = (void *)((u8 *)n + 0x10);
        n = DListGetNext_42eb30(n);
        CharaSetHoldFlags_214270(o, 4);
        CharaSetHoldDirXYZ_214380(o, 0.0f, 0.0f, 0.0f);
    }
    return 1;
}
