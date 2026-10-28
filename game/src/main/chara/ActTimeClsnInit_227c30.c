/* rgp:protos */
#define RGP_SELF_ActTimeClsnInit_227c30 1
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
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
};

void ActTimeClsnInit_227c30(struct Obj0 *p0, s32 p1, s32 p2, f32 fa0, f32 fa1)
{
    p0->m00 = fa0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = -1;
    p0->m04 = fa1;
    p0->m08 = p1;
    p0->m0C = p2;
}
