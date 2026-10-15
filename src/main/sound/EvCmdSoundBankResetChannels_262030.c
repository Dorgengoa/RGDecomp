#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 SoundBankStopAll_1bad70(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdSoundBankResetChannels_262030(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = SoundBankStopAll_1bad70(r0);
    return 1;
}
