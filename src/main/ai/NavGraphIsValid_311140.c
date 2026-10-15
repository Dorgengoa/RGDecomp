#include "types.h"

extern s32 NavGraphGetId_310e90(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 NavGraphIsValid_311140(s32 p0)
{
    s32 r;

    r = NavGraphGetId_310e90(p0);
    return (r >= 0);
}
