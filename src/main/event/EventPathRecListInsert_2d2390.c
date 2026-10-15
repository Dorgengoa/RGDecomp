#include "types.h"

extern void DListPushBack_42e5a0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EventPathRecListInsert_2d2390(s32 p0, s32 p1)
{
    DListPushBack_42e5a0(p0, p1);
}
