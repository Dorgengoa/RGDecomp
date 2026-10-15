#include "types.h"

extern s32 SplinePathReset_256c60(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvSubNodeSplineReset_2533d0(s32 p0, s32 p1)
{
    s32 r;

    r = SplinePathReset_256c60((p1 + 0x140));
    return 0;
}
