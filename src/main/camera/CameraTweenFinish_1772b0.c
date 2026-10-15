#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

struct Obj0;

struct Obj0 {
    u8 pad000[0x50];
    u128 m50;
    u128 m60;
    u8 pad070[0x70];
    u128 mE0;
    u128 mF0;
};

void CameraTweenFinish_1772b0(struct Obj0 *p0)
{
    p0->m60 = p0->mF0;
    p0->m50 = p0->mE0;
}
