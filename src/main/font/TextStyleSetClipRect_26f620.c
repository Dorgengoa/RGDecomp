#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s16 m20;
    u8 pad022[0x2];
    s32 m24;
    s32 m28;
    s32 m2C;
    s32 m30;
};

void TextStyleSetClipRect_26f620(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    p0->m20 = 1;
    p0->m24 = p1;
    p0->m28 = p2;
    p0->m2C = p3;
    p0->m30 = p4;
}
