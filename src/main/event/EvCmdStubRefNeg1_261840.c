#include "types.h"

extern s32 ScriptSetRefInt_26a1e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdStubRefNeg1_261840(s32 p0)
{
    s32 r;

    r = ScriptSetRefInt_26a1e0(p0, -1);
    return 1;
}
