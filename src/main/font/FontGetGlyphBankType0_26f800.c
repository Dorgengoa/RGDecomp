#include "types.h"
#pragma divbyzerocheck on

s32 FontGetGlyphBankType0_26f800(u32 a)
{
    s32 r;

    r = (s32)(a & 0xFFFF) / 0x2A0;
    if (r > 0) {
        r = -1;
    }
    return r;
}
