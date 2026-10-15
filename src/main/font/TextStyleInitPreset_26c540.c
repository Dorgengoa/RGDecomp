#include "types.h"

extern void TextStyleInit_26c610(s32);
extern void TextStyleSetFontType_26edf0(s32, s32);
extern void TextStyleSetSpacing_26f300(s32, s32, s32);
extern void TextStyleSetGradientMode_26e330(s32, s32);
extern void TextStyleSetRgba_26f280(s32, s32, s32, s32, s32);
extern void TextStyleSetGradRgba_26f1e0(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TextStyleInitPreset_26c540(s32 p0, s32 p1)
{
    TextStyleInit_26c610(p0);
    if (p1 == 3) {
        TextStyleSetFontType_26edf0(p0, 2);
        TextStyleSetSpacing_26f300(p0, -2, 4);
        TextStyleSetGradientMode_26e330(p0, 0);
    }
    if (p1 == 1) {
        TextStyleSetFontType_26edf0(p0, 0);
        TextStyleSetSpacing_26f300(p0, -2, 4);
        TextStyleSetGradientMode_26e330(p0, 2);
        TextStyleSetRgba_26f280(p0, 0x80, 0x80, 0x40, 0x80);
        TextStyleSetGradRgba_26f1e0(p0, 0x80, 0x40, 0x40, 0x80);
    }
}
