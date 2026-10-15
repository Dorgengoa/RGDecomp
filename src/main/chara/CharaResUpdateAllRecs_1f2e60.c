#include "types.h"

extern void CharaResRecUpdate_1f48a0(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xD00];
    s32 mD00;
};

void CharaResUpdateAllRecs_1f2e60(struct Obj0 *p0, s32 p1)
{
    struct Obj0 * l1;
    s32 l0;
    s32 t0;

    l1 = (struct Obj0 *)p0;
    l0 = 0;
    do {
        t0 = p0->mD00;
        CharaResRecUpdate_1f48a0(l1, p1, t0);
        l0 = (l0 + 1);
        l1 = (struct Obj0 *)((u8 *)l1 + 0x68);
    } while (l0 < 0x20);
}
