#include "types.h"
typedef unsigned __int128 u128_14ab70;
struct S14ab70 { u8 pad000[0x20]; u128_14ab70 m20; };
struct D14ab70 { u128_14ab70 q00; u128_14ab70 q10; };

s32 MeshPktWriteColourMaybe_14ab70(struct S14ab70 *src, struct D14ab70 *dst)
{
    dst->q00 = 0;
    *(s32 *)((u8 *)dst + 0x0) = 0x60000001;
    *(s32 *)((u8 *)dst + 0x8) = 0x01000101;
    *(s32 *)((u8 *)dst + 0xC) = 0x6C010052;
    dst->q10 = src->m20;
    return 2;
}
