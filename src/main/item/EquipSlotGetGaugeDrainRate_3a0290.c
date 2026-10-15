#include "types.h"

extern void AbilityDataGetGaugeDrainRate_3f5c40(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

f32 EquipSlotGetGaugeDrainRate_3a0290(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->m04;
    if (t0 != 0) {
        AbilityDataGetGaugeDrainRate_3f5c40(t0);
        return;
    }
    return 0.0f;
}
