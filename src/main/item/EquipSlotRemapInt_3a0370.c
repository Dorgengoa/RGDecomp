#include "types.h"

extern s32 AbilityDataRemapInt_3f5a10(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 EquipSlotRemapInt_3a0370(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 r0;

    t0 = p0->m04;
    if (t0 != 0) {
        r0 = AbilityDataRemapInt_3f5a10(t0, p1, p2);
        return r0;
    }
    return 0;
}
