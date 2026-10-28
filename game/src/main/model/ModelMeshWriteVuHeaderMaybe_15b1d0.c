/* rgp:protos */
#define RGP_SELF_ModelMeshWriteVuHeaderMaybe_15b1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Fills a 0x90-byte GS/renderer packet.  The three 0x6C0100xx / 0x6C04004C
   constants share one `lui 0x6C01`.  Returns 9. */

typedef rg_u128 u128;

s32 ModelMeshWriteVuHeaderMaybe_15b1d0(u8 *a, u8 *b, u8 *c)
{
    *(u32 *)(b + 0x00) = 0x60000008;
    *(u32 *)(b + 0x04) = 0;
    *(u32 *)(b + 0x08) = *(u32 *)(a + 0x00) | 0x03000000;
    *(u32 *)(b + 0x0C) = *(u32 *)(a + 0x04) | 0x02000000;
    *(u128 *)(b + 0x10) = 0;
    *(u32 *)(b + 0x10) = 0x01000101;
    *(u32 *)(b + 0x1C) = 0x6C04004C;
    *(u128 *)(b + 0x20) = 0;
    *(u32 *)(b + 0x20) = *(u32 *)(a + 0x08);
    *(u32 *)(b + 0x24) = *(u32 *)(a + 0x0C);
    *(u32 *)(b + 0x28) = *(u32 *)(a + 0x124);
    *(u128 *)(b + 0x30) = *(u128 *)(a + 0x70);
    *(u32 *)(b + 0x3C) = (*(u32 *)(a + 0x64) ^ 0x20) != 0;
    *(u128 *)(b + 0x40) = *(u128 *)(a + 0x90);
    *(u128 *)(b + 0x50) = *(u128 *)(a + 0xA0);
    *(u128 *)(b + 0x60) = 0;
    *(u128 *)(b + 0x70) = 0;
    *(u32 *)(b + 0x68) = 0x6C010051;
    *(u32 *)(b + 0x6C) = *(u32 *)(c + 0x00);
    *(f32 *)(b + 0x78) = *(f32 *)(c + 0x04);
    *(u32 *)(b + 0x7C) = 0x6C01002A;
    *(u128 *)(b + 0x80) = *(u128 *)(c + 0x10);
    return 9;
}
