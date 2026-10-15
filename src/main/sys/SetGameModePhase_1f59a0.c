#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004B51E0;

void SetGameModePhase_1f59a0(s32 p0)
{
    *(s32 *)&D_004B51E0 = p0;
}
