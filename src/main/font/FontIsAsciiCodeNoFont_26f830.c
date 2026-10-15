#include "types.h"

s32 FontIsAsciiCodeNoFont_26f830(s32 k)
{
    s32 r;

    if (k == 0xFF02) {
        r = 1;
    } else if (k < 0) {
        r = 0;
    } else {
        r = k < 0x6A;
    }
    return r;
}
