#include "types.h"

extern void * EquipSlotGetAbilityKind0Rec_3a0780(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
};

s32 EquipSlotGetAbilityEffectRef2_3a0450(s32 p0)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = EquipSlotGetAbilityKind0Rec_3a0780(p0);
    if (r0 != 0) {
        t0 = r0->m14;
        return t0;
    }
    return 0;
}
