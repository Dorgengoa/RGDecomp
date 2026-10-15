#include "types.h"

extern void memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    u8 pad002[0xA];
    s32 m0C;
};

void ActionPacketClear_3e3e90(struct Obj0 *p0)
{
    p0->m00 = 0;
    memset((struct Obj0 *)((u8 *)p0 + 2), 0, 8);
    p0->m0C = 0;
    memset((struct Obj0 *)((u8 *)p0 + 0x10), 0, 0x18);
}
