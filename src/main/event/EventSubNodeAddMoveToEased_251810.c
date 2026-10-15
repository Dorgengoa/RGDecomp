#include "types.h"

extern void *PoolAllocAppendNode_251e70(s32);
extern void sceVu0CopyVector(void *, const void *);

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u8 m10[0x10];
    s32 m20;
    s32 m24;
    f32 m28;
};

void EventSubNodeAddMoveToEased_251810(s32 p0, const void *p1, s32 p2, s32 p3, f32 fa0)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251e70(p0);
    if (r0 != 0) {
        r0->m00 = 4;
        sceVu0CopyVector(r0->m10, p1);
        r0->m20 = p2;
        r0->m24 = p3;
        r0->m28 = fa0;
    }
}
