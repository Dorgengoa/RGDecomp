#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1E];
    s16 m1E;
    u8 pad020[0x2];
    s16 m22;
};

void DoorCursorFadeOut_304a10(struct Obj0 *p0)
{
    s16 t0;

    t0 = p0->m1E;
    if (t0 != 0) {
        if (t0 == 6) {
            p0->m1E = 0;
        } else {
            p0->m1E = 7;
        }
        p0->m22 = 0;
    }
}
