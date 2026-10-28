/* rgp:protos */
#define RGP_SELF_FontGetDefaultGlyphWidth_26f480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 FontGetDefaultGlyphWidth_26f480(void *rgp_a0)
{
    s32 v;
    s32 r;

    v = ((signed char)TextStyleGetFontType_26ede0((void *)rgp_a0));
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
