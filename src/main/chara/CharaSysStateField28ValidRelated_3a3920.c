#include "types.h"

extern s32 CharaSysStateGetField28Related_3a3820(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 CharaSysStateField28ValidRelated_3a3920(s32 p0)
{
    s32 r;

    r = CharaSysStateGetField28Related_3a3820(p0);
    return (r >= 0);
}
