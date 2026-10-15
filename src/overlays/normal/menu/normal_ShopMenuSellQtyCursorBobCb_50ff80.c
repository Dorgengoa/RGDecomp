#include "types.h"
/* normal 0x0050FF80 -- one func_28D820 on the overlay object, returns 1. */
extern const u8 D_00527E70[];
extern void func_28D820(const void *p, s32 id);

s32 normal_ShopMenuSellQtyCursorBobCb_50ff80(void)
{
    func_28D820(D_00527E70, 0x3F);
    return 1;
}
