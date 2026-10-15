#include "types.h"

extern void EventRecCtor_2e5860(s32);
extern s32 EventScriptRecReset_2e3a90(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventScriptRecCtor_2e3ac0(s32 p0)
{
    s32 r1;

    EventRecCtor_2e5860(p0);
    r1 = EventScriptRecReset_2e3a90(p0);
    return p0;
}
