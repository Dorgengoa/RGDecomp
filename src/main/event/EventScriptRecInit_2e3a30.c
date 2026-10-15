#include "types.h"

extern void EventScriptRecReset_2e3a90(void *);
extern void EventRecInitWithKey_2e5800(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    s32 m14;
};

void EventScriptRecInit_2e3a30(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    EventScriptRecReset_2e3a90(p0);
    EventRecInitWithKey_2e5800(p0, p1);
    p0->m10 = p2;
    p0->m14 = p3;
}
