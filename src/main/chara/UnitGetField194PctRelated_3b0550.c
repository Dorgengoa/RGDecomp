#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x194];
    s16 m194;
};

f32 UnitGetField194PctRelated_3b0550(struct Obj0 *p0)
{
    return (((f32)p0->m194) / 100.0f);
}
