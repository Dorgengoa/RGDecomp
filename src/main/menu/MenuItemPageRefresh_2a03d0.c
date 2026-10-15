#include "types.h"

extern void MenuShowMoneyAndItemCounts_2a32d0(s32 a, s32 b, s32 c);
extern void MenuFillItemCounts_2a3d90(s32 a, s32 b);
extern void MenuItemGridMarkInUse_2a4860(s32 a, s32 b);
extern void MenuFillItemGrid_2a4b40(s32 a, s32 b);
extern s64 MenuItemGetOpenModeMaybe_2a4ec0(void);
extern void MenuDrawItemTabs_2a4ee0(s32 a, s32 b, s64 c);

s32 MenuItemPageRefresh_2a03d0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    MenuDrawItemTabs_2a4ee0(arg0, arg1, (s64) (s8) MenuItemGetOpenModeMaybe_2a4ec0());
    MenuFillItemGrid_2a4b40(arg0, arg2);
    MenuItemGridMarkInUse_2a4860(arg0, arg3);
    MenuFillItemCounts_2a3d90(arg0, arg4);
    MenuShowMoneyAndItemCounts_2a32d0(arg0, arg5, arg6);
    return 1;
}
