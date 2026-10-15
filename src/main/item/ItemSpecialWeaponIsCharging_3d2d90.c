#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x24];
    s16 m24;
};

u8 ItemSpecialWeaponIsCharging_3d2d90(struct Obj0 *p0)
{
    return ((p0->m24 & 4) != 0);
}
