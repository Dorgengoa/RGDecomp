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
    s64 m10;
    s64 m18;
    s64 m20;
    s64 m28;
    s64 m30;
    s64 m38;
    s64 m40;
    s64 m48;
    s64 m50;
    s64 m58;
    s64 m60;
    s64 m68;
    s64 m70;
    s64 m78;
    s64 m80;
    s64 m88;
    s64 m90;
    s64 m98;
};

struct Obj1 {
    u8 pad000[0x70];
    s64 m70;
    s64 m78;
    s64 m80;
    s64 m88;
    s64 m90;
    s64 m98;
    s64 mA0;
    s64 mA8;
    s64 mB0;
    s64 mB8;
    s64 mC0;
    s64 mC8;
    s64 mD0;
    s64 mD8;
    s64 mE0;
    s64 mE8;
    s64 mF0;
    s64 mF8;
};

s32 DrawEnvWritePacket_157460(struct Obj1 *p0, struct Obj0 *p1)
{
    s64 t0;
    s64 t1;
    s64 t2;
    s64 t3;
    s64 t4;
    s64 t5;
    s64 t6;
    s64 t7;
    s64 t8;
    s64 t9;
    s64 t10;
    s64 t11;
    s64 t12;
    s64 t13;
    s64 t14;
    s64 t15;
    s64 t16;
    s64 t17;

    p1->m00 = 0x60000009;
    p1->m04 = 0;
    p1->m08 = 0;
    p1->m0C = 0x50000009;
    t0 = p0->m70;
    p1->m10 = t0;
    t1 = p0->m78;
    p1->m18 = t1;
    t2 = p0->m80;
    p1->m20 = t2;
    t3 = p0->m88;
    p1->m28 = t3;
    t4 = p0->m90;
    p1->m30 = t4;
    t5 = p0->m98;
    p1->m38 = t5;
    t6 = p0->mA0;
    p1->m40 = t6;
    t7 = p0->mA8;
    p1->m48 = t7;
    t8 = p0->mB0;
    p1->m50 = t8;
    t9 = p0->mB8;
    p1->m58 = t9;
    t10 = p0->mC0;
    p1->m60 = t10;
    t11 = p0->mC8;
    p1->m68 = t11;
    t12 = p0->mD0;
    p1->m70 = t12;
    t13 = p0->mD8;
    p1->m78 = t13;
    t14 = p0->mE0;
    p1->m80 = t14;
    t15 = p0->mE8;
    p1->m88 = t15;
    t16 = p0->mF0;
    p1->m90 = t16;
    t17 = p0->mF8;
    p1->m98 = t17;
    return 0xA;
}
