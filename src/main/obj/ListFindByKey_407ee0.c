#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
    s32 m04;
};

struct Obj1 {
    u8 m00;
};

s32 ListFindByKey_407ee0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s16 t1;
    struct Obj1 *l0;
    s32 l1;
    u8 t2;

    t0 = p0->m04;
    t1 = p0->m02;
    l0 = (struct Obj1 *)t0;
    l1 = 0;
    while (l1 < t1) {
        t2 = l0->m00;
        if (t2 == p1) {
            return (s32)l0;
        }
        l1 = (l1 + 1);
        l0 = (struct Obj1 *)((u8 *)l0 + 0xC);
    }
    return 0;
}
