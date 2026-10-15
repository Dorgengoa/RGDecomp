#include "types.h"

extern s32 TextStyleGetFontType_26ede0(void);

s32 FontGetDefaultGlyphWidth_26f480(void)
{
    s32 v;
    s32 r;

    v = TextStyleGetFontType_26ede0();
    if (v != 2) {
        if (v != 0) {
            if (v != 1) {
                r = 0;
            } else {
                r = 0x12;
            }
        } else {
            r = 0x10;
        }
    } else {
        r = 0x10;
    }
    return r;
}
