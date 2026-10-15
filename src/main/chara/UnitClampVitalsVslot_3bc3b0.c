#include "types.h"

extern void UnitClampVitalsThunk_3bc420(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void UnitClampVitalsVslot_3bc3b0(s32 p0)
{
    UnitClampVitalsThunk_3bc420(p0);
}
