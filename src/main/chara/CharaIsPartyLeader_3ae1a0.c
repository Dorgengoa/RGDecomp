#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483820;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18E];
    s16 m18E;
};

struct Obj1 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 CharaIsPartyLeader_3ae1a0(struct Obj1 *p0)
{
    struct Obj0 * t0;
    s32 rv0;
    s16 t1;
    s32 t2;

    t0 = D_00483820;
    rv0 = (t2 == t1);
    if (t0 == 0) {
        rv0 = 0;
    } else {
        t1 = D_00483820->m18E;
        t2 = p0->m0C;
        rv0 = (t2 == t1);
    }
    return rv0;
}
