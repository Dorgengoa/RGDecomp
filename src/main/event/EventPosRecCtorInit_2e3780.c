#include "types.h"

extern void EventRecCtor_2e5860(s32);
extern s32 EventPosRecInit_2e36c0(s32, s32, s32, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventPosRecCtorInit_2e3780(s32 p0, s32 p1, s32 p2, f32 fa0, f32 fa1, f32 fa2)
{
    s32 r1;

    EventRecCtor_2e5860(p0);
    r1 = EventPosRecInit_2e36c0(p0, p1, p2, fa0, fa1, fa2);
    return p0;
}
