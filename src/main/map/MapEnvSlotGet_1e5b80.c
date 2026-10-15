#include "types.h"

u8 *MapEnvSlotGet_1e5b80(u8 *base, u32 i)
{
    u8 *r;

    if (i >= 3) {
        r = 0;
    } else {
        r = base + i * 32;
    }
    return r;
}
