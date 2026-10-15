#include "types.h"

extern void UiSetSpriteUvRect_28f9d0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern void UiSetWidgetColor_2905b0(s32 a, s32 b, f32 c, f32 d, f32 e, f32 f);

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
