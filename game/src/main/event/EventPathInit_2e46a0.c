/* rgp:protos */
#define RGP_SELF_EventPathInit_2e46a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s16 m0C;
    s16 m0E;
};

void EventPathInit_2e46a0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 l0;
    s32 t0;
    s16 r1;
    s16 t1;

    p0->m00 = p1;
    p0->m04 = p2;
    p0->m0E = 0;
    p0->m08 = p3;
    if (p3 != 0) {
        p0->m0C = p4;
        l0 = 0;
        while (l0 < p0->m0C) {
            t0 = p0->m08;
            r1 = ((short)EventPathSegGetLength_2e4770((t0 + (l0 << 3))));
            t1 = p0->m0E;
            p0->m0E = (t1 + r1);
            l0 = (l0 + 1);
        }
        return;
    }
}
