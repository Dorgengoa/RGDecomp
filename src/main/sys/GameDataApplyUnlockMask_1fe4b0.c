#include "types.h"
extern s32 GetGameData_1fede0(void);
extern void McSaveGetMergedFlags_373050(s64 *);
extern void UnlockMaskGrantItems_3e3ef0(s32, s64);

void GameDataApplyUnlockMask_1fe4b0(void)
{
    s64 v;
    s32 o;

    o = GetGameData_1fede0();
    McSaveGetMergedFlags_373050(&v);
    UnlockMaskGrantItems_3e3ef0(o, v);
}
