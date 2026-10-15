#include "types.h"
#pragma divbyzerocheck on

s32 FontGetGlyphBankType1_26f7d0(u32 a)
{
    s32 r;

    r = (s32)(a & 0xFFFF) / 0x1DC;
    if (r >= 4) {
        r = -1;
    }
    return r;
}
