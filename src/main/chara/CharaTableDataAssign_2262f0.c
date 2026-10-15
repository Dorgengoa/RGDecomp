#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s16 m24;
    s16 m26;
    s16 m28;
    s16 m2A;
    s16 m2C;
    s16 m2E;
    s16 m30;
    s16 m32;
};

struct Obj1 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s16 m24;
    s16 m26;
    s16 m28;
    s16 m2A;
    s16 m2C;
    s16 m2E;
    s16 m30;
    s16 m32;
};

struct Obj1 *CharaTableDataAssign_2262f0(struct Obj1 *p0, struct Obj0 *p1)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 t7;
    s32 t8;
    s16 t9;
    s16 t10;
    s16 t11;
    s16 t12;
    s16 t13;
    s16 t14;
    s16 t15;
    s16 t16;

    t0 = p1->m00;
    p0->m00 = t0;
    t1 = p1->m04;
    p0->m04 = t1;
    t2 = p1->m08;
    p0->m08 = t2;
    t3 = p1->m0C;
    p0->m0C = t3;
    t4 = p1->m10;
    p0->m10 = t4;
    t5 = p1->m14;
    p0->m14 = t5;
    t6 = p1->m18;
    p0->m18 = t6;
    t7 = p1->m1C;
    p0->m1C = t7;
    t8 = p1->m20;
    p0->m20 = t8;
    t9 = p1->m24;
    p0->m24 = t9;
    t10 = p1->m26;
    p0->m26 = t10;
    t11 = p1->m28;
    p0->m28 = t11;
    t12 = p1->m2A;
    p0->m2A = t12;
    t13 = p1->m2C;
    p0->m2C = t13;
    t14 = p1->m2E;
    p0->m2E = t14;
    t15 = p1->m30;
    p0->m30 = t15;
    t16 = p1->m32;
    p0->m32 = t16;
    return p0;
}
