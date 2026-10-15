#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    f32 m00;
    f32 m04;
    f32 m08;
};

struct Obj1 {
    f32 m00;
};

struct Obj2 {
    f32 m00;
};

struct Obj3 {
    f32 m00;
};

void Vec3Unpack_32b080(struct Obj0 *p0, struct Obj1 *p1, struct Obj2 *p2, struct Obj3 *p3)
{
    p1->m00 = p0->m00;
    p2->m00 = p0->m04;
    p3->m00 = p0->m08;
}
