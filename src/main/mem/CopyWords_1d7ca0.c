#include "types.h"

extern s32 memcpy(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CopyWords_1d7ca0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = memcpy(p0, p1, (p2 << 2));
    return p2;
}
