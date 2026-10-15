#include "types.h"

extern void *PoolAllocAppendNode_251e70(s32);
extern void sceVu0CopyVector(void *, const void *);

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u8 m10[0x10];
};

void EventSubNodeAddSplineAddPoint_251760(s32 p0, const void *p1)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251e70(p0);
    if (r0 != 0) {
        r0->m00 = 7;
        sceVu0CopyVector(r0->m10, p1);
    }
}
