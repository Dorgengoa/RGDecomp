#include "types.h"

extern s32 UnitClampVitalsThunk_3a9770(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UnitClampVitalsThunk_3a95c0(s32 p0)
{
    s32 r0;

    r0 = UnitClampVitalsThunk_3a9770(p0);
    return (r0 & 0xFF);
}
