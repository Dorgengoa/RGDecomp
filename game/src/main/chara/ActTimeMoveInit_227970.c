/* rgp:protos */
#define RGP_SELF_ActTimeMoveInit_227970 1
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
    f32 m08;
    f32 m0C;
    f32 m10;
};

void ActTimeMoveInit_227970(struct Obj0 *p0, f32 fa0, f32 fa1, f32 fa2, f32 fa3, f32 fa4)
{
    p0->m00 = fa0;
    p0->m04 = fa1;
    p0->m08 = fa2;
    p0->m0C = fa3;
    p0->m10 = fa4;
}
