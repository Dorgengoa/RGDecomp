#include "types.h"

typedef unsigned __int128 u128;

s32 ModelMeshMode1WriteVuHeaderMaybe_1646a0(u8 *src, u8 *dst, u8 *o)
{
    *(u32 *)(dst + 0x00) = 0x60000008;
    *(u32 *)(dst + 0x04) = 0;
    *(u32 *)(dst + 0x08) = *(u32 *)(src + 0x00) | 0x3000000;
    *(u32 *)(dst + 0x0C) = *(u32 *)(src + 0x04) | 0x2000000;
    *(u128 *)(dst + 0x10) = 0;
    *(u32 *)(dst + 0x10) = 0x1000101;
    *(u32 *)(dst + 0x1C) = 0x6C04004C;
    *(u128 *)(dst + 0x20) = 0;
    *(u32 *)(dst + 0x20) = *(u32 *)(src + 0x08);
    *(u32 *)(dst + 0x24) = *(u32 *)(src + 0x0C);
    *(u32 *)(dst + 0x28) = 0;
    *(u128 *)(dst + 0x30) = *(u128 *)(src + 0x70);
    *(u32 *)(dst + 0x3C) = (*(u32 *)(src + 0x64) ^ 0x20) != 0;
    *(u128 *)(dst + 0x40) = *(u128 *)(src + 0x80);
    *(u128 *)(dst + 0x50) = *(u128 *)(src + 0x90);
    *(u128 *)(dst + 0x60) = 0;
    *(u128 *)(dst + 0x70) = 0;
    *(u32 *)(dst + 0x68) = 0x6C010051;
    *(u32 *)(dst + 0x6C) = *(u32 *)(o + 0x00);
    *(f32 *)(dst + 0x78) = *(f32 *)(o + 0x04);
    *(u32 *)(dst + 0x7C) = 0x6C01002A;
    *(u128 *)(dst + 0x80) = *(u128 *)(o + 0x10);
    return 9;   /* addiu $2,$0,0x9 materialised and left live at the jr */
}
