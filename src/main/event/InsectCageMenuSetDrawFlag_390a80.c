#include "types.h"

extern void BitArraySetReturnOld_384360(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048335C;

void InsectCageMenuSetDrawFlag_390a80(s32 p0, s32 p1)
{
    BitArraySetReturnOld_384360(&D_0048335C, p0, p1);
}
