#include "types.h"
#pragma divbyzerocheck on

u16 NameHash16_2e3470(s8 *p)
{
    s32 t;
    s32 sum;
    s32 count;
    s8 c;

    sum = 0;
    count = 0;
    while ((c = *p) != 0) {
        p++;
        t = ((c - 0x20) << 16) / 224;
        sum = (sum + t + count) % 0x10000;
        count++;
    }
    return sum;
}
