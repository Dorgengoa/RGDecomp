/* rgp:protos */
#define RGP_SELF_MenuEquipSlotCloseState_2b7590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00482360;
extern void *D_0048235C;
extern f32 D_0047D6A0;
extern f32 D_0047D6A4;
/*rgp*/
/*rgp*/

s32 MenuEquipSlotCloseState_2b7590(s32 a, s32 b)
{
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x1A9, 0.0f, D_0047D6A4, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x185, 0.0f, D_0047D6A0, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x14D, 0.0f, D_0047D6A4, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x4B, 0);
    }
    return 1;
}
