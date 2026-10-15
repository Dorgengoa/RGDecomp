#include "types.h"

extern void *GetGameData_1fede0(void);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
extern void ItemConsume_3d41b0(s32, s32, s32);

s32 EvCmdInvConsumeItem_25af80(s64 *arg0, s32 arg1)
{
    void *ctx;
    s32 a;
    s32 flag;
    s32 r;

    ctx = GetGameData_1fede0();
    a = ScriptGetInt_26a2a0((s32)arg0++);
    flag = 1;
    if (arg1 >= 2) {
        flag = ScriptGetInt_26a2a0((s32)arg0);
    }
    r = InvFindInCategoryRange_3c8370(*(s32 *)((u8 *)ctx + 0x18), a, 0, -1, 0, 0);
    if (r != 0) {
        ItemConsume_3d41b0(r, flag, 0);
    }
    return 1;
}
