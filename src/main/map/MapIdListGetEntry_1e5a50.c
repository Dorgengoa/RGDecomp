#include "types.h"

u8 *MapIdListGetEntry_1e5a50(u8 *base, u32 i)
{
    u8 *r;

    if (i >= 0x14) {
        r = 0;
    } else {
        r = base + i * 8;
    }
    return r;
}
