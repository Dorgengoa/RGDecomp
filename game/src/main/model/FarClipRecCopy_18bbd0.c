/* rgp:protos */
#define RGP_SELF_FarClipRecCopy_18bbd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    f32 m0C;
    f32 m10;
    s32 m14;
    f32 m18;
    f32 m1C;
    f32 m20;
};

struct Obj1 {
    s32 m00;
    s32 m04;
    s32 m08;
    f32 m0C;
    f32 m10;
    s32 m14;
    f32 m18;
    f32 m1C;
    f32 m20;
};

struct Obj1 *FarClipRecCopy_18bbd0(struct Obj1 *p0, struct Obj0 *p1)
{
    p0->m00 = p1->m00;
    p0->m04 = p1->m04;
    p0->m08 = p1->m08;
    p0->m0C = p1->m0C;
    p0->m10 = p1->m10;
    p0->m14 = p1->m14;
    p0->m18 = p1->m18;
    p0->m1C = p1->m1C;
    p0->m20 = p1->m20;
    return p0;
}
