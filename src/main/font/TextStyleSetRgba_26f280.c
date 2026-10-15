#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    u8 m08;
    u8 m09;
    u8 m0A;
    u8 m0B;
};

void TextStyleSetRgba_26f280(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    p0->m08 = p1;
    p0->m09 = p2;
    p0->m0A = p3;
    p0->m0B = p4;
}
