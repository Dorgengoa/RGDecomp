#include "types.h"

extern void *PoolAllocAppendNode_2543f0(s32);
extern void sceVu0CopyVector(void *, const void *);
extern void strcpy(void *, const void *);
extern u8 D_0045EDA0[];

struct Obj0 {
    s32 m00;
    u8 pad004[0xC];
    f32 m10;
    f32 m14;
    f32 m18;
    u8 pad01C[0x4];
    u8 m20[0x10];
    s32 m30;
    s32 m34;
    u8 pad038[0x4];
    u8 m3C[0x4];
};

void EventCameraNodeAddOrbitCastSet_253b10(s32 p0, s32 p1, const void *p2, s32 p3, const void *p4,
                  f32 fa0, f32 fa1, f32 fa2)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_2543f0(p0);
    if (r0 != 0) {
        r0->m00 = 0x16;
        sceVu0CopyVector(r0->m20, p2);
        r0->m10 = fa0;
        r0->m14 = fa1;
        r0->m18 = fa2;
        r0->m30 = p1;
        r0->m34 = p3;
        if (p4 != 0) {
            strcpy(r0->m3C, p4);
        } else {
            strcpy(r0->m3C, D_0045EDA0);
        }
    }
}
