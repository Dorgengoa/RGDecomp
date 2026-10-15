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
};

struct Obj1 {
    u128 m00;
};

void QwordCopy_14cee0(s32 p0, s32 p1, s32 p2)
{
    struct Obj1 *l0;
    struct Obj0 *l1;
    s32 l2;
    u128 t0;

    l0 = (struct Obj1 *)p0;
    l1 = (struct Obj0 *)p1;
    l2 = (p2 + -1);
    while (l2 >= 0) {
        t0 = l1->m00;
        l0->m00 = t0;
        l0 = (struct Obj1 *)((u8 *)l0 + 0x10);
        l1 = (struct Obj0 *)((u8 *)l1 + 0x10);
        l2 = (l2 + -1);
    }
}
