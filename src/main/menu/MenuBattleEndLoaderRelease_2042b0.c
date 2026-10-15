#include "types.h"

extern u8 D_004BBA40[];
extern s32 D_00481C10;

extern s32 func_4EC980(void *);
extern s32 GetLoaderMgr_1f59d0(void);
extern void LoaderReleaseById_1cd340(s32, s32);

void MenuBattleEndLoaderRelease_2042b0(void)
{
    s32 handle;
    s32 i;

    func_4EC980(D_004BBA40);
    handle = GetLoaderMgr_1f59d0();
    i = 0;
    do {
        LoaderReleaseById_1cd340(handle, *(s32 *)((u8 *)&D_00481C10 + (i << 3)));
        i += 1;
    } while (i < 2);
}
