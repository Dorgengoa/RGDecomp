#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
    s32 m1C;
};

struct Obj1 {
    s32 m00;
};

struct Obj2 {
    s32 m00;
};

void EntryGetGridSize_323bb0(struct Obj0 *p0, struct Obj1 *p1, struct Obj2 *p2)
{
    p1->m00 = p0->m18;
    p2->m00 = p0->m1C;
}
