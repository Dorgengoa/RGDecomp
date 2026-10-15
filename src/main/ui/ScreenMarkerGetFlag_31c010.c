#include "types.h"

s32 ScreenMarkerGetFlag_31c010(u8 *base, s32 i)
{
    if (i >= 0x20) {
        i = 0x1F;
    }
    return base[i + 0x80] & 0x7F;
}
