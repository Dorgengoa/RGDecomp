#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x800];
    s32 m800;
};

void IdSlotTableInit_1efa30(struct Obj0 *p0)
{
    s32 l0;

    l0 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l0 << 3)) = 0;
        *(s32 *)((u8 *)p0 + (l0 << 3) + 0x4) = -1;
        l0 = (l0 + 1);
    } while (l0 < 0x100);
    p0->m800 = 0;
}
