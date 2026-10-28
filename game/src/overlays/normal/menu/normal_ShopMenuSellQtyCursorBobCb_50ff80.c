/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellQtyCursorBobCb_50ff80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050FF80 -- one func_28D820 on the overlay object, returns 1. */
extern u8 normal_D_00527E70[];
/*rgp*/

s32 normal_ShopMenuSellQtyCursorBobCb_50ff80(void)
{
    UiSelFrameAnimStep_28d820(normal_D_00527E70, 0x3F);
    return 1;
}
