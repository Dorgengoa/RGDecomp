#include "types.h"

typedef unsigned __int128 u128;

/* The DMA-chain "close the current tag" helper.  This same body appears
   INLINED at the head of PrimBatchAddVertex_164130, which is why it is spelled with the
   packet pointer reloaded from p+0xF4 at every step. */

void PrimBatchClose_1642a0(u8 *p)
{
    s32 n;
    s32 *tag;

    n = *(s32 *)(p + 0x100);
    if (n > 0) {
        **(s32 **)(p + 0x108) = n;
        **(s32 **)(p + 0x10C) = *(s32 *)(p + 0x100) | 0x8000;
        *(u128 *)(*(u8 **)(p + 0xF4)) = 0;
        *(s32 *)(*(u8 **)(p + 0xF4)) = 0x17000000;
        *(u8 **)(p + 0xF4) = *(u8 **)(p + 0xF4) + 0x10;
    }
    tag = *(s32 **)(p + 0x104);
    *tag = ((s32)(*(u8 **)(p + 0xF4) - (u8 *)tag) / 16 - 1) | 0x10000000;
}
