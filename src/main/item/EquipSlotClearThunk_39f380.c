#include "types.h"

extern void EquipSlotClear_3a0900(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EquipSlotClearThunk_39f380(s32 p0)
{
    EquipSlotClear_3a0900(p0);
}
