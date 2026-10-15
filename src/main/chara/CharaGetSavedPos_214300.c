#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4B8];
    f32 m4B8;
    f32 m4BC;
    f32 m4C0;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
    s32 m0C;
};

void CharaGetSavedPos_214300(struct Obj0 *p0, struct Obj1 *p1)
{
    p1->m00 = p0->m4B8;
    p1->m04 = p0->m4BC;
    p1->m08 = p0->m4C0;
    p1->m0C = 0x3F800000;
}
