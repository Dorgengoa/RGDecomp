#include "types.h"

extern void *GetDrawCtx_15de80(void);
extern void DrawListAddTexLoad_1418c0(void *, s32, f32);
extern void *GetSysTextStyle_313570(void);
extern void TextStyleInit_26c610(void *);
extern void TextStyleSetFontType_26edf0(void *, void *);
extern void TextStyleSetFixedCell_26f0e0(void *, s32, s32);

void FontCtxSetup9x15_2085d0(s32 a, void *b)
{
    void *r;
    void *s;

    r = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(r, a, 1.0f);
    s = GetSysTextStyle_313570();
    TextStyleInit_26c610(s);
    TextStyleSetFontType_26edf0(s, b);
    TextStyleSetFixedCell_26f0e0(s, 9, 0xF);
}
