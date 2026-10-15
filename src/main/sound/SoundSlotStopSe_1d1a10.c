#include "types.h"

extern s32 SoundSlotGetHandle_1d2150(s32);
extern void SoundStopEntry_1b8bc0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SoundSlotStopSe_1d1a10(s32 p0, s32 p1)
{
    s32 r0;

    r0 = SoundSlotGetHandle_1d2150(p0);
    SoundStopEntry_1b8bc0(r0, p1, 0);
}
