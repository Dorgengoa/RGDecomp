#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004814D4;

s32 SoundNextVoiceId_1b81a0(void)
{
    s32 t0;
    s32 t1;

    t0 = D_004814D4;
    t1 = ((t0 + 1) % 0x19);
    D_004814D4 = t1;
    return (t1 + 0x34);
}
