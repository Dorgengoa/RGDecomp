#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

struct Obj0;
struct Obj1;

struct Obj0 {
    u128 m00;
    u128 m10;
    u128 m20;
    u128 m30;
    u128 m40;
};

struct Obj1 {
    u128 m00;
    u128 m10;
    u128 m20;
    u128 m30;
    u128 m40;
};

struct Obj1 *CopyQword5_1a8670(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->m00 = p1->m00;
    p0->m10 = p1->m10;
    p0->m20 = p1->m20;
    p0->m30 = p1->m30;
    p0->m40 = p1->m40;
    return p0;
}
