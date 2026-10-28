/* rgp:protos */
#define RGP_SELF_FontMeasureGrowMax_26dd00 1
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
};

struct Obj1 {
    s32 m00;
};

void FontMeasureGrowMax_26dd00(struct Obj0 *p0, struct Obj1 *p1, s32 p2, s32 p3)
{
    s32 old0;
    s32 old1;

    if ((p0->m00 < p2) != 0) {
        old0 = p0->m00;
        p0->m00 = p2;
    }
    if (p1->m00 < p3) {
        old1 = p1->m00;
        p1->m00 = p3;
    }
}
