#include "types.h"

struct C80 {
    u8 pad000[0x50];
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    virtual s32 v8();
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0xF0];
    s32 mF0;
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

extern "C" void ModelMeshGetGroupPktsMaybe_15b150(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 t0;
    struct Obj1 *l1;
    struct Obj3 *l2;
    struct Obj2 *l3;
    s32 t1;
    s32 t2;
    s32 t3;

    ((struct C80 *)p0)->v8();
    t0 = p0->mF0;
    l1 = (struct Obj1 *)t0;
    l2 = (struct Obj3 *)p3;
    l3 = (struct Obj2 *)p2;
    while (l1 != 0) {
        t1 = l1->m0C;
        l3->m00 = t1;
        t2 = l1->m10;
        l2->m00 = t2;
        t3 = l1->m00;
        l1 = (struct Obj1 *)t3;
        l2 = (struct Obj3 *)((u8 *)l2 + 4);
        l3 = (struct Obj2 *)((u8 *)l3 + 4);
    }
    l3->m00 = -1;
}
