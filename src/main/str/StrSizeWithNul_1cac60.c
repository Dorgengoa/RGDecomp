#include "types.h"

extern s32 strlen(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 StrSizeWithNul_1cac60(s32 p0)
{
    s32 r0;

    if (p0 != 0) {
        r0 = strlen(p0);
        return (r0 + 1);
    }
    return 0;
}
