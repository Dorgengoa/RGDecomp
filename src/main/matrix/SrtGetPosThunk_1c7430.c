#include "types.h"

extern void SrtGetPos_1c7430(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SrtGetPosThunk_1c7430(s32 p0, s32 p1)
{
    SrtGetPos_1c7430(p0, p1);
}
