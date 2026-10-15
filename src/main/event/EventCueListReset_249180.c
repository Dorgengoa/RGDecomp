#include "types.h"

extern void Vec4VectorClear_250970(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x498];
    s32 m498;
    s32 m49C;
};

void EventCueListReset_249180(struct Obj0 *p0)
{
    Vec4VectorClear_250970((struct Obj0 *)((u8 *)p0 + 0x48C));
    p0->m498 = 0;
    p0->m49C = 0;
}
