#include "types.h"

extern void CharaReleaseHeldTarget_2116b0(s32, s32, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaDropHeldTarget_211de0(s32 p0, s32 p1)
{
    CharaReleaseHeldTarget_2116b0(p0, p1, 0.0f, 0.0f, 0.0f);
}
