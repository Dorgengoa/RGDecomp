#include "types.h"

extern void SplineCtor_2578c0(s32);
extern s32 SplinePathReset_256c60(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 SplinePathCtor_256cc0(s32 p0)
{
    s32 r1;

    SplineCtor_2578c0((p0 + 0x108));
    r1 = SplinePathReset_256c60(p0);
    return p0;
}
