#include "types.h"

extern void EventSoundFadeTo_249ff0(s32, s32, s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EventSoundFadeOut_24a030(s32 p0, s32 p1, s32 p2, s32 p3)
{
    EventSoundFadeTo_249ff0(p0, p1, p2, p3, 0.0f);
}
