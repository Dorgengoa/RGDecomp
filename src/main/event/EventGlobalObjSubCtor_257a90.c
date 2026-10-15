#include "types.h"

extern void ListIterCtor_257ae0(s32);
extern s32 EventGlobalObjSubReset_257a50(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventGlobalObjSubCtor_257a90(s32 p0)
{
    s32 r1;

    ListIterCtor_257ae0((p0 + 4));
    r1 = EventGlobalObjSubReset_257a50(p0);
    return p0;
}
