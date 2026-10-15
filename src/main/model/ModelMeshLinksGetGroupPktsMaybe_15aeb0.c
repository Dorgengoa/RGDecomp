#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x130];
    s32 m130;
};

struct Obj1 {
    s32 m00;
    u8 pad004[0x8];
    s32 m0C;
    s32 m10;
};

struct Obj2 {
    s32 m00;
};

struct Obj3 {
    s32 m00;
};

s32 ModelMeshLinksGetGroupPktsMaybe_15aeb0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 t0;
    struct Obj1 *l0;
    struct Obj2 *l1;
    struct Obj3 *l2;
    s32 t1;
    s32 t2;
    s32 t3;

    t0 = p0->m130;
    l0 = (struct Obj1 *)t0;
    l1 = (struct Obj2 *)p2;
    l2 = (struct Obj3 *)p3;
    while (l0 != 0) {
        t1 = l0->m0C;
        l1->m00 = t1;
        t2 = l0->m10;
        l2->m00 = t2;
        t3 = l0->m00;
        l0 = (struct Obj1 *)t3;
        l1 = (struct Obj2 *)((u8 *)l1 + 4);
        l2 = (struct Obj3 *)((u8 *)l2 + 4);
    }
    l1->m00 = -1;
    return 0;
}
