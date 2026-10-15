#include "types.h"

extern void * UiGetWidgetText_28f620(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 UiSetTextColor_290a40(s32 p0, s32 p1, s32 p2, s32 p3)
{
    struct Obj0 *r0;
    s32 rv1;

    r0 = UiGetWidgetText_28f620(p0, p1, p3);
    rv1 = 1;
    if (r0 == 0) {
        rv1 = 0;
    } else {
        r0->m0C = p2;
        rv1 = 1;
    }
    return rv1;
}
