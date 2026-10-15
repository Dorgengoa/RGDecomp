#include "types.h"

/* Allocator wrapper family (0x250f60-0x254060): alloc, tag, fill.
   Return is VOID: the pointer lives in $16 and $v0 is clobbered by the
   trailing call, so retail cannot be returning it. */

extern void *PoolAllocAppendNode_251cf0(s32);
extern void sceVu0CopyVector(void *, const void *);

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u8 m10[0x10];
    s32 m20;
};

void EventSubNodeAddWinColorTo_250f60(s32 p0, const void *p1, s32 p2)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251cf0(p0);
    if (r0 != 0) {
        r0->m00 = 0x21;
        sceVu0CopyVector(r0->m10, p1);
        r0->m20 = p2;
    }
}
