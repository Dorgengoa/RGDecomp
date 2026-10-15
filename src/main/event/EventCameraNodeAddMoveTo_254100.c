#include "types.h"

extern void *PoolAllocAppendNode_254450(s32);
extern void sceVu0CopyVector(void *, const void *);

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u8 m10[0x10];
    u8 m20[0x10];
    s32 m30;
};

/* Sibling of EventCameraNodeAddSplineAddPoint_253f20; the kind tag is 4 and there is a trailing s32. */
void EventCameraNodeAddMoveTo_254100(s32 p0, const void *p1, const void *p2, s32 p3)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_254450(p0);
    if (r0 != 0) {
        r0->m00 = 4;
        sceVu0CopyVector(r0->m10, p1);
        sceVu0CopyVector(r0->m20, p2);
        r0->m30 = p3;
    }
}
