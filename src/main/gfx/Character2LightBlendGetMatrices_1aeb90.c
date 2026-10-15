#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x630];
    u128 m630;
    u128 m640;
    u128 m650;
    u128 m660;
    u8 pad670[0x80];
    u128 m6F0;
    u128 m700;
    u128 m710;
    u128 m720;
};

struct Obj1 {
    u128 m00;
    u128 m10;
    u128 m20;
    u128 m30;
};

struct Obj2 {
    u128 m00;
    u128 m10;
    u128 m20;
    u128 m30;
};

void Character2LightBlendGetMatrices_1aeb90(struct Obj0 *p0, struct Obj1 *p1, struct Obj2 *p2)
{
    p1->m00 = p0->m630;
    p1->m10 = p0->m640;
    p1->m20 = p0->m650;
    p1->m30 = p0->m660;
    p2->m00 = p0->m6F0;
    p2->m10 = p0->m700;
    p2->m20 = p0->m710;
    p2->m30 = p0->m720;
}
