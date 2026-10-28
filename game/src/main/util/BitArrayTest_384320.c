/* rgp:protos */
#define RGP_SELF_BitArrayTest_384320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 BitArrayTest_384320(u8 *p0, s32 p1)
{
    s32 bit;

    bit = 1;
    bit <<= (p1 % 8);
    return ((bit & p0[p1 / 8]) != 0);
}
