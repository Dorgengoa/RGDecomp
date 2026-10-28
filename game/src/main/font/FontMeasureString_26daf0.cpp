#include "types.h"

extern "C" {
extern void FontMeasureGrowMax_26dd00(s32 *, s32 *, s32, s32);
extern s32 FontMapChar_26ed60(s32, s8);
extern s32 FontIsAsciiCode_26ed80(s32, s32);
extern s32 FontMatchSymbolTag_26ef40(s8 *, u16 *, s32 *);
extern s32 FontMatchGaijiTag_26ef90(s8 *, u16 *, s32 *);
extern void FontGetCharCellSize_26f310(s32, s32 *, s32 *, u16);
extern s32 FontGetGaijiHeight_26f860(s32, u16);
extern s32 FontGetGaijiWidth_26f890(s32, u16);
extern s32 strlen(const s8 *);
}

static inline bool IsWide(s32 a, s32 c) {
    return FontIsAsciiCode_26ed80(a, c);
}

extern "C" void FontMeasureString_26daf0(s32 font, s8 *s, s32 *outw, s32 *outh)
{
    u16 ce;
    u16 cc;
    s32 c8;
    s32 c4;
    s32 c0;
    s32 bc;
    s32 b8;
    s32 b4;
    s32 b0;
    s32 ac;
    s32 len;
    s32 x;
    s32 y;
    s32 i;
    s32 c;
    s8 *p;

    if (s == 0) {
        return;
    }
    len = strlen(s);
    c8 = 0;
    c4 = 0;
    x = 0;
    y = 0;
    i = 0;
    while (i < len) {
        p = s + i;
        if (FontMatchSymbolTag_26ef40(p, &ce, &c0) != 0) {
            FontGetCharCellSize_26f310(font, &bc, &b8, ce);
            x += bc;
            i += c0;
            FontMeasureGrowMax_26dd00(&c8, &c4, x, y + b8);
        } else if (FontMatchGaijiTag_26ef90(p, &cc, &b4) != 0) {
            x += (s16)FontGetGaijiWidth_26f890(font, cc);
            i += b4;
            FontMeasureGrowMax_26dd00(&c8, &c4, x, y + (s16)FontGetGaijiHeight_26f860(font, cc));
        } else {
            c = FontMapChar_26ed60(font, *p);
            FontGetCharCellSize_26f310(font, &b0, &ac, c);
            if (c == -2) {
                x = 0;
                i += 1;
                y += ac;
            } else if ((bool)FontIsAsciiCode_26ed80(font, c) != false) {
                i += 1;
                x += b0;
                FontMeasureGrowMax_26dd00(&c8, &c4, x, y + ac);
            } else {
                i += 2;
                x += b0;
                FontMeasureGrowMax_26dd00(&c8, &c4, x, y + ac);
            }
        }
    }
    *outw = c8;
    *outh = c4;
}
