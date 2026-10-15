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
    u8 pad000[0x1B0];
    u128 m1B0;
};

void ProjectileSetVelVec_3194c0(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->m1B0 = p1->m00;
}
