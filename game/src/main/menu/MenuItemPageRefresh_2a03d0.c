/* rgp:protos */
#define RGP_SELF_MenuItemPageRefresh_2a03d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuItemPageRefresh_2a03d0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    MenuDrawItemTabs_2a4ee0(arg0, arg1, (signed char)((s64) (s8) MenuItemGetOpenModeMaybe_2a4ec0((void *)arg0)));
    MenuFillItemGrid_2a4b40(arg0, arg2);
    MenuItemGridMarkInUse_2a4860(arg0, arg3);
    MenuFillItemCounts_2a3d90(arg0, arg4);
    MenuShowMoneyAndItemCounts_2a32d0(arg0, arg5, arg6);
    return 1;
}
