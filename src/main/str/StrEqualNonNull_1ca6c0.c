#include "types.h"

extern s32 strcmp(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 StrEqualNonNull_1ca6c0(s32 p0, s32 p1)
{
    s32 r0;

    if (p0 == 0 || p1 == 0) {
        return (u8)0;
    }
    r0 = strcmp(p0, p1);
    return (r0 == 0);
}
