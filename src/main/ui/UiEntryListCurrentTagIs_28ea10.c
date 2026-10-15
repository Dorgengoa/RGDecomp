#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0xC];
    struct Obj1 *m0C;
};

struct Obj1 {
    struct Obj2 *m00;
};

struct Obj2 {
    u16 m00;
};

s32 UiEntryListCurrentTagIs_28ea10(struct Obj0 *p0, s32 p1)
{
    struct Obj1 * t0;
    s32 rv0;
    struct Obj2 * t1;
    u16 t2;

    t0 = p0->m0C;
    rv0 = (t2 == (p1 & 0xFFFF));
    if (t0 == 0) {
        rv0 = 1;
    } else {
        t1 = p0->m0C->m00;
        t2 = p0->m0C->m00->m00;
        rv0 = (t2 == (p1 & 0xFFFF));
    }
    return rv0;
}
