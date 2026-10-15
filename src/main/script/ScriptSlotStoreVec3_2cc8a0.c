#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;
struct Obj4;

struct Obj0 {
    s32 m00;
    struct Obj2 *m04;
    u8 pad008[0x4];
    struct Obj3 *m0C;
    u8 pad010[0x4];
    struct Obj4 *m14;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
};

struct Obj2 {
    u8 pad000[0x4];
    f32 m04;
};

struct Obj3 {
    u8 pad000[0x4];
    f32 m04;
};

struct Obj4 {
    u8 pad000[0x4];
    f32 m04;
};

void ScriptSlotStoreVec3_2cc8a0(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t0;
    f32 t1;
    struct Obj2 * t2;
    f32 t3;
    struct Obj3 * t4;
    f32 t5;
    struct Obj4 * t6;

    t0 = p0->m00;
    if (t0 == 3) {
        t1 = p1->m00;
        t2 = p0->m04;
        p0->m04->m04 = t1;
        t3 = p1->m04;
        t4 = p0->m0C;
        p0->m0C->m04 = t3;
        t5 = p1->m08;
        t6 = p0->m14;
        p0->m14->m04 = t5;
        return;
    }
}
