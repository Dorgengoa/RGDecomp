/* rgp:protos */
#define RGP_SELF_MovieFrameBufSize_1d5570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 MovieFrameBufSize_1d5570(s32 p0, s32 p1, s32 p2)
{
    s32 a;
    s32 b;

    a = p1 / 16;
    b = (a * p2) / 16;
    return ((((((b * 3) * 2) + 0x6E) * 4) + 0x3F) / 64) << 8;
}
