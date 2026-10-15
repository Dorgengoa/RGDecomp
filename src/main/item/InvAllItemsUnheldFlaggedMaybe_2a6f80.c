#include "types.h"

extern s32 GetGameData_1fede0(void);
extern s32 IterNext_370040(void *arg0);
extern void IterInit_370170(void *arg0, void *arg1);
extern void InvViewCtorFromOwner_3cec70(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 ItemIsUnheldFlaggedMaybe_3d4420(s32 arg0);

s32 InvAllItemsUnheldFlaggedMaybe_2a6f80(void)
{
    u8 sp28[8];
    u8 sp10[0x18];
    s32 t;

    InvViewCtorFromOwner_3cec70(sp10, GetGameData_1fede0(), 9, -1, -1, -1);
    IterInit_370170(sp28, sp10);
    goto test;
    do {
        if (ItemIsUnheldFlaggedMaybe_3d4420(t) == 0) {
            return 0;
        }
test:
        t = IterNext_370040(sp28);
    } while (t != 0);
    return 1;
}
