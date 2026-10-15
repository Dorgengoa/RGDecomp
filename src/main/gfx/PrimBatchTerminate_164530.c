#include "types.h"

typedef unsigned __int128 u128;

s32 PrimBatchTerminate_164530(u8 *p)
{
    u8 *q;

    *(u128 *)(*(u8 **)(p + 0xF4)) = 0;
    *(s32 *)(*(u8 **)(p + 0xF4)) = 0x60000000;
    *(s32 *)(*(u8 **)(p + 0xF4) + 8) = 0x11000000;
    q = *(u8 **)(p + 0xF4) + 0x10;
    *(u8 **)(p + 0xF4) = q;
    return (s32)(q - *(u8 **)(p + 0xF0)) / 16;
}
