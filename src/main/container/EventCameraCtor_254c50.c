#include "types.h"

extern void SplinePathPairCtor_257120(s32);
extern s32 EventCameraClear_254c30(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventCameraCtor_254c50(s32 p0)
{
    s32 r1;

    SplinePathPairCtor_257120((p0 + 0x1C0));
    r1 = EventCameraClear_254c30(p0);
    return p0;
}
