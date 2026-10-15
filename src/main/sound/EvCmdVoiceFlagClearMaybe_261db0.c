#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004BDA20;

s32 EvCmdVoiceFlagClearMaybe_261db0(s32 p0)
{
    s32 r;

    *(s32 *)&D_004BDA20 = 0;
    r = ScriptGetInt_26a2a0(p0);
    return 1;
}
