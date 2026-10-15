#include "types.h"

extern void * UiFindWidget_290460(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x24];
    s32 m24;
};

struct Obj1 {
    s16 m00;
};

struct Obj0 *UiSetWidgetSubItemValue_291250(s32 p0, s32 p1, s32 p2, s64 p3)
{
    struct Obj0 *r0;
    s32 t0;
    struct Obj1 *l2;
    s32 l1;

    r0 = UiFindWidget_290460(p0, p1);
    if (r0 == 0) {
        goto out;
    }
    t0 = r0->m24;
    l2 = (struct Obj1 *)t0;
    if (t0 == 0) {
        goto out;
    }
    l1 = 0;
    while (l2->m00 != -1) {
        l2 = (struct Obj1 *)((u8 *)l2 + 0x20);
        l1 = (l1 + 1);
    }
    if (l1 >= (p2 + 1)) {
        *(s64 *)((u8 *)(p2 << 5) + t0 + 0x8) = p3;
    }
out:
    return r0;
}
