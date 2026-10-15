#include "types.h"

extern s32 EquipSlotGetAbilityType_3a0720(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 EquipSlotHasGaugeMaybe_39ef10(s32 p0)
{
    s32 r;

    r = EquipSlotGetAbilityType_3a0720(p0);
    return (r == 2);
}
