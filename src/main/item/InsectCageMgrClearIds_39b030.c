#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA0];
    s16 mA0;
};

void InsectCageMgrClearIds_39b030(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;

    l1 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l1 << 1) + 0x94) = -1;
        l0 = ((l1 + 1) < 6);
        l1 = (l1 + 1);
    } while (l0 != 0);
    p0->mA0 = 0;
}
