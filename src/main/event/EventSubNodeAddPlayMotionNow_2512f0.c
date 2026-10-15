#include "types.h"

extern void *PoolAllocAppendNode_251db0(s32);
extern void strcpy(void *, const void *);

struct Obj0 {
    s32 m00;
    u8 pad004[0x1C];
    s32 m20;
    f32 m24;
    s32 m28;
    u8 m2C[0x4];
};

void EventSubNodeAddPlayMotionNow_2512f0(s32 p0, const void *p1, s32 p2, f32 fa0)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251db0(p0);
    if (r0 != 0) {
        r0->m00 = 0x13;
        strcpy(r0->m2C, p1);
        r0->m20 = p2;
        r0->m24 = fa0;
        r0->m28 = 0;
    }
}
