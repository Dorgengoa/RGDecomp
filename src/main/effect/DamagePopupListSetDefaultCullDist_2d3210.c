#include "types.h"

extern void DamagePopupListSetCullDist_2d2e60(void *, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    u8 m0C;
};

void DamagePopupListSetDefaultCullDist_2d3210(struct Obj0 *p0)
{
    p0->m0C = 1;
    DamagePopupListSetCullDist_2d2e60(p0, 50.0f);
}
