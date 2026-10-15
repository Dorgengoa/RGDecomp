#include "types.h"

extern void UskMemoryFree_42d8a0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
};

void HeapBlockRefRelease_42e250(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m00;
    if (t0 != 0) {
        t1 = p0->m04;
        UskMemoryFree_42d8a0(t0, t1, 0);
        p0->m00 = 0;
    } else {
        p0->m00 = 0;
    }
    p0->m04 = 0;
    p0->m08 = 0;
}
