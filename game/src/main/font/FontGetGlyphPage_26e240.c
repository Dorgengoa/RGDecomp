/* rgp:protos */
#define RGP_SELF_FontGetGlyphPage_26e240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 FontGetGlyphPage_26e240(s32 pad0, s32 arg1)
{
    s32 idx;
    s32 r;

    switch (((signed char)TextStyleGetFontType_26ede0((void *)pad0))) {
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
