#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x20C];
    s32 m20C;
    s32 m210;
};

struct Obj1 {
    u8 pad000[0x8];
    s32 m08;
};

s32 ObjFindNthAttachPoint_1addc0(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 t1;
    struct Obj1 *l0;
    s32 l2;
    s32 l1;
    s32 t2;
    s32 rv3;

    t0 = p0->m210;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m20C;
    l0 = (struct Obj1 *)t0;
    l2 = -1;
    l1 = 0;
    while (l1 < t1) {
        t2 = l0->m08;
        rv3 = l2;
        if (t2 == p1) {
            rv3 = (l2 + 1);
        }
        if (rv3 == p2) {
            return (s32)l0;
        }
        l1 = (l1 + 1);
        l0 = (struct Obj1 *)((u8 *)l0 + 0x20);
        l2 = rv3;
    }
    return 0;
}
