#include "types.h"

extern void UnitBaseClear_3b8520(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4A4];
    s32 m4A4;
    s32 m4A8;
};

void CharaClear_3af980(struct Obj0 *p0)
{
    UnitBaseClear_3b8520(p0);
    p0->m4A4 = 0;
    p0->m4A8 = 0;
}
