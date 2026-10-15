#include "types.h"

extern s32 MapCaptionRelease_33fa10(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapMgrCaptionRelease_1e2d10(s32 p0)
{
    s32 r;

    r = MapCaptionRelease_33fa10((p0 + 0x18E8));
    return 1;
}
