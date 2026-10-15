#include "types.h"

extern void TargetRefCtor_2e71f0(s32);
extern s32 TargetRefPairReset_337080(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 TargetRefPairCtor_3370c0(s32 p0)
{
    s32 r2;

    TargetRefCtor_2e71f0(p0);
    TargetRefCtor_2e71f0((p0 + 0x30));
    r2 = TargetRefPairReset_337080(p0);
    return p0;
}
