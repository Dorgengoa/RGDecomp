/* rgp:protos */
#define RGP_SELF_TransMenuItemDiscardCloseState_37d260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D978 __attribute__((section(".sdata")));
extern void *D_00484710;
extern void *D_0048470C;

/*rgp*/
/*rgp*/

s32 TransMenuItemDiscardCloseState_37d260(void)
{
    f32 g = D_0047D978;

    UiFadeWidgetAlpha_290690(D_00484710, 0x761E, 0.0f, g, -1.0f);
    StateMachineSetState_28ede0(D_0048470C, 0x24, 0);
    return 1;
}
