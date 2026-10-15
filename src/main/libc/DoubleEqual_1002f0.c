#include "types.h"

extern s32 DoubleCmp_13b948(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 DoubleEqual_1002f0(s32 p0, s32 p1)
{
    s32 r;

    r = DoubleCmp_13b948(p0, p1);
    return (r == 0);
}
