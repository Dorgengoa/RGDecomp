/* rgp:protos */
#define RGP_SELF_MenuEquipFadeToListState_2b6650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00482360;
extern void *D_00482370;
extern void *D_0048235C;
extern f32 D_0047D6A4;
extern u8 D_004DB790[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuEquipFadeToListState_2b6650(void)
{
    u8 t;

    t = MenuPartyFadeSequenceStep_2b9240(0x185, 0x130, 0x12F);
    if (t != 0) {
        MenuSetGridSel_29f9b0(D_00482370, 0, 0, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x163, 0.0f, D_0047D6A4, -1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x5F, 0);
    }
    UiSelFrameAnimStep_28d820(D_004DB790, 0x14D);
    return 1;
}
