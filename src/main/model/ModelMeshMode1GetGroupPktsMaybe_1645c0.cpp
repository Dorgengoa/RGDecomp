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
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0xA8];
    s32 mA8;
    u8 pad0AC[0x14];
    s32 mC0;
};

struct Obj1 {
    s32 m00;
    s32 m04;
};

struct Obj2 {
    s32 m00;
};

extern "C" void ModelMeshMode1GetGroupPktsMaybe_1645c0(struct Obj0 *p0, s32 p1, struct Obj1 *p2, struct Obj2 *p3)
{
    s32 t0;
    s32 t1;

    ((struct C80 *)p0)->v6();
    t0 = p0->mA8;
    p2->m00 = t0;
    t1 = p0->mC0;
    p3->m00 = t1;
    p2->m04 = -1;
}
