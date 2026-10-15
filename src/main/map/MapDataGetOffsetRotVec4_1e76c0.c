#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    f32 m04;
    s32 m08;
    s32 m0C;
};

struct Obj1 {
    u8 pad000[0x4C];
    f32 m4C;
};

void MapDataGetOffsetRotVec4_1e76c0(struct Obj1 *p0, struct Obj0 *p1)
{
    p1->m00 = 0;
    p1->m04 = p0->m4C;
    p1->m08 = 0;
    p1->m0C = 0x3F800000;
}
