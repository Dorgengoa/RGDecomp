#include "types.h"

extern void CharaMgrPoolCount_3a8260(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaMgrPoolViewCountThunk_3b09c0(s32 p0)
{
    CharaMgrPoolCount_3a8260((p0 + -4));
}
