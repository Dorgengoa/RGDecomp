/* rgp:protos */
#define RGP_SELF_NodeSetRotation_186620 1
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
    u8 pad000[0xC];
    f32 m0C;
    f32 m10;
    f32 m14;
    u8 pad018[0x18];
    s16 m30;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
};

void NodeSetRotation_186620(struct Obj0 *p0, struct Obj1 *p1)
{
    s16 t0;
    f32 t1;
    f32 t2;
    f32 t3;

    t0 = p0->m30;
    if (t0 == 0) {
        t1 = p1->m00;
        p0->m0C = t1;
        t2 = p1->m04;
        p0->m10 = t2;
        t3 = p1->m08;
        p0->m14 = t3;
        return;
    }
}
