/* rgp:protos */
#define RGP_SELF_ActInfoClsnInit_230bf0 1
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
    s16 m10;
    s16 m12;
};

void ActInfoClsnInit_230bf0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6)
{
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m10 = 0;
    p0->m0C = 0;
    p0->m12 = 0;
    if (p1 != 0) {
        p0->m00 = p1;
        p0->m04 = p2;
        p0->m08 = p3;
        if (p3 != 0) {
            p0->m10 = p4;
        }
        p0->m0C = p5;
        if (p5 != 0) {
            p0->m12 = p6;
        }
    }
}
