#include "types.h"

s32 TextStyleGetFontType_26ede0();
s32 FontGetGlyphBankType2_26f7a0(s32);
s32 FontGetGlyphBankType1_26f7d0(s32);
s32 FontGetGlyphBankType0_26f800(s32);
s32 FontGetPageTex_270000(s32);

s32 FontGetGlyphPage_26e240(s32 pad0, s32 arg1)
{
    s32 idx;
    s32 r;

    switch (TextStyleGetFontType_26ede0()) {
    case 1:
        r = FontGetGlyphBankType1_26f7d0(arg1);
        if (r < 0 || r >= 4) {
            return 0;
        }
        idx = r;
        break;
    case 0:
        r = FontGetGlyphBankType0_26f800(arg1);
        if (r < 0 || r > 0) {
            return 0;
        }
        idx = r + 7;
        break;
    case 2:
        r = FontGetGlyphBankType2_26f7a0(arg1);
        if (r < 0 || r >= 3) {
            return 0;
        }
        idx = r + 4;
        break;
    }
    return FontGetPageTex_270000(idx);
}
