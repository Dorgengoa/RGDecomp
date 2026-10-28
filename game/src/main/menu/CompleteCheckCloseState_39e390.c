/* rgp:protos */
#define RGP_SELF_CompleteCheckCloseState_39e390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004E96B0[];
extern f32 D_0047D7C8;
extern s8 D_004836A0;
extern s8 D_004836B0;
/*rgp*/
/*rgp*/
/*rgp*/

s32 CompleteCheckCloseState_39e390(s32 a, s32 b)
{
    f32 r;

    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_004E96B0, 1, 0.0f, D_0047D7C8, -1.0f);
    }
    r = UiGetWidgetAlpha_290770(D_004E96B0, 1);
    if (r <= 0.0f) {
        UiSetWidgetVisible_290010(D_004E96B0, 1, 0, -1);
        D_004836A0 = 0;
        D_004836B0 = 0;
    }
    return 1;
}
