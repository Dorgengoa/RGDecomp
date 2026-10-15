#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4BD];
    u8 m4BD;
    u8 m4BE;
};

s32 CharaGaugeClear_3aaee0(struct Obj0 *p0)
{
    p0->m4BD = 0;
    p0->m4BE = 0;
    return 1;
}
