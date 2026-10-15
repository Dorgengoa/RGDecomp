#include "types.h"

extern void memcpy(void *, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x170];
    s32 m170;
};

void MinimapSelectNow_32ad20(struct Obj0 *p0, s32 p1)
{
    p0->m170 = p1;
    memcpy(p0, (struct Obj0 *)((u8 *)p0 + 0x10), 0x10);
}
