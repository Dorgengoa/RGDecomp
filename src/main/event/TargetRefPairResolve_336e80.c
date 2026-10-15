#include "types.h"

extern void TargetRefResolve_2e5ed0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 TargetRefPairResolve_336e80(s32 p0, s32 p1)
{
    TargetRefResolve_2e5ed0(p0, 0);
    TargetRefResolve_2e5ed0((p0 + 0x30), p1);
    return 1;
}
