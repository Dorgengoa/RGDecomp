#include "types.h"

extern void EventGlobalObjSubCtor_257a90(s32);
extern s32 EventGlobalObjReset_257940(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventGlobalObjCtor_257a10(s32 p0)
{
    s32 r1;

    EventGlobalObjSubCtor_257a90((p0 + 0x4C));
    r1 = EventGlobalObjReset_257940(p0);
    return p0;
}
