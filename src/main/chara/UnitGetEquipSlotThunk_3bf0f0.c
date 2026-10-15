#include "types.h"

extern void UnitGetEquipSlot_3bd7e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void UnitGetEquipSlotThunk_3bf0f0(s32 p0, s32 p1)
{
    UnitGetEquipSlot_3bd7e0(p0, p1);
}
