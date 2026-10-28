/* rgp:protos */
#define RGP_SELF_FontGetLineHeight_26f3e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 FontGetLineHeight_26f3e0(void *rgp_a0)
{
    s32 v;
    s32 r;

    v = ((signed char)TextStyleGetFontType_26ede0((void *)rgp_a0));
    if (v != 2) {
        if (v != 0) {
            if (v != 1) {
                r = 0;
            } else {
                r = 0x16;
            }
        } else {
            r = 0x12;
        }
    } else {
        r = 0x14;
    }
    return r;
}
