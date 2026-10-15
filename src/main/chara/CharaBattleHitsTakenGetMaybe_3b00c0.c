#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4AE];
    s16 m4AE;
};

s16 CharaBattleHitsTakenGetMaybe_3b00c0(struct Obj0 *p0)
{
    s16 t0;

    t0 = p0->m4AE;
    return t0;
}
