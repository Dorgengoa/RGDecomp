/* rgp:protos */
#define RGP_SELF_JudgeObjectGetVelZero_313f80 1
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
    s32 m0C;
};

void JudgeObjectGetVelZero_313f80(s32 p0, struct Obj0 *p1)
{
    p1->m00 = 0;
    p1->m04 = 0;
    p1->m08 = 0;
    p1->m0C = 0;
}
