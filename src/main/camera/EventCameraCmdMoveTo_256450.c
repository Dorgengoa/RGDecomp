#include "types.h"

extern void sceVu0CopyVector(void *, const void *);
extern void VecSub_13be40(f32 *, const f32 *, const f32 *); /* dst = a - b */
extern void VecAdd_13be20(f32 *, const f32 *, const f32 *); /* dst = a + b */
extern void sceVu0DivVector(f32 *, const f32 *, f32);

struct Obj0 {
    u8 pad000[0x10];
    f32 m10[4];
    f32 m20[4];
    s32 m30;
};

struct Obj1 {
    u8 pad000[0x38];
    s32 m38;
    u8 pad03C[0x14];
    f32 m50[4];
    f32 m60[4];
    u8 pad070[0x60];
    f32 mD0[4];
    f32 mE0[4];
    u8 pad0F0[0x60];
    f32 m150[4];
    f32 m160[4];
};

s32 EventCameraCmdMoveTo_256450(struct Obj0 *p0, struct Obj1 *p1)
{
    f32 v30[4];

    if (p1->m38 >= p0->m30) {
        sceVu0CopyVector(p1->m50, p0->m10);
        sceVu0CopyVector(p1->m60, p0->m20);
        p1->m38 = 0;
        return 0;
    }
    if (p1->m38 <= 0) {
        VecSub_13be40(v30, p0->m10, p1->m50);
        sceVu0DivVector(p1->mD0, v30, (f32)p0->m30);
        p1->mD0[3] = 1.0f;
        VecSub_13be40(v30, p0->m20, p1->m60);
        sceVu0DivVector(p1->mE0, v30, (f32)p0->m30);
        p1->mE0[3] = 1.0f;
        sceVu0CopyVector(p1->m150, p1->mD0);
        sceVu0CopyVector(p1->m160, p1->mE0);
    } else {
        VecAdd_13be20(p1->m50, p1->m50, p1->mD0);
        p1->m50[3] = 1.0f;
        VecAdd_13be20(p1->m60, p1->m60, p1->mE0);
        p1->m60[3] = 1.0f;
    }
    p1->m38 = p1->m38 + 1;
    return 1;
}
