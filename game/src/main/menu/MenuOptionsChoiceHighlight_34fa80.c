/* rgp:protos */
#define RGP_SELF_MenuOptionsChoiceHighlight_34fa80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

extern f32 D_0047D288;
extern s32 D_00482360;

s32 MenuOptionsChoiceHighlight_34fa80(s32 arg0, s32 arg1)
{
    UiSetWidgetColor_2905b0(D_00482360, arg0, 1.0f, 1.0f, 1.0f, 1.0f);
    UiSetWidgetColor_2905b0(D_00482360, arg1, D_0047D288, D_0047D288, D_0047D288, 1.0f);
    UiSetSpriteUvRect_28f9d0(D_00482360, arg0, 0, 0, 0x48, 0x1A, 0);
    UiSetSpriteUvRect_28f9d0(D_00482360, arg1, 0, 0x1A, 0x48, 0x1A, 0);
    return 1;
}
