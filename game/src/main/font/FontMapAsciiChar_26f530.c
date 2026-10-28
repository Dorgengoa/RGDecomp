/* rgp:protos */
#define RGP_SELF_FontMapAsciiChar_26f530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0044E850[];

s32 FontMapAsciiChar_26f530(s64 arg0)
{
    s32 var_2;
    s64 temp_6;
    u8 *temp_4;

    temp_6 = (s8)arg0;
    if (temp_6 == 10) {
        return -2;
    }
    if (temp_6 == 32) {
        return 0;
    }
    var_2 = 0;
    while (*(u8 *)(D_0044E850 + (var_2 * 4) + 1) != 0) {
        temp_4 = D_0044E850 + (var_2 * 4);
        if (temp_6 == *(s8 *)temp_4) {
            return var_2;
        }
        var_2 += 1;
    }
    return -1;
}
