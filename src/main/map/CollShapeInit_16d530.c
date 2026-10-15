#include "types.h"

extern void memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

void CollShapeInit_16d530(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m04 = 0;
    memset((struct Obj0 *)((u8 *)p0 + 0x10), 0, 0x20);
}
