#include "types.h"

extern void EffectTimedSlotReset_2d4cf0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    s32 m0C;
};

void EffectTimedSlotInit_2d4d10(struct Obj0 *p0)
{
    EffectTimedSlotReset_2d4cf0(p0);
    p0->m08 = -1;
    p0->m0C = 0;
}
