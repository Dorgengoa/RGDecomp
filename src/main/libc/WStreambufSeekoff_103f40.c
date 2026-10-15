#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s64 m00;
    s32 m08;
};

void WStreambufSeekoff_103f40(struct Obj0 *p0)
{
    p0->m00 = -1;
    p0->m08 = 0;
}
