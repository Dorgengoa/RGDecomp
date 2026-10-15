#include "types.h"

extern void * UiFindWidget_290460(s32, s32);

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x24];
    struct Obj1 *m24;
};

struct Obj1 {
    s16 m00;
    s16 m02;
};

s32 UiSetFirstSubItemPos_2911e0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    struct Obj0 *r0;
    struct Obj1 *t0;

    r0 = UiFindWidget_290460(p0, p1);
    if (r0 == 0) {
        return 0;
    }
    t0 = r0->m24;
    if (t0 == 0) {
        return 0;
    }
    if (p2 >= 0) {
        t0->m00 = p2;
    }
    if (p3 >= 0) {
        t0->m02 = p3;
    }
    return 1;
}
