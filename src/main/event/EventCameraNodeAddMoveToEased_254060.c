#include "types.h"

extern void *PoolAllocAppendNode_254450(s32);
extern void sceVu0CopyVector(void *, const void *);

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    u8 m10[0x10];
    u8 m20[0x10];
    s32 m30;
    s32 m34;
    f32 m38;
};

void EventCameraNodeAddMoveToEased_254060(s32 p0, const void *p1, const void *p2, s32 p3, s32 p4, f32 fa0)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_254450(p0);
    if (r0 != 0) {
        r0->m00 = 5;
        sceVu0CopyVector(r0->m10, p1);
        sceVu0CopyVector(r0->m20, p2);
        r0->m30 = p3;
        r0->m34 = p4;
        r0->m38 = fa0;
    }
}
