#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 SoundBankRelease_1bb6e0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdSoundBankRelease_262610(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = SoundBankRelease_1bb6e0(r0);
    return 1;
}
