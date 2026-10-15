#include "types.h"

extern void CharaTintResetOverride_21f0b0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1A];
    s16 m1A;
    s32 m1C;
};

void CharaTintClear_21f520(struct Obj0 *p0)
{
    CharaTintResetOverride_21f0b0(p0);
    p0->m1C = 0;
    p0->m1A = 0;
}
