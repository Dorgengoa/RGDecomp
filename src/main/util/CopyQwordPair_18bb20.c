#include "types.h"

extern void CopyQword_18bb60(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CopyQwordPair_18bb20(s32 p0, s32 p1, s32 p2)
{
    CopyQword_18bb60(p0, p1);
    CopyQword_18bb60((p0 + 0x10), p2);
}
