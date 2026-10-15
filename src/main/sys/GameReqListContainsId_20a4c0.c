#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    s16 m04;
};

struct Obj1 {
    s32 m00;
};

s32 GameReqListContainsId_20a4c0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s16 t1;
    s32 l0;
    struct Obj1 *l1;
    s32 t2;

    t0 = p0->m00;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m04;
    l0 = 0;
    l1 = (struct Obj1 *)t0;
    while (l0 < t1) {
        t2 = l1->m00;
        if (t2 == p1) {
            return 1;
        }
        l0 = (l0 + 1);
        l1 = (struct Obj1 *)((u8 *)l1 + 0x14);
    }
    return 0;
}
