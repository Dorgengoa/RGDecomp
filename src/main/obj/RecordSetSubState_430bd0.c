#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x1188];
    struct Obj1 *m1188;
};

struct Obj1 {
    u8 pad000[0xC];
    s32 m0C;
    u8 pad010[0xC];
    s32 m1C;
};

s32 RecordSetSubState_430bd0(struct Obj0 *p0, s32 p1)
{
    s32 old0;

    old0 = p0->m1188->m0C;
    p0->m1188->m0C = p1;
    if (p1 != old0) {
        p0->m1188->m1C = old0;
    }
    return 1;
}
