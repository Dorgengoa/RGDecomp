#include "types.h"

typedef unsigned __int128 u128;

s32 DrawPktBuildCameraMatrix_1486c0(u8 *p0, u8 *p1)
{
    u8 *q;
    u8 *r;

    q = *(u8 **)(p0 + 0xF20);
    if (q == 0) {
        return 0;
    }
    r = q + 0x14;
    if (r == 0) {
        return 0;
    }
    *(u128 *)p1 = 0;
    *(u32 *)(p1 + 0x8) = 0x1000101;
    *(u128 *)(p1 + 0x10) = *(u128 *)(q + 0xB0);
    *(u128 *)(p1 + 0x20) = *(u128 *)(q + 0xC0);
    *(u128 *)(p1 + 0x30) = *(u128 *)(q + 0xD0);
    *(u128 *)(p1 + 0x40) = *(u128 *)(q + 0xE0);
    *(u128 *)(p1 + 0x50) = *(u128 *)(q + 0x170);
    *(u32 *)(p1 + 0xC) = 0x6C050018;
    *(u32 *)(p1 + 0x0) = 0x60000005;
    return 6;
}
