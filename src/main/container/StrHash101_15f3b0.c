#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s8 m00;
};

s32 StrHash101_15f3b0(s32 p0, s32 p1)
{
    s32 l0;
    struct Obj0 *l1;

    l0 = 0;
    l1 = (struct Obj0 *)p1;
    while (l1->m00 != 0) {
        l0 = (((((l0 & 0xFF) << 8) + l1->m00) % 0x65) & 0xFF);
        l1 = (struct Obj0 *)((u8 *)l1 + 1);
    }
    return (l0 & 0xFF);
}
