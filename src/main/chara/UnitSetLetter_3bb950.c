#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x238];
    u8 m238;
};

void UnitSetLetter_3bb950(struct Obj0 *p0, s32 p1)
{
    p0->m238 = p1;
}
