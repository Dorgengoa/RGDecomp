/* rgp:protos */
#define RGP_SELF_MenuMemberListCloseSlideStep_3426a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D65C;
extern f32 D_0047D668;
extern s32 D_00482360;
extern s32 D_00482D24;

s32 MenuMemberListCloseSlideStep_3426a0(void)
{
    s32 sp1C;
    s32 sp18;

    switch (D_00482D24) {
    case 0:
        UiPlaceRowWidgetPairMaybe_28cf40(1, 3, 0x19, 0x10, D_00482360);
        UiGetWidgetPos_2910a0(D_00482360, 0x19, &sp1C, &sp18);
        if (sp1C < 0x1F) {
            D_00482D24 = 1;
            UiFadeWidgetAlpha_290690(D_00482360, 0x41, 0.0f, D_0047D668, -1.0f);
        }
        break;
    case 1:
        UiGetWidgetAlpha_290770(D_00482360, 0x41);
        UiFadeWidgetAlpha_290690(D_00482360, 0x3C, 1.0f, D_0047D65C, -1.0f);
        {
            void *p = UiFindWidget_290460(D_00482360, 0x3C);
            *(s16 *)((u8 *)*(void **)((u8 *)p + 0x20) + 0x8) = 0x60;
        }
        D_00482D24 = 3;
        break;
    }
    return 0;
}
