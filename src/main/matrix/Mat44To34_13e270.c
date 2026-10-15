#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    f32 m00;
    f32 m04;
    f32 m08;
    u8 pad00C[0x4];
    f32 m10;
    f32 m14;
    f32 m18;
    u8 pad01C[0x4];
    f32 m20;
    f32 m24;
    f32 m28;
    u8 pad02C[0x4];
    f32 m30;
    f32 m34;
    f32 m38;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
    f32 m0C;
    f32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
    f32 m20;
    f32 m24;
    f32 m28;
    f32 m2C;
};

void Mat44To34_13e270(struct Obj1 *p0, struct Obj0 *p1)
{
    f32 t0;
    f32 t1;
    f32 t2;
    f32 t3;
    f32 t4;
    f32 t5;
    f32 t6;
    f32 t7;
    f32 t8;
    f32 t9;
    f32 t10;
    f32 t11;

    t0 = p1->m00;
    p0->m00 = t0;
    t1 = p1->m04;
    p0->m04 = t1;
    t2 = p1->m08;
    p0->m08 = t2;
    t3 = p1->m10;
    p0->m0C = t3;
    t4 = p1->m14;
    p0->m10 = t4;
    t5 = p1->m18;
    p0->m14 = t5;
    t6 = p1->m20;
    p0->m18 = t6;
    t7 = p1->m24;
    p0->m1C = t7;
    t8 = p1->m28;
    p0->m20 = t8;
    t9 = p1->m30;
    p0->m24 = t9;
    t10 = p1->m34;
    p0->m28 = t10;
    t11 = p1->m38;
    p0->m2C = t11;
}
