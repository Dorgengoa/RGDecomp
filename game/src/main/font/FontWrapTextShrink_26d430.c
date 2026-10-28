/* rgp:protos */
#define RGP_SELF_FontWrapTextShrink_26d430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 FontWrapTextShrink_26d430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5)
{
    s32 flag;
    u8 saved;
    s32 r;

    if (arg1 == 0 || arg2 == 0 || arg3 <= 0 || arg4 < 0) {
        return 0;
    }
    if (arg4 == 0) {
        return FontWrapTextNoLimit_26d590(arg0, arg1, arg2, arg3);
    }
    saved = TextStyleGetSpaceWidth_26f5d0(arg0);
    while (TextStyleGetSpaceWidth_26f5d0(arg0) >= 5) {
        r = FontWrapText_26d5a0(arg0, arg1, arg2, arg3, arg4, &flag);
        if (flag != 0) {
            break;
        }
        TextStyleAddSpaceWidth_26f5b0(arg0, -1);
    }
    if (flag != 0) {
        *arg5 = TextStyleGetSpaceWidth_26f5d0(arg0);
    } else {
        *arg5 = saved;
    }
    TextStyleSetSpaceWidth_26f5e0(arg0, saved);
    if (flag == 0) {
        r = FontWrapTextNoLimit_26d590(arg0, arg1, arg2, arg3);
    }
    return r;
}
