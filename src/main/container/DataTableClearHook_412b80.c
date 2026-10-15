#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x94];
    s32 m94;
};

void DataTableClearHook_412b80(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;

    p0->m94 = 0;
    l1 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l1 * 0x6) + 0x98) = -1;
        *(s16 *)((u8 *)p0 + (l1 * 0x6) + 0x9A) = -1;
        *(s16 *)((u8 *)p0 + (l1 * 0x6) + 0x9C) = -1;
        l0 = ((l1 + 1) < 0x65);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
