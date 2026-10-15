#include "types.h"

extern void CharaClear_3af980(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaClearThunk_3a9b10(s32 p0)
{
    CharaClear_3af980(p0);
}
