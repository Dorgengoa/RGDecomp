/* rgp:protos */
#define RGP_SELF_ActInfoVertInitNameVec_231010 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    f32 m0C;
    f32 m10;
    f32 m14;
};

void ActInfoVertInitNameVec_231010(struct Obj0 *p0, s32 p1, f32 fa0, f32 fa1, f32 fa2)
{
    p0->m00 = 0;
    p0->m08 = -1;
    p0->m04 = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    if (p1 != 0) {
        p0->m00 = p1;
        p0->m04 = 0;
        p0->m08 = -1;
        p0->m0C = fa0;
        p0->m10 = fa1;
        p0->m14 = fa2;
        return;
    }
}
