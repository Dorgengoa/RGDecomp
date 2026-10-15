/* MATCH (main s22): the final FontDrawText_26cdc0 4th-arg `addu` was the
   call-normalisation case of [[mwcc-commutative-add-operand-order]] --
   `arg0 + (call tree)` and `(call tree) + arg0` are the SAME object because
   mwcc pushes a call expression into rt.  `(call tree) - (-arg0)` pins it in
   rs and the unit closes. */
#include "types.h"

extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void DrawListClearScreen_1423c0(s32, s32, f32, s32, s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);
extern void TextStyleInit_26c610(void *);
extern void FontDrawText_26cdc0(void *, s32, s32, s32);
extern void FontMeasureString_26daf0(void *, s32, s32 *, s32 *);
extern void TextStyleSetFontType_26edf0(void *, s32);
extern void TextStyleSetGradRgbaU32_26f170(void *, s32);
extern void TextStyleSetRgbaU32_26f210(void *, s32);
extern void TextStyleAddSpacing_26f2b0(void *, s32, s32);
extern s32 DiscStatusMessageGetText_39ecd0(void);

void DiscStatusMessageDraw_39ecf0(s32 arg0)
{
    s32 sp8C;
    s32 sp88;
    u8 sp40[0x40];
    s32 temp_17;
    s32 temp_18;
    s32 temp_2;
    s32 temp_5;

    temp_2 = GetDrawCtx_15de80();
    DrawListClearScreen_1423c0(temp_2, 0, 0.0f, 0, 0x80);
    DrawListAddTexLoad_1418c0(temp_2, 0x338, 1.0f);
    TextStyleInit_26c610(sp40);
    TextStyleInit_26c610(sp40);
    TextStyleSetFontType_26edf0(sp40, 1);
    TextStyleAddSpacing_26f2b0(sp40, 3, 0);
    TextStyleSetRgbaU32_26f210(sp40, 0x80686A6B);
    TextStyleSetGradRgbaU32_26f170(sp40, 0x80686A6B);
    temp_18 = DiscStatusMessageGetText_39ecd0();
    temp_5 = temp_18;
    sp8C = 0;
    sp88 = 0;
    FontMeasureString_26daf0(sp40, temp_5, &sp8C, &sp88);
    temp_17 = (DrawEnvGetWidth_1451e0(temp_2) - sp8C) >> 1;
    FontDrawText_26cdc0(sp40, temp_18, temp_17, ((DrawEnvGetHeight_1451d0(temp_2) - 0x18) >> 1) - (-arg0));
}
