/* rgp:protos */
#define RGP_SELF_FontGetCharWidth_26f4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
extern u8 D_0044E851[0x400];

u8 FontGetCharWidth_26f4c0(s32 arg0, s32 arg1)
{
    s32 temp_4;
    u8 var_2;

    if (!(arg1 & 0xFFFF)) {
        return TextStyleGetSpaceWidth_26f5d0((void *)arg0);
    }
    temp_4 = ((signed char)TextStyleGetFontType_26ede0((void *)arg0)) & 0xFF;
    var_2 = *(D_0044E851 + ((arg1 & 0xFFFF) * 4) + temp_4);
    if (temp_4 == 0) {
        var_2 -= 1;
    }
    return var_2;
}
