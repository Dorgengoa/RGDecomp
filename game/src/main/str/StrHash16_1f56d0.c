/* rgp:protos */
#define RGP_SELF_StrHash16_1f56d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 StrHash16_1f56d0(s8 *str)
{
    s32 acc;
    s8 c;

    if (str == NULL) {
        return 0;
    }
    acc = 0;
    while ((c = *str) != 0) {
        str++;
        acc = (acc + ((c - 0x20) << 8) + 1) & 0xFFFF;
    }
    return acc & 0xFFFF;
}
