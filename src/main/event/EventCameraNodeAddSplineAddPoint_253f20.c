#include "types.h"

extern void *PoolAllocAppendNode_254450(s32);
extern void sceVu0CopyVector(void *, const void *);

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u8 m10[0x10];
    u8 m20[0x10];
};

void EventCameraNodeAddSplineAddPoint_253f20(s32 p0, const void *p1, const void *p2)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_254450(p0);
    if (r0 != 0) {
        r0->m00 = 0xA;
        sceVu0CopyVector(r0->m10, p1);
        sceVu0CopyVector(r0->m20, p2);
    }
}
