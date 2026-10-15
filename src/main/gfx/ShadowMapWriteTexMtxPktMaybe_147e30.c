#include "types.h"

typedef unsigned __int128 u128;

extern void MtxMul_13d240(void *, void *, void *);

s32 ShadowMapWriteTexMtxPktMaybe_147e30(u8 *p0, u8 *p1, u8 *p2)
{
    u128 tmp[4];

    *(u128 *)p1 = 0;
    *(u32 *)(p1 + 0x8) = 0x1000101;
    MtxMul_13d240(tmp, p0 + 0x3B50, p2 + 0x30);
    *(u128 *)(p1 + 0x10) = tmp[0];
    *(u128 *)(p1 + 0x20) = tmp[1];
    *(u128 *)(p1 + 0x30) = tmp[2];
    *(u128 *)(p1 + 0x40) = tmp[3];
    *(u32 *)(p1 + 0xC) = 0x6C04001E;
    *(u32 *)(p1 + 0x0) = 0x60000004;
    return 5;
}
