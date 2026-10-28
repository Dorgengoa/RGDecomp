/* rgp:protos */
#define RGP_SELF_XformGetScaledMatrix_2e76b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    f32 m18;
    f32 m1C;
    f32 m20;
    f32 m24;
    f32 m28;
    f32 m2C;
    f32 m30;
    f32 m34;
    f32 m38;
    f32 m3C;
    f32 m40;
    f32 m44;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
    s32 m0C;
    f32 m10;
    f32 m14;
    f32 m18;
    s32 m1C;
    f32 m20;
    f32 m24;
    f32 m28;
    s32 m2C;
    f32 m30;
    f32 m34;
    f32 m38;
    s32 m3C;
};

void XformGetScaledMatrix_2e76b0(struct Obj0 *p0, struct Obj1 *p1, f32 fa0, f32 fa1, f32 fa2)
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

    t0 = p0->m24;
    p1->m00 = (fa0 * t0);
    t1 = p0->m28;
    p1->m04 = (fa0 * t1);
    t2 = p0->m2C;
    p1->m08 = (fa0 * t2);
    p1->m0C = 0;
    t3 = p0->m30;
    p1->m10 = (fa1 * t3);
    t4 = p0->m34;
    p1->m14 = (fa1 * t4);
    t5 = p0->m38;
    p1->m18 = (fa1 * t5);
    p1->m1C = 0;
    t6 = p0->m3C;
    p1->m20 = (fa2 * t6);
    t7 = p0->m40;
    p1->m24 = (fa2 * t7);
    t8 = p0->m44;
    p1->m28 = (fa2 * t8);
    p1->m2C = 0;
    t9 = p0->m18;
    p1->m30 = t9;
    t10 = p0->m1C;
    p1->m34 = t10;
    t11 = p0->m20;
    p1->m38 = t11;
    p1->m3C = 0x3F800000;
}
