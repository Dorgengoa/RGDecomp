#include "types.h"

extern s32 FontIsAsciiCodeNoFont_26f830(s32);
extern s32 FontGetCharWidth_26f4c0(s32, s32);
extern s32 FontGetDefaultGlyphWidth_26f480(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 FontGetGlyphWidth_26f420(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = FontIsAsciiCodeNoFont_26f830((p1 & 0xFFFF));
    rv3 = r2;
    if (r0 != 0) {
        r1 = FontGetCharWidth_26f4c0(p0, p1);
        rv3 = r1;
    } else {
        r2 = FontGetDefaultGlyphWidth_26f480(p0);
        rv3 = r2;
    }
    return rv3;
}
