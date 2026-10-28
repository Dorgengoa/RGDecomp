/* rgp:protos */
#define RGP_SELF_JdgGridNodeGetBounds_3171f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x20];
    f32 m20;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
    u8 pad00C[0x4];
    f32 m10;
    f32 m14;
    f32 m18;
};

void JdgGridNodeGetBounds_3171f0(struct Obj0 *p0, struct Obj1 *p1)
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

    VecMaxMin_13df70(p1, (struct Obj1 *)((u8 *)p1 + 0x10), p0, (struct Obj0 *)((u8 *)p0 + 0x10));
    t0 = p0->m20;
    t1 = p1->m00;
    p1->m00 = (t1 + t0);
    t2 = p0->m20;
    t3 = p1->m04;
    p1->m04 = (t3 + t2);
    t4 = p0->m20;
    t5 = p1->m08;
    p1->m08 = (t5 + t4);
    t6 = p0->m20;
    t7 = p1->m10;
    p1->m10 = (t7 - t6);
    t8 = p0->m20;
    t9 = p1->m14;
    p1->m14 = (t9 - t8);
    t10 = p0->m20;
    t11 = p1->m18;
    p1->m18 = (t11 - t10);
}
