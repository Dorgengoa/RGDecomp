/* rgp:protos */
#define RGP_SELF_PrimBatchAddVertex_164130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/*rgp*/

void PrimBatchAddVertex_164130(u8 *p, u128 *a, u128 *b, u128 *c, u128 *d, u128 *e)
{
    s32 n;
    s32 *tag;

    n = *(s32 *)(p + 0x100);
    if (n >= *(s32 *)(p + 0xF8)) {
        if (n > 0) {
            **(s32 **)(p + 0x108) = n;
            **(s32 **)(p + 0x10C) = *(s32 *)(p + 0x100) | 0x8000;
            *(u128 *)(*(u8 **)(p + 0xF4)) = 0;
            *(s32 *)(*(u8 **)(p + 0xF4)) = 0x17000000;
            *(u8 **)(p + 0xF4) = *(u8 **)(p + 0xF4) + 0x10;
        }
        tag = *(s32 **)(p + 0x104);
        *tag = ((s32)(*(u8 **)(p + 0xF4) - (u8 *)tag) / 16 - 1) | 0x10000000;
        PrimBatchBegin_164320(p, *(s32 *)(p + 0xFC), *(s32 *)(p + 0xF8));
    }
    *((*(u128 **)(p + 0x110))++) = a[0];
    *((*(u128 **)(p + 0x110))++) = b[0];
    *((*(u128 **)(p + 0x114))++) = c[0];
    *((*(u128 **)(p + 0x114))++) = c[1];
    *((*(u128 **)(p + 0x118))++) = d[0];
    *((*(u128 **)(p + 0x11C))++) = e[0];
    *(s32 *)(p + 0x100) = *(s32 *)(p + 0x100) + 1;
}
