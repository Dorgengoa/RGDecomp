#include "types.h"

extern void CharaKind1001ResetState_3a9b20(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaResetStateThunk_3a9a80(s32 p0)
{
    CharaKind1001ResetState_3a9b20(p0);
}
