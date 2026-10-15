#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2];
    s8 m02;
    u8 pad003[0x1];
    s16 m04;
};

s32 ItemDefIsKindCId4B0_40e310(struct Obj0 *p0)
{
    s8 t0;
    s16 t1;

    t0 = p0->m02;
    if (t0 == 0xC) {
        t1 = p0->m04;
        return (t1 == 0x4B0);
    }
    return 0;
}
