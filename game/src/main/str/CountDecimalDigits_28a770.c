/* rgp:protos */
#define RGP_SELF_CountDecimalDigits_28a770 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
#pragma inline_intrinsics off

extern s32 abs(s32 x);

s32 CountDecimalDigits_28a770(s32 arg0)
{
    s32 count;
    s32 n;

    count = 1;
    n = abs(arg0);
    while (n >= 10) {
        n = n / 10;
        count++;
    }
    return count;
}
