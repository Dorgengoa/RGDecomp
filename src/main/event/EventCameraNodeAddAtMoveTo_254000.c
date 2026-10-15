#include "types.h"

extern void *PoolAllocAppendNode_254450(s32);
extern void sceVu0CopyVector(void *, const void *);

struct Obj0 {
    s32 m00;
    u8 pad004[0x1C];
    u8 m20[0x10];
    s32 m30;
};

void EventCameraNodeAddAtMoveTo_254000(s32 p0, const void *p1, s32 p2)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_254450(p0);
    if (r0 != 0) {
        r0->m00 = 6;
        sceVu0CopyVector(r0->m20, p1);
        r0->m30 = p2;
    }
}
