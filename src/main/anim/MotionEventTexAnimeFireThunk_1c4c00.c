#include "types.h"

extern void MotionEventTexAnimeFire_1b1130(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MotionEventTexAnimeFireThunk_1c4c00(s32 p0, s32 p1)
{
    MotionEventTexAnimeFire_1b1130(p0, p1);
}
