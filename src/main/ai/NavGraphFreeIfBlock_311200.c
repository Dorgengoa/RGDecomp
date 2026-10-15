#include "types.h"

extern void HeapBlockRefFreeIfBlock_42e0e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void NavGraphFreeIfBlock_311200(s32 p0, s32 p1)
{
    HeapBlockRefFreeIfBlock_42e0e0(p0, p1);
}
