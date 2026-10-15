#include "types.h"

extern f32 MapDataGetColorR_1e75d0(s32);
extern f32 MapDataGetColorG_1e7590(s32);
extern f32 MapDataGetColorB_1e7550(s32);
extern f32 MapDataGetColorA_1e7510(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    f32 m00;
    f32 m04;
    f32 m08;
    f32 m0C;
};

f32 MapDataGetColorVec4_1e7610(s32 p0, struct Obj0 *p1)
{
    f32 r0;
    f32 r1;
    f32 r2;
    f32 r3;

    r0 = MapDataGetColorR_1e75d0(p0);
    p1->m00 = r0;
    r1 = MapDataGetColorG_1e7590(p0);
    p1->m04 = r1;
    r2 = MapDataGetColorB_1e7550(p0);
    p1->m08 = r2;
    r3 = MapDataGetColorA_1e7510(p0);
    p1->m0C = r3;
    return r3;
}
