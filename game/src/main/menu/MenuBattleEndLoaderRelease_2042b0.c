/* rgp:protos */
#define RGP_SELF_MenuBattleEndLoaderRelease_2042b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004BBA40[];
extern s32 D_00481C10;

extern void func_4EC980(void *);
/*rgp*/
/*rgp*/

void MenuBattleEndLoaderRelease_2042b0(void)
{
    s32 handle;
    s32 i;

    func_4EC980(D_004BBA40);
    handle = ((s32)GetLoaderMgr_1f59d0());
    i = 0;
    do {
        LoaderReleaseById_1cd340(handle, *(s32 *)((u8 *)&D_00481C10 + (i << 3)));
        i += 1;
    } while (i < 2);
}
