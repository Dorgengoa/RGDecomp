/* rgp:protos */
#define RGP_SELF_ActInfoClsnPntInit_230dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    f32 m00;
    f32 m04;
    s32 m08;
    u8 m0C;
};

void ActInfoClsnPntInit_230dd0(struct Obj0 *p0, s32 p1, s32 p2, f32 fa0, f32 fa1)
{
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    if (p1 != 0) {
        p0->m00 = fa0;
        p0->m04 = fa1;
        p0->m08 = p1;
        p0->m0C = p2;
        return;
    }
}
