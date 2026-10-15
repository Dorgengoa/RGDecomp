#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x8];
    f32 m08;
    f32 m0C;
};

struct Obj1 {
    f32 m00;
};

struct Obj2 {
    f32 m00;
};

void EntryGetOrigin_323b10(struct Obj0 *p0, struct Obj1 *p1, struct Obj2 *p2)
{
    p1->m00 = p0->m08;
    p2->m00 = p0->m0C;
}
