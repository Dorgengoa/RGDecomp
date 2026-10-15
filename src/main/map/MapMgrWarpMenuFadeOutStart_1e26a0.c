#include "types.h"

extern void WarpMenuFadeOutStart_39dd20(s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapMgrWarpMenuFadeOutStart_1e26a0(s32 p0, s32 p1)
{
    WarpMenuFadeOutStart_39dd20((p0 + 0x18B0), ((f32)p1));
}
