#include "types.h"

extern void NavGraphStorageRelease_3114b0(s32);
extern void NavGraphReset_3111a0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void NavGraphRelease_311170(s32 p0)
{
    NavGraphStorageRelease_3114b0((p0 + 0x90));
    NavGraphReset_3111a0(p0);
}
