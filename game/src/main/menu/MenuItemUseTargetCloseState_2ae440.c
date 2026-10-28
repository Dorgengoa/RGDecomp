/* rgp:protos */
#define RGP_SELF_MenuItemUseTargetCloseState_2ae440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D6D0 __attribute__((section(".sdata")));
extern void *D_00482360;
extern void *D_0048235C;

/*rgp*/
/*rgp*/

s32 MenuItemUseTargetCloseState_2ae440(void)
{
    f32 g = D_0047D6D0;

    UiFadeWidgetAlpha_290690(D_00482360, 0x8D, 0.0f, g, -1.0f);
    StateMachineSetState_28ede0(D_0048235C, 0x13, 0);
    return 1;
}
