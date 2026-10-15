#pragma divbyzerocheck on
#include "types.h"

typedef struct FreeNode {
    struct FreeNode *next;
    struct FreeNode *prev;
    u32 field8;
    u32 fieldC;
} FreeNode;

void *MemStackHeapAllocFrontAligned_14dde0(void *arg0, FreeNode *arg1, u32 arg2)
{
    FreeNode *node;
    FreeNode *blk;
    u32 size;
    u8 *p;
    u32 r;
    s32 n;

    node = *(FreeNode **)((u8 *)arg0 + 0x18);
    size = (u32)arg1 + arg2;
    while ((arg1 = node->next) != NULL) {
        blk = (FreeNode *)((u8 *)node + node->field8 * 0x10);
        if (size <= (u32)(((u8 *)arg1 - (u8 *)blk) / 0x10)) {
            p = (u8 *)blk + 0x10;
            blk->next = arg1;
            node->next = blk;
            blk->prev = node;
            blk->next->prev = blk;
            blk->field8 = size;
            r = ((u32)p >> 4) % arg2;
            if (r != 0) {
                p += (arg2 - r) * 0x10;
            }
            n = (p - (u8 *)blk) / 0x10;
            blk->fieldC = n;
            *(u32 *)(p - 4) = n;
            return p;
        }
        node = arg1;
    }
    return NULL;
}
