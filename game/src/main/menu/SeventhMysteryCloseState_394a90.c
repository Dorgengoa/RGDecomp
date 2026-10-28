/* rgp:protos */
#define RGP_SELF_SeventhMysteryCloseState_394a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D7C8;
extern s8 D_00483480;
extern s8 D_00483498;
extern s8 D_004E9550[0x100];

s32 SeventhMysteryCloseState_394a90(void)
{
    if (*((f32 *)UiGetWidgetColor_2904b0(D_004E9550, 5)) <= 1.0f) {
        UiFadeWidgetAlpha_290690(D_004E9550, 1, 0.0f, D_0047D7C8, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_004E9550, 1) <= 0.0f) {
        UiSetWidgetVisible_290010(D_004E9550, 1, 0, -1);
        D_00483480 = 0;
        D_00483498 = 0;
    }
    return 1;
}
