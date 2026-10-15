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
    u8 pad000[0x90];
    u128 m90;
    u8 pad0A0[0x10];
    s32 mB0;
};

void MenuWinMoveTo_26c220(struct Obj1 *p0, struct Obj0 *p1, s32 p2)
{
    p0->m90 = p1->m00;
    p0->mB0 = p2;
}
