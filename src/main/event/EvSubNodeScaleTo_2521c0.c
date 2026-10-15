#include "types.h"

extern void EventCastSetScale_257fb0(void *, s32, f32, f32, f32);
extern void EventCastGetScale_257eb0(void *, s32, f32 *);
extern void VecSub_13be40(f32 *, f32 *, f32 *);
extern void VecAdd_13be20(f32 *, f32 *, void *);
extern void sceVu0DivVector(void *, f32 *, f32);
extern u8 D_004BDDB0[];

struct Obj0 {
    u8 pad000[0x10];
    f32 m10;
    f32 m14;
    f32 m18;
    u8 pad01C[0x4];
    s32 m20;
};

struct Obj1 {
    u8 pad000[0x54];
    s32 m54;
    u8 pad058[0x8];
    s32 m60;
    u8 pad064[0xCC];
    u8 m130[0x10];
};

/* Guard loads p0->m20 first, so the compare is written with it on the left. */
s32 EvSubNodeScaleTo_2521c0(struct Obj0 *p0, struct Obj1 *p1)
{
    f32 v50[4];
    f32 v40[4];
    f32 v30[4];

    if (p1->m54 >= p0->m20) {
        EventCastSetScale_257fb0(D_004BDDB0, p1->m60, p0->m10, p0->m14, p0->m18);
        p1->m54 = 0;
        return 0;
    }
    if (p1->m54 <= 0) {
        EventCastGetScale_257eb0(D_004BDDB0, p1->m60, v40);
        VecSub_13be40(v50, &p0->m10, v40);
        sceVu0DivVector(p1->m130, v50, (f32)p0->m20);
    } else {
        EventCastGetScale_257eb0(D_004BDDB0, p1->m60, v30);
        VecAdd_13be20(v30, v30, p1->m130);
        EventCastSetScale_257fb0(D_004BDDB0, p1->m60, v30[0], v30[1], v30[2]);
    }
    p1->m54 = p1->m54 + 1;
    return 1;
}
