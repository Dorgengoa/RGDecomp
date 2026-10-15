#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xB560];
    u8 mB560;
    u8 mB561;
    u8 mB562;
    u8 mB563;
};

void GameSceneTintReset_1ce980(struct Obj0 *p0)
{
    p0->mB560 = 0;
    p0->mB561 = 0x80;
    p0->mB562 = 0x80;
    p0->mB563 = 0x80;
}
