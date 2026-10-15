#include "types.h"

extern void TargetRefIsActive_2e6f00(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EvFollowObjIsTargetActive_2f7e30(s32 p0)
{
    TargetRefIsActive_2e6f00((p0 + 0xA0));
}
