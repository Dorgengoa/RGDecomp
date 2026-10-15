#include "types.h"

extern s32 MpegAddStrCallback_115740(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 VideoDecSetStream_1d5430(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r;

    r = MpegAddStrCallback_115740(p1, (p2 & 0xFF), p3, p4, p5);
    return 1;
}
