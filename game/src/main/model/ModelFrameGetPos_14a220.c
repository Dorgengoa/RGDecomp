/* rgp:protos */
#define RGP_SELF_ModelFrameGetPos_14a220 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x14];
    struct Obj1 *m14;
    u8 pad018[0x78];
    u128 m90;
};

struct Obj1 {
    u128 m00;
};

struct Obj2 {
    u128 m00;
};

void ModelFrameGetPos_14a220(struct Obj0 *p0, struct Obj2 *p1)
{
    struct Obj1 * t0;
    u128 t1;
    u128 t2;

    t0 = p0->m14;
    if (t0 != 0) {
        t1 = p0->m14->m00;
        p1->m00 = t1;
    } else {
        t2 = p0->m90;
        p1->m00 = t2;
    }
}
