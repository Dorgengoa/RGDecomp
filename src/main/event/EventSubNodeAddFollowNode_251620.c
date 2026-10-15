#include "types.h"

extern void *PoolAllocAppendNode_251e70(s32);
extern void sceVu0CopyVector(void *, const void *);
extern void strcpy(void *, const void *);

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u8 m10[0x10];
    s32 m20;
    s32 m24;
    u8 pad028[0x4];
    u8 m2C[0x4];
};

void EventSubNodeAddFollowNode_251620(s32 p0, s32 p1, const void *p2, s32 p3, const void *p4)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251e70(p0);
    if (r0 != 0) {
        r0->m00 = 0xA;
        r0->m20 = p1;
        strcpy(r0->m2C, p2);
        r0->m24 = p3;
        sceVu0CopyVector(r0->m10, p4);
    }
}
