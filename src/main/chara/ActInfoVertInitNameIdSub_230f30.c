#include "types.h"

/* Store order is 0x00, 0x08, 0x04, 0x0C, 0x10, 0x14 -- read off the listing,
   not assumed.  The three `swc1 $f0` in the block are a CHAINED assignment. */

typedef struct {
    s32 m00;
    s32 m04;
    s32 m08;
    f32 m0C;
    f32 m10;
    f32 m14;
} Slot;

void ActInfoVertInitNameIdSub_230f30(Slot *o, s32 a, s32 b, s32 c)
{
    f32 z = 0.0f;

    o->m00 = 0;
    o->m08 = -1;
    o->m04 = 0;
    o->m0C = 0.0f;
    o->m10 = 0.0f;
    o->m14 = 0.0f;
    if (a != 0) {
        o->m00 = a;
        o->m04 = c;
        o->m08 = b;
        o->m0C = z;
        o->m10 = z;
        o->m14 = z;
    }
}
