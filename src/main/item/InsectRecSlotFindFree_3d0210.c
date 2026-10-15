#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 InsectRecSlotFindFree_3d0210(struct Obj0 *p0)
{
    s32 l0;
    s32 t0;
    s32 t1;

    l0 = 0;
    while (l0 < 5) {
        t0 = p0->m18;
        t1 = *(s32 *)((u8 *)t0 + (l0 << 2) + 0xC);
        if (t1 == 0) {
            return l0;
        }
        l0 = (l0 + 1);
    }
    return -1;
}
