#include "types.h"

extern void strcpy(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xAAC];
    u8 mAAC;
};

void CharaSetAbltName_2137e0(struct Obj0 *p0, s32 p1)
{
    p0->mAAC = 0;
    if (p1 != 0) {
        strcpy((struct Obj0 *)((u8 *)p0 + 0xAAC), p1);
    }
}
