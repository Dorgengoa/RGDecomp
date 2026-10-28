/* rgp:protos */
#define RGP_SELF_MemStackHeapAllocBackAligned_14dd20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on

void *MemStackHeapAllocBackAligned_14dd20(void *arg0, s32 arg1, u32 arg2)
{
    u8 *n;
    u32 need;
    u8 *blk;
    u8 *top;
    u8 *data;
    u32 r;
    s32 sz;
    s32 av;

    n = *(u8 **)(*(u8 **)((u8 *)arg0 + 0x1C) + 4);
    need = arg1 + arg2;
    while (n != NULL) {
        av = (*(s32 *)n - (s32)(n + *(s32 *)(n + 8) * 16)) / 16;
        if (need <= (u32)av) {
            top = *(u8 **)n;
            blk = top - need * 16;
            *(u8 **)blk = top;
            data = blk + 16;
            *(u8 **)n = blk;
            *(u8 **)(blk + 4) = n;
            *(u8 **)(*(u8 **)blk + 4) = blk;
            *(u32 *)(blk + 8) = need;
            if ((r = ((u32)data >> 4) % arg2) != 0) {
                data += (arg2 - r) * 16;
            }
            sz = (data - blk) / 16;
            *(s32 *)(blk + 0xC) = sz;
            *(s32 *)(data - 4) = sz;
            return data;
        }
        n = *(u8 **)(n + 4);
    }
    return NULL;
}
