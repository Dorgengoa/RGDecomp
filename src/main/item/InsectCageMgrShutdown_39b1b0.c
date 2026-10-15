#include "types.h"

extern void InsectCageMgrReleaseAll_39a2e0(s32);
extern void InsectCageMgrReset_39b1e0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void InsectCageMgrShutdown_39b1b0(s32 p0)
{
    InsectCageMgrReleaseAll_39a2e0(p0);
    InsectCageMgrReset_39b1e0(p0);
}
