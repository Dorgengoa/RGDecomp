#include "types.h"

extern void * UiGetWidgetText_28f620(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
};

struct Obj0 *UiSetTextPos_28f5d0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    struct Obj0 *r0;

    r0 = UiGetWidgetText_28f620(p0, p1, p4);
    if (r0 != 0) {
        r0->m00 = p2;
        r0->m02 = p3;
    }
    return r0;
}
