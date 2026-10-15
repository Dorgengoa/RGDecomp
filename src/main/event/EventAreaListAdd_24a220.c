#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    s32 m00;
};

s32 EventAreaListAdd_24a220(s32 p0, s32 p1)
{
    struct Obj0 *l2;
    struct Obj1 *l1;
    s32 l0;
    s32 t0;
    struct Obj0 * rv4;
    struct Obj0 * rv3;

    l2 = (struct Obj0 *)(p0 + 0x334);
    l1 = (struct Obj1 *)0;
    l0 = 0;
    while (l0 < 0x20) {
        t0 = l2->m00;
        if (t0 == p1) {
            return 1;
        }
        rv4 = (struct Obj0 *)l1;
        if (l1 == 0) {
            rv3 = (struct Obj0 *)l1;
            if (t0 < 0) {
                rv3 = (struct Obj0 *)l2;
            }
            rv4 = (struct Obj0 *)rv3;
        }
        l0 = (l0 + 1);
        l1 = (struct Obj1 *)rv4;
        l2 = (struct Obj0 *)((u8 *)l2 + 4);
    }
    if (l1 != 0) {
        l1->m00 = p1;
        return 1;
    }
    return 0;
}
