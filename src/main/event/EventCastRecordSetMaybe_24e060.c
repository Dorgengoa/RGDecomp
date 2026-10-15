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
    u8 pad010[0x24];
    s32 m34;
};

void EventCastRecordSetMaybe_24e060(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    p0->m00 = p1;
    p0->m04 = p2;
    p0->m08 = p3;
    p0->m0C = p4;
    p0->m34 = 0;
}
