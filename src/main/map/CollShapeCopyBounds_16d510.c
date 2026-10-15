#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x10];
    u128 m10;
    u128 m20;
};

struct Obj1 {
    u8 pad000[0x10];
    u128 m10;
    u128 m20;
};

void CollShapeCopyBounds_16d510(struct Obj0 *p0, struct Obj1 *p1)
{
    p1->m10 = p0->m10;
    p1->m20 = p0->m20;
}
