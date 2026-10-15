#include "types.h"

extern void * UiFindWidget_290460(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
};

struct Obj0 *UiSetWidgetParent_2911a0(s32 p0, s32 p1, s32 p2)
{
    struct Obj0 *r0;

    r0 = UiFindWidget_290460(p0, p1);
    if (r0 != 0) {
        if (p2 != 0) {
            r0->m02 = p2;
        } else {
            r0->m02 = 0;
        }
    }
    return r0;
}
