#include "types.h"

extern void CharaKind1002ResetState_3a99a0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaResetStateThunk_3a9900(s32 p0)
{
    CharaKind1002ResetState_3a99a0(p0);
}
