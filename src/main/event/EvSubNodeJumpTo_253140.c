#include "types.h"

extern void sceVu0CopyVector(void *, const void *);
extern void JumpArcLerp_258f70(void *, void *, void *, f32, f32, f32);

struct Obj0 {
    u8 pad000[0x10];
    u8 m10[0x10];
    f32 m20;
    s32 m24;
};

struct Obj1 {
    u8 pad000[0x40];
    s32 m40;
    u8 pad044[0x2C];
    u8 m70[0x10];
    u8 pad080[0x80];
    u8 m100[0x10];
    u8 m110[0x10];
};

s32 EvSubNodeJumpTo_253140(struct Obj0 *p0, struct Obj1 *p1)
{
    if (p1->m40 <= 0) {
        sceVu0CopyVector(p1->m100, p1->m70);
        sceVu0CopyVector(p1->m110, p0->m10);
    }
    if (p1->m40 >= p0->m24) {
        sceVu0CopyVector(p1->m70, p1->m110);
        p1->m40 = 0;
        return 0;
    }
    p1->m40 = p1->m40 + 1;
    JumpArcLerp_258f70(p1->m70, p1->m100, p1->m110, p0->m20, (f32)p0->m24, (f32)p1->m40);
    return 1;
}
