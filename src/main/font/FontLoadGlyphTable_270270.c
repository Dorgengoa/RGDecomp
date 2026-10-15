#include "types.h"

extern s32 GetSysTextStyle_313570(void);
extern void TextStyleSetFontType_26edf0(s32, s32);
extern void FontSetGlyphTable_26f730(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void FontLoadGlyphTable_270270(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = GetSysTextStyle_313570();
    TextStyleSetFontType_26edf0(r0, p0);
    FontSetGlyphTable_26f730(r0, p1, p2);
}
