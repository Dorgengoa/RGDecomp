#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2C];
    s16 m2C;
};

struct Obj0 *PartyGetBgmOverride_3cb100(struct Obj0 *p0)
{
    s16 t0;

    t0 = p0->m2C;
    if (t0 < 0) {
        return (struct Obj0 *)0;
    }
    return (struct Obj0 *)((u8 *)p0 + 0x2C);
}
