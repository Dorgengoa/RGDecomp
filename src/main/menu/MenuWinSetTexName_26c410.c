#include "types.h"

extern void strcpy(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    u8 pad00C[0xAC];
    s32 mB8;
};

void MenuWinSetTexName_26c410(struct Obj0 *p0, s32 p1, s32 p2)
{
    strcpy((struct Obj0 *)((u8 *)p0 + 0xC), p1);
    p0->m08 = p2;
    p0->mB8 = 0;
}
