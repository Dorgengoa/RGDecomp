#include "types.h"

extern s32 SplinePathPairReset_257030(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventCameraCmdSplineReset_2553f0(s32 p0, s32 p1)
{
    s32 r;

    r = SplinePathPairReset_257030((p1 + 0x1C0));
    return 0;
}
