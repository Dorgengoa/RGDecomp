#include "types.h"

extern void ViBufDelete_1d3e20(s32);
extern s32 MpegDelete_111100(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 VideoDecDelete_1d53f0(s32 p0, s32 p1)
{
    s32 r1;

    ViBufDelete_1d3e20((p1 + 0x48));
    r1 = MpegDelete_111100(p1);
    return 1;
}
