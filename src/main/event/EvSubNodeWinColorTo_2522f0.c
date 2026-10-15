#include "types.h"

extern void EventCastSetWinColor_257dc0(void *, s32, void *);
extern void EventCastGetWinColor_257d50(void *, s32, f32 *);
extern void VecSub_13be40(f32 *, f32 *, f32 *);
extern void VecAdd_13be20(f32 *, f32 *, void *);
extern void sceVu0DivVector(void *, f32 *, f32);
extern u8 D_004BDDB0[];

struct Obj0 {
    u8 pad000[0x10];
    u8 m10[0x10];
    s32 m20;
};

struct Obj1 {
    u8 pad000[0x50];
    s32 m50;
    u8 pad054[0xC];
    s32 m60;
    u8 pad064[0xBC];
    u8 m120[0x10];
};

s32 EvSubNodeWinColorTo_2522f0(struct Obj0 *p0, struct Obj1 *p1)
{
    f32 v50[4];
    f32 v40[4];
    f32 v30[4];

    if (p1->m50 >= p0->m20) {
        EventCastSetWinColor_257dc0(D_004BDDB0, p1->m60, p0->m10);
        p1->m50 = 0;
        return 0;
    }
    if (p1->m50 <= 0) {
        EventCastGetWinColor_257d50(D_004BDDB0, p1->m60, v40);
        VecSub_13be40(v50, (f32 *)p0->m10, v40);
        sceVu0DivVector(p1->m120, v50, (f32)p0->m20);
    } else {
        EventCastGetWinColor_257d50(D_004BDDB0, p1->m60, v30);
        VecAdd_13be20(v30, v30, p1->m120);
        EventCastSetWinColor_257dc0(D_004BDDB0, p1->m60, v30);
    }
    p1->m50 = p1->m50 + 1;
    return 1;
}
