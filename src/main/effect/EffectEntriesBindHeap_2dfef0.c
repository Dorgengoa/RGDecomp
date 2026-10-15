#include "types.h"

extern void EffectEntrySetHeaps_2dc540(void *, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2A00];
    s32 m2A00;
};

void EffectEntriesBindHeap_2dfef0(struct Obj0 *p0, s32 p1)
{
    s32 l0;
    s32 l1;

    p0->m2A00 = p1;
    l1 = 0;
    do {
        EffectEntrySetHeaps_2dc540((struct Obj0 *)((u8 *)p0 + (((l1 << 3) - l1) << 5)), 0, p1, -1);
        l0 = ((l1 + 1) < 0x30);
        l1 = (l1 + 1);
    } while (l0 != 0);
}
