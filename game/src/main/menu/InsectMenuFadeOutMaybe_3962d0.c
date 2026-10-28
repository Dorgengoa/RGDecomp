/* rgp:protos */
#define RGP_SELF_InsectMenuFadeOutMaybe_3962d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047DD2C;
extern f32 D_0047FF44;
extern s32 D_004834F0;
extern u8 D_004E95C0[0x400];
extern u8 D_004E95E0[0x400];

s32 InsectMenuFadeOutMaybe_3962d0(s32 pad0, s32 arg1)
{
    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_004E95E0, 0x7531, 0);
        UiSetWidgetAlpha_2907a0(D_004E95C0, 0x7534, 1.0f);
        UiFadeWidgetAlpha_290690(D_004E95C0, 0x7534, 0.0f, D_0047DD2C, -1.0f);
        UiSetWidgetAlpha_2907a0(D_004E95C0, 0x7538, 1.0f);
        UiFadeWidgetAlpha_290690(D_004E95C0, 0x7538, 0.0f, D_0047DD2C, -1.0f);
        D_0047FF44 = 1.0f;
    }
    D_0047FF44 += D_0047DD2C;
    if (UiGetWidgetAlpha_290770(D_004E95C0, 0x7538) <= 0.0f) {
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7538, 0, 1);
        StateMachineSetState_28ede0(&D_004834F0, 0x753F, 0);
    }
    return 1;
}
