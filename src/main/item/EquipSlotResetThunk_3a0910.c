#include "types.h"

extern void EquipSlotReset_3a0910(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EquipSlotResetThunk_3a0910(s32 p0)
{
    EquipSlotReset_3a0910(p0);
}
