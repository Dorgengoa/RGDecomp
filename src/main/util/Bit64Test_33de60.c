#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s64 m00;
};

u8 Bit64Test_33de60(struct Obj0 *p0, s32 p1)
{
    s64 t0;

    t0 = p0->m00;
    return ((t0 & (1 << p1)) != 0);
}
