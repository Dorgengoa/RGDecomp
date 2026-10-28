/* rgp:protos */
#define RGP_SELF_TextStyleInitWithFontType_2931c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void TextStyleInitWithFontType_2931c0(s32 arg0, s64 arg1) {
    s64 temp_16;

    TextStyleInit_26c610((void *)arg0);
    temp_16 = (s64)(s8)arg1;
    TextStyleSetFontType_26edf0(arg0, (unsigned char)(temp_16));
    if (temp_16 == 2) {
        TextStyleAddSpacing_26f2b0(arg0, 3, 0);
        return;
    }
    if (temp_16 == 1) {
        TextStyleAddSpacing_26f2b0(arg0, 3, 0);
    }
}
