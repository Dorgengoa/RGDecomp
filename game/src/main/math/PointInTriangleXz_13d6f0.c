/* rgp:protos */
#define RGP_SELF_PointInTriangleXz_13d6f0 1
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
struct Obj2;
struct Obj3;

struct Obj0 {
    f32 m00;
    u8 pad004[0x4];
    f32 m08;
};

struct Obj1 {
    f32 m00;
    u8 pad004[0x4];
    f32 m08;
};

struct Obj2 {
    f32 m00;
    u8 pad004[0x4];
    f32 m08;
};

struct Obj3 {
    f32 m00;
    u8 pad004[0x4];
    f32 m08;
};

int PointInTriangleXz_13d6f0(struct Obj0 *p0, struct Obj1 *p1, struct Obj2 *p2, struct Obj3 *p3)
{
    f32 t0;
    f32 t1;
    f32 t2;
    f32 t3;
    f32 t4;
    f32 t5;
    f32 t6;
    f32 t7;

    t0 = p0->m08;
    t1 = p1->m00;
    t2 = p1->m08;
    t3 = p2->m00;
    t4 = p2->m08;
    t5 = p3->m00;
    t6 = p3->m08;
    t7 = p0->m00;
    return PointInTriangle2D_13d4d0(t7, t0, t1, t2, t3, t4, t5, t6);
}
